namespace gtime {
    using namespace gnumeric::types;

    float64 steady() noexcept {
        return std::chrono::duration<float64>(
            std::chrono::steady_clock::now()
            .time_since_epoch()
        ).count();
    }

    struct Timer {
        float64 start;
        Timer() : start(steady()) {}
        float64 elapsed() const noexcept { return steady() - start; }
    };
}
