namespace gyuv420frame {
    using namespace gnumeric::types;
    using galigned_stl::aligned_vector;
    using gsp::gsp;

    struct YUV420Frame {
        aligned_vector<uint8, 16> data;
        uint64 width, height;

        void ensureSize() {
            if (data.size() != getDataSize()) {
                data.resize(getDataSize());
            }
        }

        static gsp<YUV420Frame> Make(uint64 width, uint64 height) {
            auto* frame = new YUV420Frame();
            frame->width = width;
            frame->height = height;
            frame->ensureSize();
            return gsp<YUV420Frame>(frame);
        }

        gsp<YUV420Frame> move() {
            auto* frame = new YUV420Frame();
            frame->data = std::move(data);
            frame->width = width;
            frame->height = height;
            return gsp<YUV420Frame>(frame);
        }

        uint64 getDataSize() const { return width * height * 3 / 2; }

        uint8* y() const { return (uint8*)data.data(); }
        uint8* u() const { return (uint8*)data.data() + width * height; }
        uint8* v() const { return (uint8*)data.data() + width * height + width * height / 4; }
        uint64 rowBytesY() const { return width; }
        uint64 rowBytesU() const { return width / 2; }
        uint64 rowBytesV() const { return width / 2; }

        std::array<uint8*, 3> dataPtrs() const { return { y(), u(), v() }; }
        std::array<uint64, 3> rowBytes() const { return { rowBytesY(), rowBytesU(), rowBytesV() }; }

        void fromPtr(void* ptr) {
            memcpy(data.data(), ptr, getDataSize());
        }
    };
}
