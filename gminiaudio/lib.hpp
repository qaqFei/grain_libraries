#ifdef GMINIAUDIO_NO_STATIC
#define MINIAUDIO_IMPLEMENTATION
#endif

#include <gminiaudio/miniaudio.h>

namespace gminiaudio {
    using namespace gnumeric::types;
    using gdecoded_audio::DecodedAudio;
    using gaudio_engine::AudioEngine;
    using gsp::gsp;

    gsp<DecodedAudio> decode(const gdata::Data& data) {
        if (data.isStartsWith("OggS")) {
            return gvorbis::decode(data);
        }
        
        ma_decoder_config config = ma_decoder_config_init(ma_format_s16, 0, 0);

        ma_decoder decoder;
        ma_result result = ma_decoder_init_memory(data.data.data(), data.data.size(), &config, &decoder);
        if (result != MA_SUCCESS) {
            throw std::runtime_error("failed to decode audio");
        }

        auto decoded = DecodedAudio::Make();
        decoded->channels = decoder.outputChannels;
        decoded->sampleRate = decoder.outputSampleRate;

        const uint64 chunk_size = 4096;
        std::vector<int16> buffer(chunk_size * decoder.outputChannels);

        while (true) {
            ma_uint64 framesRead = 0;

            ma_result result = ma_decoder_read_pcm_frames(
                &decoder, buffer.data(),
                chunk_size, &framesRead
            );

            decoded->data.insert(decoded->data.end(), buffer.begin(), buffer.begin() + framesRead * decoder.outputChannels);
            if (framesRead < chunk_size) break;
        }

        ma_decoder_uninit(&decoder);
        return decoded;
    }

    gsp<AudioEngine> makeAudioEngine() {
        auto engine = AudioEngine::Make();

        struct AudioContext {
            ma_device device;
            AudioEngine* engine;
        };

        auto ctx = std::unique_ptr<AudioContext>(new AudioContext());

        ma_device_config deviceConfig = ma_device_config_init(ma_device_type_playback);
        deviceConfig.playback.format = ma_format_s16;
        deviceConfig.playback.channels = deviceConfig.sampleRate = 0;
        deviceConfig.dataCallback = [](ma_device* pDevice, void* pOutput, const void* pInput, ma_uint32 frameCount) {
            auto* ctx = (AudioContext*)pDevice->pUserData;
            ctx->engine->callback((int16*)pOutput, frameCount);
        };
        deviceConfig.pUserData = ctx.get();

        if (ma_device_init(NULL, &deviceConfig, &ctx->device) != MA_SUCCESS) {
            throw std::runtime_error("failed to initialize audio device");
        }
        engine->channels = ctx->device.playback.channels;
        engine->sampleRate = ctx->device.sampleRate;

        ctx->engine = engine.get();
        ma_device_start(&ctx->device);

        engine->audioContext = ctx.release();
        engine->audioContextDestructor = [](void* userdata) {
            auto* ctx = (AudioContext*)userdata;
            ma_device_uninit(&ctx->device);
            delete ctx;
        };

        return engine;
    }
}
