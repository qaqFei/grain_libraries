namespace gcolor {
    using namespace gnumeric::types;

    struct Color {
        float64 r, g, b, a;

        static Color White() noexcept { return Color { 1.0, 1.0, 1.0, 1.0 }; }
        static Color Black() noexcept { return Color { 0.0, 0.0, 0.0, 1.0 }; }
        static Color Red() noexcept { return Color { 1.0, 0.0, 0.0, 1.0 }; }
        static Color Green() noexcept { return Color { 0.0, 1.0, 0.0, 1.0 }; }
        static Color Blue() noexcept { return Color { 0.0, 0.0, 1.0, 1.0 }; }
        static Color Transparent() noexcept { return Color { 0.0, 0.0, 0.0, 0.0 }; }

        static Color FromCss(std::string css) {
            static std::unordered_map<std::string, std::string> colorPresets = {
                { "aliceblue", "#f0f8ff" }, { "antiquewhite", "#faebd7" }, { "aqua", "#00ffff" },
                { "aquamarine", "#7fffd4" }, { "azure", "#f0ffff" }, { "beige", "#f5f5dc" },
                { "bisque", "#ffe4c4" }, { "black", "#000000" }, { "blanchedalmond", "#ffebcd" },
                { "blue", "#0000ff" }, { "blueviolet", "#8a2be2" }, { "brown", "#a52a2a" },
                { "burlywood", "#deb887" }, { "cadetblue", "#5f9ea0" }, { "chartreuse", "#7fff00" },
                { "chocolate", "#d2691e" }, { "coral", "#ff7f50" }, { "cornflowerblue", "#6495ed" },
                { "cornsilk", "#fff8dc" }, { "crimson", "#dc143c" }, { "cyan", "#00ffff" },
                { "darkblue", "#00008b" }, { "darkcyan", "#008b8b" }, { "darkgoldenrod", "#b8860b" },
                { "darkgray", "#a9a9a9" }, { "darkgreen", "#006400" }, { "darkgrey", "#a9a9a9" },
                { "darkkhaki", "#bdb76b" }, { "darkmagenta", "#8b008b" }, { "darkolivegreen", "#556b2f" },
                { "darkorange", "#ff8c00" }, { "darkorchid", "#9932cc" }, { "darkred", "#8b0000" },
                { "darksalmon", "#e9967a" }, { "darkseagreen", "#8fbc8f" }, { "darkslateblue", "#483d8b" },
                { "darkslategray", "#2f4f4f" }, { "darkslategrey", "#2f4f4f" }, { "darkturquoise", "#00ced1" },
                { "darkviolet", "#9400d3" }, { "deeppink", "#ff1493" }, { "deepskyblue", "#00bfff" },
                { "dimgray", "#696969" }, { "dimgrey", "#696969" }, { "dodgerblue", "#1e90ff" },
                { "firebrick", "#b22222" }, { "floralwhite", "#fffaf0" }, { "forestgreen", "#228b22" },
                { "fuchsia", "#ff00ff" }, { "gainsboro", "#dcdcdc" }, { "ghostwhite", "#f8f8ff" },
                { "gold", "#ffd700" }, { "goldenrod", "#daa520" }, { "gray", "#808080" },
                { "green", "#008000" }, { "greenyellow", "#adff2f" }, { "grey", "#808080" },
                { "honeydew", "#f0fff0" }, { "hotpink", "#ff69b4" }, { "indianred", "#cd5c5c" },
                { "indigo", "#4b0082" }, { "ivory", "#fffff0" }, { "khaki", "#f0e68c" },
                { "lavender", "#e6e6fa" }, { "lavenderblush", "#fff0f5" }, { "lawngreen", "#7cfc00" },
                { "lemonchiffon", "#fffacd" }, { "lightblue", "#add8e6" }, { "lightcoral", "#f08080" },
                { "lightcyan", "#e0ffff" }, { "lightgoldenrodyellow", "#fafad2" }, { "lightgray", "#d3d3d3" },
                { "lightgreen", "#90ee90" }, { "lightgrey", "#d3d3d3" }, { "lightpink", "#ffb6c1" },
                { "lightsalmon", "#ffa07a" }, { "lightseagreen", "#20b2aa" }, { "lightskyblue", "#87cefa" },
                { "lightslategray", "#778899" }, { "lightslategrey", "#778899" }, { "lightsteelblue", "#b0c4de" },
                { "lightyellow", "#ffffe0" }, { "lime", "#00ff00" }, { "limegreen", "#32cd32" },
                { "linen", "#faf0e6" }, { "magenta", "#ff00ff" }, { "maroon", "#800000" },
                { "mediumaquamarine", "#66cdaa" }, { "mediumblue", "#0000cd" }, { "mediumorchid", "#ba55d3" },
                { "mediumpurple", "#9370db" }, { "mediumseagreen", "#3cb371" }, { "mediumslateblue", "#7b68ee" },
                { "mediumspringgreen", "#00fa9a" }, { "mediumturquoise", "#48d1cc" }, { "mediumvioletred", "#c71585" },
                { "midnightblue", "#191970" }, { "mintcream", "#f5fffa" }, { "mistyrose", "#ffe4e1" },
                { "moccasin", "#ffe4b5" }, { "navajowhite", "#ffdead" }, { "navy", "#000080" },
                { "oldlace", "#fdf5e6" }, { "olive", "#808000" }, { "olivedrab", "#6b8e23" },
                { "orange", "#ffa500" }, { "orangered", "#ff4500" }, { "orchid", "#da70d6" },
                { "palegoldenrod", "#eee8aa" }, { "palegreen", "#98fb98" }, { "paleturquoise", "#afeeee" },
                { "palevioletred", "#db7093" }, { "papayawhip", "#ffefd5" }, { "peachpuff", "#ffdab9" },
                { "peru", "#cd853f" }, { "pink", "#ffc0cb" }, { "plum", "#dda0dd" },
                { "powderblue", "#b0e0e6" }, { "purple", "#800080" }, { "red", "#ff0000" },
                { "rosybrown", "#bc8f8f" }, { "royalblue", "#4169e1" }, { "saddlebrown", "#8b4513" },
                { "salmon", "#fa8072" }, { "sandybrown", "#f4a460" }, { "seagreen", "#2e8b57" },
                { "seashell", "#fff5ee" }, { "sienna", "#a0522d" }, { "silver", "#c0c0c0" },
                { "skyblue", "#87ceeb" }, { "slateblue", "#6a5acd" }, { "slategray", "#708090" },
                { "slategrey", "#708090" }, { "snow", "#fffafa" }, { "springgreen", "#00ff7f" },
                { "steelblue", "#4682b4" }, { "tan", "#d2b48c" }, { "teal", "#008080" },
                { "thistle", "#d8bfd8" }, { "tomato", "#ff6347" }, { "turquoise", "#40e0d0" },
                { "violet", "#ee82ee" }, { "wheat", "#f5deb3" }, { "white", "#ffffff" },
                { "whitesmoke", "#f5f5f5" }, { "yellow", "#ffff00" }, { "yellowgreen", "#9acd32" },
                { "transparent", "#00000000" },
            };

            std::transform(css.begin(), css.end(), css.begin(), [](unsigned char c){ return std::tolower(c); });
            gstrutils::stripString(css);

            if (colorPresets.find(css) != colorPresets.end()) {
                css = colorPresets.at(css);
            }

            if (gstrutils::stringIsStartsWith(css, "#")) {
                css = gstrutils::stringSlice(css, 1, css.size());
                if (css.size() == 3 || css.size() == 4) css = gstrutils::doubleChars(css);
                if (css.size() == 6) css += "ff";

                float64 ret[4];

                for (uint64 i = 0; i < 4; i++) {
                    try {
                        auto hex = gstrutils::stringSlice(css, i * 2, i * 2 + 2);
                        ret[i] = std::stoi(hex, nullptr, 16);
                    } catch (...) { }
                }

                return Color { ret[0], ret[1], ret[2], ret[3] } / 255;
            }

            auto tryParse = [&](
                std::string css,
                const std::string name,
                uint64 arglen,
                std::optional<std::vector<float64>> maxs = std::nullopt,
                bool funcAllowAlpha = false
            ) -> std::optional<Color> {
                if (!gstrutils::stringIsStartsWith(css, name)) return std::nullopt;
                css = gstrutils::stringSlice(css, name.size(), css.size());

                if (!gstrutils::stringIsStartsWith(css, "(")) return std::nullopt;
                if (!gstrutils::stringIsEndsWith(css, ")")) return std::nullopt;
                css = gstrutils::stringSlice(css, 1, -1);

                css = gstrutils::replaceStringWith(css, " ", ",");
                while (css.find(",,") != std::string::npos) css = gstrutils::replaceStringWith(css, ",,", ",");

                if (css.empty()) return std::nullopt;

                std::vector<std::string> args;
                gstrutils::splitString(css, args, ',');
                std::vector<std::optional<float64>> vals;
                vals.resize(args.size());
                bool hasAlphaArg = false;

                for (uint64 i = 0; i < args.size(); i++) {
                    auto& arg = args[i];
                    if (arg == "/") {
                        hasAlphaArg = true;
                        continue;
                    }

                    if (gstrutils::stringIsEndsWith(arg, "%")) {
                        try {
                            vals[i] = std::stod(gstrutils::stringSlice(arg, 0, -1)) / 100;
                        } catch (...) { return std::nullopt; }

                        if (maxs.has_value() && i < maxs.value().size()) {
                            vals[i].value() *= maxs.value()[i];
                        }
                    } else if (gstrutils::stringIsEndsWith(arg, "deg")) {
                        try {
                            vals[i] = std::stod(gstrutils::stringSlice(arg, 0, -3));
                        } catch (...) { return std::nullopt; }
                    } else {
                        try {
                            vals[i] = std::stod(arg);
                        } catch (...) { return std::nullopt; }
                    }
                }

                bool allowAlpha = funcAllowAlpha && hasAlphaArg;
                std::vector<float64> collected;

                for (uint64 i = 0; i < vals.size(); i++) {
                    if (!vals[i].has_value()) continue;
                    collected.push_back(vals[i].value());
                }

                if (collected.size() != arglen && !allowAlpha) return std::nullopt;
                if (collected.size() != arglen + 1 && allowAlpha) return std::nullopt;

                collected.resize(4);

                if (!allowAlpha && funcAllowAlpha && arglen < 4) {
                    collected[arglen] = 1.0;
                }

                return Color { collected[0], collected[1], collected[2], collected[3] };
            };

            std::optional<Color> ret;

            if ((ret = tryParse(css, "rgb", 3, std::vector<float64> { 255, 255, 255 })).has_value()) {
                auto c = ret.value() / 255.0;
                c.a = 1.0;
                return c.clamp();
            } else if ((ret = tryParse(css, "rgba", 4, std::vector<float64> { 255, 255, 255, 1.0 })).has_value()) {
                return (ret.value() / Color { 255.0, 255.0, 255.0, 1.0 }).clamp();
            } else if ((ret = tryParse(css, "hsl", 3)).has_value()) {
                auto c = ret.value().hsl2rgb();
                c.a = 1.0;
                return c.clamp();
            } else if ((ret = tryParse(css, "hsla", 4)).has_value()) {
                return ret.value().hsl2rgb().clamp();
            } else if ((ret = tryParse(css, "hsv", 3)).has_value()) {
                auto c = ret.value().hsv2rgb();
                c.a = 1.0;
                return c.clamp();
            } else if ((ret = tryParse(css, "hsva", 4)).has_value()) {
                return ret.value().hsv2rgb().clamp();
            } else if ((ret = tryParse(css, "oklch", 3, std::nullopt, true)).has_value()) {
                return ret.value().oklch2rgb().clamp();
            }

            return {};
        }

        Color applyAlpha(float64 alpha) const noexcept { return Color { r, g, b, a * alpha }; }
        Color setAlpha(float64 alpha) const noexcept { return Color { r, g, b, alpha }; }

        Color operator*(const Color& c) const noexcept { return Color { r * c.r, g * c.g, b * c.b, a * c.a }; }
        Color operator*(float64 v) const noexcept { return Color { r * v, g * v, b * v, a * v }; }
        Color operator+(const Color& c) const noexcept { return Color { r + c.r, g + c.g, b + c.b, a + c.a }; }
        Color operator+(float64 v) const noexcept { return Color { r + v, g + v, b + v, a + v }; }
        Color operator-(const Color& c) const noexcept { return Color { r - c.r, g - c.g, b - c.b, a - c.a }; }
        Color operator-(float64 v) const noexcept { return Color { r - v, g - v, b - v, a - v }; }
        Color operator/(const Color& c) const noexcept { return Color { r / c.r, g / c.g, b / c.b, a / c.a }; }
        Color operator/(float64 v) const noexcept { return Color { r / v, g / v, b / v, a / v }; }

        Color& operator*=(const Color& c) noexcept { r *= c.r; g *= c.g; b *= c.b; a *= c.a; return *this; }
        Color& operator*=(float64 v) noexcept { r *= v; g *= v; b *= v; a *= v; return *this; }
        Color& operator+=(const Color& c) noexcept { r += c.r; g += c.g; b += c.b; a += c.a; return *this; }
        Color& operator+=(float64 v) noexcept { r += v; g += v; b += v; a += v; return *this; }
        Color& operator-=(const Color& c) noexcept { r -= c.r; g -= c.g; b -= c.b; a -= c.a; return *this; }
        Color& operator-=(float64 v) noexcept { r -= v; g -= v; b -= v; a -= v; return *this; }
        Color& operator/=(const Color& c) noexcept { r /= c.r; g /= c.g; b /= c.b; a /= c.a; return *this; }
        Color& operator/=(float64 v) noexcept { r /= v; g /= v; b /= v; a /= v; return *this; }

        bool operator==(const Color& c) const noexcept { return r == c.r && g == c.g && b == c.b && a == c.a; }
        bool operator!=(const Color& c) const noexcept { return !(*this == c); }

        Color clamp() const noexcept { return Color { std::clamp(r, 0.0, 1.0), std::clamp(g, 0.0, 1.0), std::clamp(b, 0.0, 1.0), std::clamp(a, 0.0, 1.0) }; }

        Color hsl2rgb() const noexcept {
            auto c = (1.0 - std::abs(2.0 * b - 1.0)) * g;
            auto x = c * (1.0 - std::abs(std::fmod(r / 60.0, 2.0) - 1.0));
            auto m = b - c / 2.0;

            if (0 <= r && r < 60) {
                return Color { c, x, 0.0, 0.0 } + m + Color { 0.0, 0.0, 0.0, a };
            } else if (60 <= r && r < 120) {
                return Color { x, c, 0.0, 0.0 } + m + Color { 0.0, 0.0, 0.0, a };
            } else if (120 <= r && r < 180) {
                return Color { 0.0, c, x, 0.0 } + m + Color { 0.0, 0.0, 0.0, a };
            } else if (180 <= r && r < 240) {
                return Color { 0.0, x, c, 0.0 } + m + Color { 0.0, 0.0, 0.0, a };
            } else if (240 <= r && r < 300) {
                return Color { x, 0.0, c, 0.0 } + m + Color { 0.0, 0.0, 0.0, a };
            } else {
                return Color { c, 0.0, x, 0.0 } + m + Color { 0.0, 0.0, 0.0, a };
            }
        }

        Color hsv2rgb() const noexcept {
            auto c = b * g;
            auto x = c * (1.0 - std::abs(std::fmod(r / 60.0, 2.0) - 1.0));
            auto m = b - c;

            if (0 <= r && r < 60) {
                return Color { c, x, 0.0, 0.0 } + m + Color { 0.0, 0.0, 0.0, a };
            } else if (60 <= r && r < 120) {
                return Color { x, c, 0.0, 0.0 } + m + Color { 0.0, 0.0, 0.0, a };
            } else if (120 <= r && r < 180) {
                return Color { 0.0, c, x, 0.0 } + m + Color { 0.0, 0.0, 0.0, a };
            } else if (180 <= r && r < 240) {
                return Color { 0.0, x, c, 0.0 } + m + Color { 0.0, 0.0, 0.0, a };
            } else if (240 <= r && r < 300) {
                return Color { x, 0.0, c, 0.0 } + m + Color { 0.0, 0.0, 0.0, a };
            } else {
                return Color { c, 0.0, x, 0.0 } + m + Color { 0.0, 0.0, 0.0, a };
            }
        }

        Color oklch2rgb() const noexcept {
            auto a_ = g * std::cos(std::numbers::pi / 180.0 * b);
            auto b_ = g * std::sin(std::numbers::pi / 180.0 * b);

            auto l_ = r + 0.3963377774 * a_ + 0.2158037573 * b_;
            auto m_ = r - 0.1055613458 * a_ - 0.0638541728 * b_;
            auto s_ = r - 0.0894841775 * a_ - 1.2914855480 * b_;

            auto l_cube = l_ * l_ * l_;
            auto m_cube = m_ * m_ * m_;
            auto s_cube = s_ * s_ * s_;
        
            auto r_linear = 4.0767416621 * l_cube - 3.3077115913 * m_cube + 0.2309699292 * s_cube;
            auto g_linear = -1.2684380046 * l_cube + 2.6097574011 * m_cube - 0.3413193965 * s_cube;
            auto b_linear = -0.0041960863 * l_cube - 0.7034186147 * m_cube + 1.7076147010 * s_cube;

            auto to_srgb = [](float64 x) {
                if (x <= 0.0031308) {
                    return 12.92 * x;
                } else {
                    return 1.055 * std::pow(x, 1.0 / 2.4) - 0.055;
                }
            };

            return {
                to_srgb(std::clamp(r_linear, 0.0, 1.0)),
                to_srgb(std::clamp(g_linear, 0.0, 1.0)),
                to_srgb(std::clamp(b_linear, 0.0, 1.0)),
                a
            };
        }
    };

    struct ColorLink {
        std::vector<std::pair<float64, Color>> steps;

        Color get(float64 p) const {
            if (steps.empty()) return {};
            if (p <= steps.front().first) return steps.front().second;
            if (p >= steps.back().first) return steps.back().second;

            for (uint64 i = 0; i < steps.size() - 1; i++) {
                auto& t = steps[i];
                auto& n = steps[i + 1];
                
                if (t.first <= p && p <= n.first) {
                    auto sp = (p - t.first) / (n.first - t.first);
                    return t.second + (n.second - t.second) * sp;
                }
            }

            gassert::assert(false, "ColorLink::get failed");
            return {};
        }
    };
}
