namespace gassert {
    #ifdef GRAIN_IS_RELEASE
        void asrt(bool, const std::string&) noexcept {}
    #else
        void asrt(bool condition, const std::string& msg) {
            if (!condition) {
                std::cerr << std::format("Assertion failed ({}:{}): {}", __FILE__, __LINE__, msg) << std::endl;
                std::abort();
            }
        }
    #endif
}
