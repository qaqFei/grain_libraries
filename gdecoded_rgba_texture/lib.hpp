namespace gdecoded_rgba_texture {
    using namespace gnumeric::types;

    struct DecodedRGBATexture {
        std::vector<uint8> data;
        uint64 width, height;

        static DecodedRGBATexture Make(uint64 width, uint64 height, uint8 init = 0) {
            return {
                .data = std::vector<uint8>(width * height * 4, init),
                .width = width, .height = height
            };
        }

        uint64 getIndexBase(uint64 x, uint64 y) const noexcept {
            return (y * width + x) * 4;
        }

        bool valid() const {
            return width > 0 && height > 0 && data.size() == (width * height * 4);
        }

        void fillWithGray(const std::vector<uint8>& gray) {
            if (gray.size() != width * height) throw std::runtime_error("gray data size mismatch");
            ensureDataSize();

            std::fill(data.begin(), data.end(), 255);
            for (uint64 i = 0; i < width * height; ++i) {
                data[i * 4 + 3] = gray[i];
            }
        }

        void fillRGBWhite() {
            ensureDataSize();
            std::fill(data.begin(), data.end(), 255);
            for (uint64 i = 0; i < width * height; ++i) data[i * 4 + 3] = 0;
        }

        void paste(const DecodedRGBATexture& other, int64 x, int64 y) noexcept {
            if (x >= (int64)width || y >= (int64)height) return;
            if (x + other.width < 0 || y + other.height < 0) return;

            for (int64 i = 0; i < (int64)other.width; i++) {
                int64 px = i + x;
                if (px < 0) continue;
                if (px >= (int64)width) break;

                for (int64 j = 0; j < (int64)other.height; j++) {
                    int64 py = j + y;
                    if (py < 0) continue;
                    if (py >= (int64)height) break;

                    auto src_idx = (j * other.width + i) * 4;
                    auto dst_idx = (py * width + px) * 4;

                    float64 src_a = other.data[src_idx + 3] / 255.0;
                    float64 dst_a = data[dst_idx + 3] / 255.0;

                    auto a = src_a + dst_a * (1 - src_a);
                    data[dst_idx + 3] = (uint8)(a * 255);
                    if (data[dst_idx + 3] == 0) continue;

                    for (int64 k = 0; k < 3; k++) {
                        float64 src = other.data[src_idx + k] / 255.0;
                        float64 dst = data[dst_idx + k] / 255.0;
                        auto color = (src * src_a + dst * dst_a * (1 - src_a)) / a;
                        data[dst_idx + k] = (uint8)(color * 255);
                    }
                }
            }
        }

        private:
        void ensureDataSize() {
            data.resize(width * height * 4);
        }
    };
}
