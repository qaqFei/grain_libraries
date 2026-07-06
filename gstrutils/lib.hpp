namespace gstrutils {
    using namespace gnumeric::types;

    void stripString(std::string& str) {
        auto not_space = [](unsigned char ch) { return !std::isspace(ch); };
        auto tail = std::ranges::find_if(str | std::views::reverse, not_space);
        str.erase(tail.base(), str.end());
        auto head = std::ranges::find_if(str, not_space);
        str.erase(str.begin(), head);
    }

    void splitString(const std::string& str, std::vector<std::string>& lines, char delimiter = '\n') {
        for (auto&& subrange : str | std::views::split(delimiter)) {
            lines.emplace_back(subrange.begin(), subrange.end());
        }
    }

    bool stringIsStartsWith(const std::string& str, const std::string& prefix) {
        return str.size() >= prefix.size() && str.substr(0, prefix.size()) == prefix;
    }

    bool stringIsEndsWith(const std::string& str, const std::string& suffix) {
        return str.size() >= suffix.size() && str.substr(str.size() - suffix.size()) == suffix;
    }

    std::string replaceStringWith(const std::string& str, const std::string& target, const std::string& replacement) {
        if (target.empty()) return str;

        std::string result;
        size_t start = 0;
        size_t pos;
        while ((pos = str.find(target, start)) != std::string::npos) {
            result.append(str, start, pos - start);
            result.append(replacement);
            start = pos + target.size();
        }
        result.append(str, start, std::string::npos);
        return result;
    }

    std::string stringSlice(const std::string& str, int64 start, int64 end) {
        int64 len = str.size();
        if (start < 0) start = std::max<int64>(0, len + start);
        else start = std::min(start, len);
        if (end < 0) end = std::max<int64>(0, len + end);
        else end = std::min(end, len);
        if (start >= end) return "";
        return str.substr(start, end - start);
    }

    std::string stringSliceProgress(const std::string& str, float64 p) {
        p = std::clamp(p, 0.0, 1.0);
        return str.substr(0, (uint64)(str.size() * p));
    }

    std::string doubleChars(const std::string& str) {
        std::string result;
        result.reserve(str.size() * 2);
        for (auto c : str) result.append(2, c);
        return result;
    }
}
