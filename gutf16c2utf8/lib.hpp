namespace gutf16c2utf8 {
    using namespace gnumeric::types;

    std::string utf16c2utf8(uint16 n, uint16 n2 = 0) {
        uint32 codepoint;
        
        if (n >= 0xD800 && n <= 0xDBFF) {
            if (n2 >= 0xDC00 && n2 <= 0xDFFF) {
                codepoint = 0x10000 + ((n - 0xD800) << 10) | (n2 - 0xDC00);
            } else {
                return "\xEF\xBF\xBD";
            }
        } else if (n >= 0xDC00 && n <= 0xDFFF) {
            return "\xEF\xBF\xBD";
        } else {
            codepoint = n;
        }
        
        std::string result;
        
        if (codepoint <= 0x7F) {
            result.push_back((char)(codepoint));
        } 
        else if (codepoint <= 0x7FF) {
            result.push_back((char)(0xC0 | (codepoint >> 6)));
            result.push_back((char)(0x80 | (codepoint & 0x3F)));
        } 
        else if (codepoint <= 0xFFFF) {
            result.push_back((char)(0xE0 | (codepoint >> 12)));
            result.push_back((char)(0x80 | ((codepoint >> 6) & 0x3F)));
            result.push_back((char)(0x80 | (codepoint & 0x3F)));
        } 
        else {
            result.push_back((char)(0xF0 | (codepoint >> 18)));
            result.push_back((char)(0x80 | ((codepoint >> 12) & 0x3F)));
            result.push_back((char)(0x80 | ((codepoint >> 6) & 0x3F)));
            result.push_back((char)(0x80 | (codepoint & 0x3F)));
        }
        
        return result;
    }
}
