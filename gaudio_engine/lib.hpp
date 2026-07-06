namespace gaudio_engine {
    using namespace gnumeric::types;
    using gdecoded_audio::DecodedAudio;
    using gsp::gsp;

    struct AudioEngine {
        AudioEngine() = default;
        AudioEngine(const AudioEngine&) = delete;
        AudioEngine& operator=(const AudioEngine&) = delete;
        AudioEngine(AudioEngine&&) = delete;
        AudioEngine& operator=(AudioEngine&&) = delete;

        void* audioContext;
        std::function<void(void*)> audioContextDestructor;

        uint64 channels;
        uint64 sampleRate;

        struct Task {
            gsp<DecodedAudio> audio;
            int64 offset;
            float64 volume = 1.0;
            bool stopped;

            static gsp<Task> Make() {
                auto* task = new Task();
                return gsp<Task>(task);
            }
        };

        int64 currentOffset;
        float64 currentOffsetTime;
        std::vector<gsp<Task>> tasks;
        float64 volume = 1.0;

        static gsp<AudioEngine> Make() {
            auto* eng = new AudioEngine();
            return gsp<AudioEngine>(eng);
        }

        gsp<Task> createTask(const gsp<DecodedAudio>& audio) noexcept {
            auto task = Task::Make();
            task->audio = audio;
            task->offset = currentOffset;

            std::lock_guard<std::mutex> guard(mtx);
            tasks.push_back(task);
            return task;
        }

        float64 getTaskTime(const gsp<Task>& task) const noexcept {
            return (float64)(currentOffset - task->offset) / sampleRate + (gtime::steady() - currentOffsetTime);
        }

        bool getTaskEnded(const gsp<Task>& task) const noexcept {
            return (task->offset + (int64)task->audio->getSampleCount(sampleRate) <= currentOffset) || task->stopped;
        }

        void seekTask(const gsp<Task>& task, float64 time) const noexcept {
            task->offset = currentOffset - (int64)(time * sampleRate);
        }

        void callback(int16* buffer, int64 frameCount) noexcept {
            {
                std::lock_guard<std::mutex> guard(mtx);
                tasks.erase(std::remove_if(
                    tasks.begin(),
                    tasks.end(),
                    [&](const auto& task) { return getTaskEnded(task); }
                ), tasks.end());
                tasksCopied = tasks;
            }

            bufferCache.resize(frameCount * channels);
            std::fill(bufferCache.begin(), bufferCache.end(), 0);

            for (const auto& task : tasksCopied) {
                int64 startSample = currentOffset - task->offset;
                int64 endSample = startSample + frameCount;

                if (startSample > (int64)task->audio->getSampleCount(sampleRate)) continue;
                if (endSample <= 0) continue;

                startSample = std::max<int64>(0, startSample);
                endSample = std::min<int64>(task->audio->getSampleCount(sampleRate), endSample);

                for (int64 i = startSample; i < endSample; i++) {
                    for (int64 j = 0; j < (int64)channels; j++) {
                        int16 sample = task->audio->sampleAt(i, j, channels, sampleRate);
                        bufferCache[(i - startSample) * channels + j] += (int32)sample * task->volume;
                    }
                }
            }

            for (int64 i = 0; i < (int64)(frameCount * channels); i++) {
                buffer[i] = gnumeric::utils::clamp<int16, int32>(bufferCache[i] * volume);
            }

            currentOffset += frameCount;
            currentOffsetTime = gtime::steady();
        }

        ~AudioEngine() {
            if (audioContextDestructor) {
                audioContextDestructor(audioContext);
            }
        }

        private:
        std::mutex mtx;
        std::vector<gsp<Task>> tasksCopied;
        std::vector<int32> bufferCache;
    };
}
