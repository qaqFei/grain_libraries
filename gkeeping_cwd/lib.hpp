namespace gkeeping_cwd {
    struct KeepingCWD {
        KeepingCWD() {
            cwd = std::filesystem::current_path();
        }

        ~KeepingCWD() {
            try {
                std::filesystem::current_path(cwd);
            } catch (...) {}
        }

        private:
        std::filesystem::path cwd;
    };
}
