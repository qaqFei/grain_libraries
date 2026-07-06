#include <gtext_renderer/stb_truetype.h>

namespace gtext_renderer {
    using namespace gnumeric::types;
    using gsp::gsp;
    using gdecoded_rgba_texture::DecodedRGBATexture;
    using gdata::Data;

    struct TextRenderer {
        TextRenderer() = default;
        TextRenderer(const TextRenderer&) = delete;
        TextRenderer& operator=(const TextRenderer&) = delete;

        static gsp<TextRenderer> Make() {
            auto* tr = new TextRenderer();
            return gsp<TextRenderer>(tr);
        }

        void loadFont(const Data& data, uint64 index = 0) {
            fontData = data;
            if (!stbtt_InitFont(&font, fontData.data.data(), stbtt_GetFontOffsetForIndex(fontData.data.data(), index))) {
                throw std::runtime_error("failed to load font");
            }
        }

        DecodedRGBATexture render(const std::string& text, uint64 fontSize) {
            struct DrawedChar {
                DecodedRGBATexture tex;
                int32 xoff, yoff;
                float64 advance_width;
            };

            std::vector<DrawedChar> chars;

            auto scale = stbtt_ScaleForPixelHeight(&font, fontSize);

            for (uint64 i = 0; i < text.size(); i++) {
                uint64 codepoint = 0;
                uint8 bytes = 0;

                auto c = text[i];
                if ((c & 0x80) == 0) {
                    codepoint = c;
                    bytes = 1;
                } else if ((c & 0xE0) == 0xC0) {
                    codepoint = c & 0x1F;
                    bytes = 2;
                } else if ((c & 0xF0) == 0xE0) {
                    codepoint = c & 0x0F;
                    bytes = 3;
                } else if ((c & 0xF8) == 0xF0) {
                    codepoint = c & 0x07;
                    bytes = 4;
                }

                if (i + bytes > text.size()) break;

                for (uint8 j = 1; j < bytes; j++) {
                    codepoint = (codepoint << 6) | (text[i + j] & 0x3F);
                }

                i += bytes - 1;

                auto glyph_index = stbtt_FindGlyphIndex(&font, codepoint);
                if (!glyph_index) glyph_index = stbtt_FindGlyphIndex(&font, '?');
                if (!glyph_index) continue;

                auto& dc = chars.emplace_back();

                int32 advance, lsb;
                stbtt_GetGlyphHMetrics(&font, glyph_index, &advance, &lsb);
                dc.advance_width = advance * scale;

                int32 w, h;
                stbtt_GetGlyphBitmapBox(&font, glyph_index, scale, scale, &dc.xoff, &dc.yoff, &w, &h);
                w -= dc.xoff; h -= dc.yoff;

                std::vector<uint8> bitmap(w * h);
                stbtt_MakeGlyphBitmap(&font, bitmap.data(), w, h, w, scale, scale, glyph_index);

                dc.tex = DecodedRGBATexture::Make(w, h);
                dc.tex.fillWithGray(bitmap);
            }

            if (chars.empty()) return DecodedRGBATexture::Make(2, 2);

            int32 top = 0, bottom = 0;
            float64 width = 0, real_right = 0;

            for (auto& dc : chars) {
                top = std::min(top, dc.yoff);
                bottom = std::max<int32>(bottom, dc.yoff + dc.tex.height);
                real_right = std::max(real_right, width + dc.xoff + dc.tex.width);
                width += dc.advance_width;
                real_right = std::max(real_right, width);
            }

            int32 padding = 2;
            int32 iwidth = std::ceil(real_right - chars.front().xoff + padding * 2);

            if (top >= bottom || iwidth <= 0) return DecodedRGBATexture::Make(2, 2);

            auto tex = DecodedRGBATexture::Make(iwidth, bottom - top);
            tex.fillRGBWhite();

            float64 x = -chars.front().xoff + padding;

            for (auto& dc : chars) {
                int64 y = dc.yoff - top;
                int64 ix = std::ceil(x + dc.xoff);
                tex.paste(dc.tex, ix, y);
                x += dc.advance_width;
            }

            return tex;
        }

        private:
        Data fontData;
        stbtt_fontinfo font;
    };
}
