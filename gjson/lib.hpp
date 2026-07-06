namespace gjson {
    using namespace gnumeric::types;

    struct JsonNode {
        enum class EnumType { String, Number, Bool, Array, Object, Null };

        EnumType type;
        std::variant<
            std::monostate,
            std::string,
            float64,
            bool,
            std::vector<JsonNode>,
            std::unordered_map<std::string, JsonNode>
        > value;

        static JsonNode MakeString(const std::string& str) noexcept {
            return JsonNode {
                .type = EnumType::String,
                .value = str
            };
        }

        static JsonNode MakeStringMove(std::string&& str) noexcept {
            return JsonNode {
                .type = EnumType::String,
                .value = std::move(str)
            };
        }

        static JsonNode MakeNumber(float64 num) noexcept {
            return JsonNode {
                .type = EnumType::Number,
                .value = num
            };
        }

        static JsonNode MakeBool(bool b) noexcept {
            return JsonNode {
                .type = EnumType::Bool,
                .value = b
            };
        }

        static JsonNode MakeArray() noexcept {
            return JsonNode {
                .type = EnumType::Array,
                .value = std::vector<JsonNode>()
            };
        }

        static JsonNode MakeArray(const std::vector<JsonNode>& arr) noexcept {
            return JsonNode {
                .type = EnumType::Array,
                .value = arr
            };
        }

        static JsonNode MakeArrayMove(std::vector<JsonNode>&& arr) noexcept {
            return JsonNode {
                .type = EnumType::Array,
                .value = std::move(arr)
            };
        }

        static JsonNode MakeObject() noexcept {
            return JsonNode {
                .type = EnumType::Object,
                .value = std::unordered_map<std::string, JsonNode>()
            };
        }

        static JsonNode MakeObject(const std::unordered_map<std::string, JsonNode>& obj) noexcept {
            return JsonNode {
                .type = EnumType::Object,
                .value = obj
            };
        }

        static JsonNode MakeObjectMove(std::unordered_map<std::string, JsonNode>&& obj) noexcept {
            return JsonNode {
                .type = EnumType::Object,
                .value = std::move(obj)
            };
        }

        static JsonNode MakeNull() noexcept {
            return JsonNode {
                .type = EnumType::Null,
                .value = std::monostate{}
            };
        }

        bool isString() const noexcept { return type == EnumType::String; }
        bool isNumber() const noexcept { return type == EnumType::Number; }
        bool isBool() const noexcept { return type == EnumType::Bool; }
        bool isArray() const noexcept { return type == EnumType::Array; }
        bool isObject() const noexcept { return type == EnumType::Object; }
        bool isNull() const noexcept { return type == EnumType::Null; }

        std::string& getString() noexcept { return std::get<std::string>(value); }
        const std::string& getString() const noexcept { return std::get<std::string>(value); }
        float64 getNumber() const noexcept { return std::get<float64>(value); }
        bool getBool() const noexcept { return std::get<bool>(value); }
        std::vector<JsonNode>& getArray() noexcept { return std::get<std::vector<JsonNode>>(value); }
        const std::vector<JsonNode>& getArray() const noexcept { return std::get<std::vector<JsonNode>>(value); }
        std::unordered_map<std::string, JsonNode>& getObject() noexcept { return std::get<std::unordered_map<std::string, JsonNode>>(value); }
        const std::unordered_map<std::string, JsonNode>& getObject() const noexcept { return std::get<std::unordered_map<std::string, JsonNode>>(value); }
        
        struct StringReader {
            std::string_view str;
            uint64 pos;

            StringReader(std::string_view str) : str(str), pos(0) {}

            void eatWhitespace() {
                while (pos < str.size() && (str[pos] == ' ' || str[pos] == '\n' || str[pos] == '\t' || str[pos] == '\r')) {
                    pos++;
                }
            }

            bool nextIs(const char c) {
                return pos < str.size() && str[pos] == c;
            }

            bool nextIsAny(const std::string& s) {
                for (uint64 i = 0; i < s.size(); i++) {
                    if (nextIs(s[i])) return true;
                }
                return false;
            }

            bool nextIsSub(const std::string& s) {
                return pos + s.size() <= str.size() && str.substr(pos, s.size()) == s;
            }

            bool nextIsSubAny(const std::vector<std::string>& ss) {
                for (const auto& s : ss) {
                    if (nextIsSub(s)) return true;
                }
                return false;
            }

            std::string getNextCharToString() {
                return pos < str.size() ? (std::string() + str[pos++]) : "";
            }

            std::string generatePositionString() {
                return "at " + std::to_string(pos) + " of " + std::to_string(str.size());
            }

            bool eof() {
                return pos >= str.size();
            }

            bool readUnicodeEscape(uint16* dst) {
                if (pos + 4 > str.size()) return false;

                auto c1 = str[pos++];
                auto c2 = str[pos++];
                auto c3 = str[pos++];
                auto c4 = str[pos++];

                if ('0' <= c1 && c1 <= '9') {
                    *dst = (uint16)(c1 - '0') << 12;
                } else if ('A' <= c1 && c1 <= 'F') {
                    *dst = (uint16)(c1 - 'A' + 10) << 12;
                } else if ('a' <= c1 && c1 <= 'f') {
                    *dst = (uint16)(c1 - 'a' + 10) << 12;
                } else return false;

                if ('0' <= c2 && c2 <= '9') {
                    *dst |= (uint16)(c2 - '0') << 8;
                } else if ('A' <= c2 && c2 <= 'F') {
                    *dst |= (uint16)(c2 - 'A' + 10) << 8;
                } else if ('a' <= c2 && c2 <= 'f') {
                    *dst |= (uint16)(c2 - 'a' + 10) << 8;
                } else return false;

                if ('0' <= c3 && c3 <= '9') {
                    *dst |= (uint16)(c3 - '0') << 4;
                } else if ('A' <= c3 && c3 <= 'F') {
                    *dst |= (uint16)(c3 - 'A' + 10) << 4;
                } else if ('a' <= c3 && c3 <= 'f') {
                    *dst |= (uint16)(c3 - 'a' + 10) << 4;
                } else return false;

                if ('0' <= c4 && c4 <= '9') {
                    *dst |= (uint16)(c4 - '0');
                } else if ('A' <= c4 && c4 <= 'F') {
                    *dst |= (uint16)(c4 - 'A' + 10);
                } else if ('a' <= c4 && c4 <= 'f') {
                    *dst |= (uint16)(c4 - 'a' + 10);
                } else return false;

                return true;
            }
            
            std::string getNextToString(uint64 len) {
                return std::string(str.substr(pos, len));
            }

            char getNextChar() {
                return pos < str.size() ? str[pos++] : '\0';
            }
        };

        static JsonNode Parse(StringReader& reader) {
            auto failed = [&](const std::string& err) {
                throw std::runtime_error(std::format("{} at {}", err, reader.generatePositionString()));
            };
            
            reader.eatWhitespace();

            if (reader.nextIs('"')) {
                reader.pos++;
                std::string str;
                str.reserve(64);
                bool isInBackslash = false;

                while (!reader.eof()) {
                    if (reader.nextIs('"') && !isInBackslash) {
                        reader.pos++;
                        str.shrink_to_fit();
                        return MakeStringMove(std::move(str));
                    } else if (reader.nextIs('\\') && !isInBackslash) {
                        isInBackslash = true;
                        reader.pos++;
                    } else if (isInBackslash) {
                        if (reader.nextIsAny("\"\\/")) {
                            str += reader.getNextChar();
                        } else if (reader.nextIs('b')) {
                            str += '\b';
                            reader.pos++;
                        } else if (reader.nextIs('f')) {
                            str += '\f';
                            reader.pos++;
                        } else if (reader.nextIs('n')) {
                            str += '\n';
                            reader.pos++;
                        } else if (reader.nextIs('r')) {
                            str += '\r';
                            reader.pos++;
                        } else if (reader.nextIs('t')) {
                            str += '\t';
                            reader.pos++;
                        } else if (reader.nextIs('u')) {
                            reader.pos++;

                            uint16 u1;
                            if (!reader.readUnicodeEscape(&u1)) failed("invalid unicode escape");

                            uint16 u2 = 0;
                            if (u1 >= 0xD800 && u1 <= 0xDBFF) {
                                if (!reader.nextIsSub("\\u")) failed("expected \\u for surrogate pair");
                                reader.pos += 2;

                                if (!reader.readUnicodeEscape(&u2)) failed("invalid unicode escape");
                                if (u2 < 0xDC00 || u2 > 0xDFFF) failed("invalid surrogate pair");
                            } else if (u1 >= 0xDC00 && u1 <= 0xDFFF) {
                                failed("invalid low surrogate");
                            }

                            str += gutf16c2utf8::utf16c2utf8(u1, u2);
                        } else {
                            failed("unexpected char after backslash");
                        }

                        isInBackslash = false;
                    } else {
                        str += reader.getNextChar();
                    }
                }

                failed("unexpected eof");
            } else if (reader.nextIsAny("0123456789-")) {
                float64 num = 0;
                bool isNegative = reader.nextIs('-');
                if (isNegative) reader.pos++;

                bool afterDot = false;
                uint64 decimal = 1;
                float64 fraction = 0;
                bool hasFraction = false;

                while (!reader.eof()) {
                    uint8 c = reader.getNextChar();

                    if ('0' <= c && c <= '9') {
                        if (!afterDot) {
                            num *= 10;
                            num += (float64)(c - '0');
                        } else {
                            fraction = fraction * 10 + (float64)(c - '0');
                            decimal *= 10;
                            hasFraction = true;
                        }
                    } else if (c == '.') {
                        if (afterDot) failed("unexpected dot");
                        afterDot = true;
                    } else if (c == 'e' || c == 'E') {
                        if (hasFraction) num += fraction / (float64)decimal;
                        
                        bool isNegativeExp = reader.nextIs('-');
                        if (isNegativeExp) reader.pos++;
                        else if (reader.nextIs('+')) reader.pos++;

                        uint64 exp = 0;
                        bool hasExp = false;
                        while (!reader.eof()) {
                            uint8 c = reader.getNextChar();

                            if ('0' <= c && c <= '9') {
                                exp *= 10;
                                exp += (uint64)(c - '0');
                                hasExp = true;
                            } else {
                                reader.pos--;
                                break;
                            }
                        }
                        
                        if (!hasExp) failed("expected exponent digits");

                        if (isNegativeExp) num /= std::pow<float64>(10, exp);
                        else num *= std::pow<float64>(10, exp);
                        return MakeNumber(num * (isNegative ? -1 : 1));
                    } else {
                        reader.pos--;
                        if (hasFraction) num += fraction / (float64)decimal;
                        return MakeNumber(num * (isNegative ? -1 : 1));
                    }
                }
                
                if (hasFraction) num += fraction / (float64)decimal;
                return MakeNumber(num * (isNegative ? -1 : 1));
            } else if (reader.nextIsSubAny({ "true", "false" })) {
                bool b = reader.nextIsSub("true");
                reader.pos += b ? 4 : 5;
                return MakeBool(b);
            } else if (reader.nextIs('[')) {
                reader.pos++;
                std::vector<JsonNode> arr;
                arr.reserve(8);

                while (!reader.eof()) {
                    reader.eatWhitespace();

                    if (reader.nextIs(']')) {
                        reader.pos++;
                        return MakeArrayMove(std::move(arr));
                    }

                    if (arr.size()) {
                        if (!reader.nextIs(',')) failed("expected comma");
                        reader.pos++;
                        reader.eatWhitespace();
                    }

                    auto node = Parse(reader);
                    arr.push_back(std::move(node));
                }

                failed("unexpected eof");
            } else if (reader.nextIs('{')) {
                reader.pos++;
                std::unordered_map<std::string, JsonNode> obj;
                obj.reserve(8);

                while (!reader.eof()) {
                    reader.eatWhitespace();

                    if (reader.nextIs('}')) {
                        reader.pos++;
                        return MakeObjectMove(std::move(obj));
                    }

                    if (obj.size()) {
                        if (!reader.nextIs(',')) failed("expected comma");
                        reader.pos++;
                        reader.eatWhitespace();
                    }

                    auto key = Parse(reader);
                    if (!key.isString()) failed("expected string");

                    reader.eatWhitespace();
                    if (!reader.nextIs(':')) failed("expected colon");
                    reader.pos++;
                    reader.eatWhitespace();

                    auto value = Parse(reader);
                    obj.emplace(std::move(key.getString()), std::move(value));
                }

                failed("unexpected eof");
            } else if (reader.nextIsSub("null")) {
                reader.pos += 4;
                return MakeNull();
            }

            failed("unexpected char");
            return MakeNull();
        }

        static JsonNode Parse(const gdata::Data& data) {
            StringReader reader(std::string_view(
                (const char*)data.data.data(),
                data.data.size()
            ));
            return Parse(reader);
        }

        template<typename T>
        void print(T& stream) const {
            if (isString()) {
                stream << '"';
                for (uint8 c : getString()) {
                    if (c == '"') stream << "\\\"";
                    else if (c == '\\') stream << "\\\\";
                    else if (c == '\n') stream << "\\n";
                    else if (c == '\r') stream << "\\r";
                    else if (c == '\t') stream << "\\t";
                    else if (c == '\b') stream << "\\b";
                    else if (c == '\f') stream << "\\f";
                    else stream << c;
                }
                stream << '"';
            } else if (isNumber()) {
                auto number = getNumber();
                stream << (std::fmod(number, 1.0) != 0.0 ? std::format("{:.10g}", number) : std::to_string((int64)number));
            } else if (isBool()) stream << (getBool() ? "true" : "false");
            else if (isArray()) {
                stream << '[';
                for (uint64 i = 0; i < getArray().size(); i++) {
                    if (i) stream << ',';
                    getArray()[i].print(stream);
                }
                stream << ']';
            } else if (isObject()) {
                stream << '{';
                uint64 i = 0;
                for (auto& [key, value] : getObject()) {
                    JsonNode::MakeString(key).print(stream);
                    stream << ':';
                    value.print(stream);
                    if (i < getObject().size() - 1) stream << ',';
                    i++;
                }
                stream << '}';
            } else if (isNull()) stream << "null";
        }

        void print() const { print(std::cout); }

        std::string toString() const {
            std::string result;
            result.reserve(256);
            toStringImpl(result);
            return result;
        }
        
        bool operator==(const JsonNode& other) const {
            if (type != other.type) return false;
            if (type == EnumType::Null) return true;
            if (type == EnumType::String) return getString() == other.getString();
            if (type == EnumType::Number) return getNumber() == other.getNumber();
            if (type == EnumType::Bool) return getBool() == other.getBool();
            if (type == EnumType::Array) {
                if (getArray().size() != other.getArray().size()) return false;
                for (uint32 i = 0; i < getArray().size(); i++) {
                    if (getArray()[i] != other.getArray()[i]) return false;
                }
                return true;
            }
            if (type == EnumType::Object) {
                if (getObject().size() != other.getObject().size()) return false;
                for (auto& [key, value] : getObject()) {
                    if (value != other[key]) return false;
                }
                return true;
            }
            return false;
        }

        bool operator!=(const JsonNode& other) const { return !(*this == other); }

        JsonNode operator[](uint64 index) const noexcept {
            return getArray()[index];
        }

        JsonNode operator[](const std::string& key) const noexcept {
            auto it = getObject().find(key);
            if (it != getObject().end()) return it->second;
            return MakeNull();
        }

        JsonNode& operator[](uint64 index) noexcept {
            auto& arr = getArray();
            return arr[index];
        }

        JsonNode& operator[](const std::string& key) noexcept {
            auto& obj = getObject();
            return obj[key];
        }

        bool hasKey(const std::string& key) const {
            if (type != EnumType::Object) return false;
            return getObject().contains(key);
        }

    private:
        void toStringImpl(std::string& out) const {
            if (isString()) {
                out += '"';
                for (uint8 c : getString()) {
                    if (c == '"') out += "\\\"";
                    else if (c == '\\') out += "\\\\";
                    else if (c == '\n') out += "\\n";
                    else if (c == '\r') out += "\\r";
                    else if (c == '\t') out += "\\t";
                    else if (c == '\b') out += "\\b";
                    else if (c == '\f') out += "\\f";
                    else out += c;
                }
                out += '"';
            } else if (isNumber()) out += std::format("{:.10g}", getNumber());
            else if (isBool()) out += (getBool() ? "true" : "false");
            else if (isArray()) {
                out += '[';
                for (uint64 i = 0; i < getArray().size(); i++) {
                    if (i) out += ',';
                    getArray()[i].toStringImpl(out);
                }
                out += ']';
            } else if (isObject()) {
                out += '{';
                uint64 i = 0;
                for (auto& [key, value] : getObject()) {
                    out += '"';
                    out += key;
                    out += "\":";
                    value.toStringImpl(out);
                    if (i < getObject().size() - 1) out += ',';
                    i++;
                }
                out += '}';
            } else if (isNull()) out += "null";
        }
    };
}
