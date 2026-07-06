namespace gassert {
    #ifdef GRAIN_IS_RELEASE
        void assert(bool, const std::string&) noexcept {}
    #else
        void assert(bool condition, const std::string& msg) {
            if (!condition) {
                std::cerr << "Assertion failed: " << msg << std::endl;
                std::abort();
            }
        }
    #endif
}
