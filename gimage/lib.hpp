#include <gimage/stb_image.h>

namespace gimage {
    using namespace gnumeric::types;
    using gdecoded_rgba_texture::DecodedRGBATexture;

    DecodedRGBATexture decode(const gdata::Data& data) {
        int width, height, channels;
        uint8* pixels = stbi_load_from_memory(
            data.data.data(),
            data.data.size(),
            &width, &height, &channels,
            4
        );

        if (!pixels) {
            throw std::runtime_error("failed to decode image");
        }

        DecodedRGBATexture tex {
            .data = std::vector<uint8>(pixels, pixels + width * height * 4),
            .width = (uint64)width,
            .height = (uint64)height
        };

        stbi_image_free(pixels);
        return tex;
    }
}
