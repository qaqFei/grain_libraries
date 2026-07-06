extern "C" {
    #include <gvideoenc/libavcodec/avcodec.h>
    #include <gvideoenc/libavformat/avformat.h>
}

namespace gvideoenc {
    using namespace gnumeric::types;
    using gsp::gsp;

    struct VideoCap {
        AVFormatContext* fmtCtx;

        AVStream* vStream;
        AVCodecContext* vCodecCtx;

        AVStream* aStream;
        AVCodecContext* aCodecCtx;

        AVFrame* vFrame;
        AVFrame* aFrame;
        AVPacket* packet;

        static constexpr uint64 aSampleRate = 44100;
        static constexpr uint64 aChannels = 2;

        void init(const std::string& path, int32 width, int32 height, float64 fps) {
            fmtCtx = avformat_alloc_context();
            fmtCtx->oformat = av_guess_format("mp4", nullptr, nullptr);

            const AVCodec* vCodec = avcodec_find_encoder(AV_CODEC_ID_H264);
            vStream = avformat_new_stream(fmtCtx, vCodec);
            vCodecCtx = avcodec_alloc_context3(vCodec);
            vCodecCtx->width = width;
            vCodecCtx->height = height;
            vCodecCtx->time_base = {1, (int32)fps};
            vCodecCtx->framerate = {(int32)fps, 1};
            vCodecCtx->pix_fmt = AV_PIX_FMT_YUV420P;
            vCodecCtx->gop_size = std::max(10, (int32)fps * 2);
            vCodecCtx->max_b_frames = 2;
            vCodecCtx->rc_min_rate = 0;
            vCodecCtx->rc_max_rate = 0;

            AVDictionary* vopts = nullptr;
            av_dict_set(&vopts, "preset", "superfast", 0);
            av_dict_set(&vopts, "tune", "film", 0);
            av_dict_set(&vopts, "crf", "23", 0);
            av_dict_set(&vopts, "refs", "1", 0);
            av_dict_set(&vopts, "rc-lookahead", "20", 0);
            avcodec_open2(vCodecCtx, vCodec, &vopts);
            av_dict_free(&vopts);
            avcodec_parameters_from_context(vStream->codecpar, vCodecCtx);

            const AVCodec* aCodec = avcodec_find_encoder(AV_CODEC_ID_AAC);
            aStream = avformat_new_stream(fmtCtx, aCodec);
            aStream->time_base = {1, aSampleRate};
            aCodecCtx = avcodec_alloc_context3(aCodec);
            aCodecCtx->sample_fmt = AV_SAMPLE_FMT_S16;
            aCodecCtx->bit_rate = 192000;
            aCodecCtx->sample_rate = aSampleRate;
            aCodecCtx->ch_layout.nb_channels = aChannels;
            av_channel_layout_default(&aCodecCtx->ch_layout, aCodecCtx->ch_layout.nb_channels);
            aCodecCtx->time_base = {1, aSampleRate};

            AVDictionary* aopts = nullptr;
            avcodec_open2(aCodecCtx, aCodec, &aopts);
            av_dict_free(&aopts);
            avcodec_parameters_from_context(aStream->codecpar, aCodecCtx);

            vFrame = av_frame_alloc();
            vFrame->pts = 0;
            vFrame->format = AV_PIX_FMT_YUV420P;
            vFrame->width = width;
            vFrame->height = height;

            aFrame = av_frame_alloc();
            aFrame->pts = 0;
            aFrame->format = aCodecCtx->sample_fmt;
            aFrame->ch_layout = aCodecCtx->ch_layout;
            aFrame->sample_rate = aCodecCtx->sample_rate;
            aFrame->nb_samples = aCodecCtx->frame_size;

            packet = av_packet_alloc();

            avio_open(&fmtCtx->pb, path.c_str(), AVIO_FLAG_WRITE);
            avformat_write_header(fmtCtx, nullptr) == 0;
        }

        void writeAudio(gsp<gdecoded_audio::DecodedAudio> audio) {
            audio = audio->copy();
            audio->resample(aCodecCtx->ch_layout.nb_channels, aCodecCtx->sample_rate);

            auto frameSamples = aCodecCtx->frame_size * audio->channels;

            for (uint64 offset = 0; offset + frameSamples <= audio->data.size(); offset += frameSamples) {
                aFrame->data[0] = (uint8*)(audio->data.data() + offset);
                aFrame->pts += aCodecCtx->frame_size;

                if (avcodec_send_frame(aCodecCtx, aFrame) < 0) {
                    std::cerr << "failed to send a frame" << std::endl;
                }

                flush();
            }
        }

        void writeVideoFrame(uint8* data[3], uint64 linesize[3]) {
            vFrame->data[0] = data[0];
            vFrame->data[1] = data[1];
            vFrame->data[2] = data[2];
            vFrame->linesize[0] = linesize[0];
            vFrame->linesize[1] = linesize[1];
            vFrame->linesize[2] = linesize[2];
            vFrame->pts++;

            if (avcodec_send_frame(vCodecCtx, vFrame) < 0) {
                std::cerr << "failed to send v frame" << std::endl;
            }

            flush();
        }

        ~VideoCap() {
            avcodec_send_frame(vCodecCtx, nullptr);
            avcodec_send_frame(aCodecCtx, nullptr);
            flush();

            av_write_trailer(fmtCtx);
            avio_closep(&fmtCtx->pb);

            avformat_free_context(fmtCtx);
            avcodec_free_context(&vCodecCtx);
            avcodec_free_context(&aCodecCtx);
            av_frame_free(&vFrame);
            av_frame_free(&aFrame);
            av_packet_free(&packet);
        }

        private:
        void flushStream(AVStream* stream, AVCodecContext* codecCtx) {
            while (avcodec_receive_packet(codecCtx, packet) == 0) {
                av_packet_rescale_ts(packet, codecCtx->time_base, stream->time_base);
                packet->stream_index = stream->index;
                av_interleaved_write_frame(fmtCtx, packet);
                av_packet_unref(packet);
            }
        }

        void flush() {
            flushStream(vStream, vCodecCtx);
            flushStream(aStream, aCodecCtx);
        }
    };
}
