namespace gframerate_meter {
    using namespace gnumeric::types;

    struct FramerateMeter {
        void frame() {
            auto now = gtime::steady();
            timestamps.push_back(now);
            auto threshold = now - windowSize;
            while (!timestamps.empty() && timestamps.front() < threshold) {
                timestamps.pop_front();
            }
        }

        float64 get() const {
            if (timestamps.size() < 2) return 0.0;
            float64 delta = timestamps.back() - timestamps.front();
            if (delta <= 0.0) return 0.0;
            return (timestamps.size() - 1) / delta;
        }

    private:
        std::deque<float64> timestamps;
        const float64 windowSize = 0.5;
    };
}
