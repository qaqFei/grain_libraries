namespace gobject_index {
    using namespace gnumeric::types;

    static std::atomic<uint64> _counter = 1;
    uint64 _reqCounter() noexcept { return _counter++; }

    struct ObjectIndexer {
        uint64 index;

        uint64 get() noexcept {
            return index ? index : (index = _reqCounter());
        }

        void set(uint64 given) noexcept {
            index = given;
        }
    };

    template <typename T>
    struct ObjectIndexGenerator {
        uint64 get(const T& key) noexcept {
            auto it = map.find(key);
            if (it == map.end()) {
                return map[key] = _reqCounter();
            }
            return it->second;
        }

        private:
        std::map<T, uint64> map;
    };
}
