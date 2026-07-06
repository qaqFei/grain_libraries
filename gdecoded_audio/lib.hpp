namespace gdecoded_audio {
    using namespace gnumeric::types;
    using gsp::gsp;

    struct DecodedAudio {
        std::vector<int16> data;
        uint64 channels;
        uint64 sampleRate;

        static gsp<DecodedAudio> Make() {
            auto* audio = new DecodedAudio();
            return gsp<DecodedAudio>(audio);
        }

        uint64 getSampleCount() const noexcept {
            return data.size() / channels;
        }

        uint64 getSampleCount(uint64 sampleRate) const noexcept {
            return (float64)getSampleCount() * sampleRate / this->sampleRate;
        }

        int16 sampleAt(float64 index, uint64 channel_index, uint64 channels) const noexcept {
            index = std::clamp<float64>(index, 0, getSampleCount() - 1);

            if (channels == this->channels) {
                float64 v1 = data[int64(index) * channels + channel_index];
                float64 v2 = data[int64(std::ceil(index)) * channels + channel_index];
                return gnumeric::utils::clamp<int16, float64>(v1 + (v2 - v1) * (index - int64(index)));
            } else {
                float64 sum = 0;
                for (uint64 i = 0; i < this->channels; i++) {
                    sum += data[int64(index) * this->channels + i];
                }

                return gnumeric::utils::clamp<int16, float64>(sum / this->channels);
            }
        }

        int16 sampleAt(int64 index, uint64 channel_index, uint64 channels, uint64 sampleRate) const noexcept {
            return sampleAt((float64)index / sampleRate * this->sampleRate, channel_index, channels);
        }

        float64 getLengthInSeconds() const noexcept {
            return (float64)getSampleCount() / sampleRate;
        }

        gsp<DecodedAudio> copy() const {
            auto audio = DecodedAudio::Make();
            audio->data = data;
            audio->channels = channels;
            audio->sampleRate = sampleRate;
            return audio;
        }

        void overlapIndex(const gsp<DecodedAudio>& other, int64 start_index, float64 volume = 1.0) noexcept {
            int64 end_index = start_index + other->getSampleCount(sampleRate);

            if (start_index > (int64)getSampleCount()) return;
            if (end_index < 0) return;

            start_index = std::max<int64>(0, start_index);
            end_index = std::min<int64>(getSampleCount(), end_index);

            for (int64 i = start_index; i < end_index; i++) {
                for (int64 j = 0; j < (int64)channels; j++) {
                    int64 k = i * channels + j;
                    data[k] = gnumeric::utils::clamp<int16, float64>((float64)data[k] + other->sampleAt(i - start_index, j, channels, sampleRate) * volume);
                }
            }
        }

        void overlapSecond(const gsp<DecodedAudio>& other, float64 start_time, float64 volume = 1.0) noexcept {
            overlapIndex(other, (int64)(start_time * sampleRate), volume);
        }

        void applyVolume(float64 volume) noexcept {
            if (volume == 1.0) return;

            for (uint64 i = 0; i < data.size(); i++) {
                data[i] = gnumeric::utils::clamp<int16, float64>((float64)data[i] * volume);
            }
        }

        uint64 getSampleBytesSize() const noexcept {
            return data.size() * sizeof(int16);
        }

        gdata::Data toWav() const {
            using namespace gbyte_rwer;

            ByteWriter<ByteEndian::Little> writer;

            writer.writeBytes("RIFF");
            writer.write<int32>(getSampleBytesSize() + 36);
            writer.writeBytes("WAVEfmt ");
            writer.write<int32>(16);
            writer.write<int16>(1);
            writer.write<int16>(channels);
            writer.write<int32>(sampleRate);
            writer.write<int32>(sampleRate * channels * sizeof(int16));
            writer.write<int16>(channels * sizeof(int16));
            writer.write<int16>(16);
            writer.writeBytes("data");
            writer.write<int32>(getSampleBytesSize());
            for (uint64 i = 0; i < data.size(); i++) {
                writer.write<int16>(data[i]);
            }
            return writer.toData();
        }

        void resample(uint64 channels, uint64 sampleRate) {
            if (channels == this->channels && sampleRate == this->sampleRate) return;
            
            std::vector<int16> data;
            uint64 sampleCount = getSampleCount(sampleRate);
            data.resize(sampleCount * channels);

            for (uint64 i = 0; i < sampleCount; i++) {
                for (uint64 j = 0; j < channels; j++) {
                    data[i * channels + j] = sampleAt(i, j, channels, sampleRate);
                }
            }

            this->data = data;
            this->channels = channels;
            this->sampleRate = sampleRate;
        }
    };
}
