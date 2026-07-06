#define STB_VORBIS_HEADER_ONLY
#include <gvorbis/stb_vorbis.c>

namespace gvorbis {
    using namespace gnumeric::types;
    using gdecoded_audio::DecodedAudio;
    using gsp::gsp;

    gsp<DecodedAudio> decode(const gdata::Data& data) {
        int channels, sampleRate;
        int16* pcm;

        uint64 frames = stb_vorbis_decode_memory(
            data.data.data(),
            data.data.size(),
            &channels,
            &sampleRate,
            &pcm
        );

        if (frames <= 0) {
            throw std::runtime_error("failed to decode audio");
        }

        auto decoded = DecodedAudio::Make();
        decoded->channels = channels;
        decoded->sampleRate = sampleRate;
        decoded->data.insert(decoded->data.end(), pcm, pcm + frames * channels);
        free(pcm);
        return decoded;
    }
}
