void entrypoint() {
    using namespace gstrutils;

    std::string str = "  Hello, World!  ";
    stripString(str);
    std::cout << "strip: " << str << std::endl;

    std::vector<std::string> lines;
    splitString("a,b,c,123,,456", lines, ',');
    for (auto &line : lines) {
        std::cout << "split: " << line << std::endl;
    }

    std::cout << "sw: " << stringIsStartsWith("ABCd", "AB") << std::endl;
    std::cout << "ew: " << stringIsEndsWith("ABCd", "Cd") << std::endl;
    std::cout << "replace: " << replaceStringWith("abCabab", "ab", "BB") << std::endl;
    std::cout << "slice: " << stringSlice("abcde", 1, 3) << std::endl;
    std::cout << "slice -: " << stringSlice("abcde", 1, -1) << std::endl;
    std::cout << "slice progress: " << stringSliceProgress("1234567890", 0.4) << std::endl;
    std::cout << "double chars: " << doubleChars("abcde") << std::endl;
}
