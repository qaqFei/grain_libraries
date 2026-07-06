#ifdef _WIN32
    #include <windows.h>
#endif

void entrypoint() {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif

    std::cout << gutf16c2utf8::utf16c2utf8(0xD83D, 0xDE00) << std::endl;
}
