namespace ghash_bucket {
    using namespace gnumeric::types;

    struct Bucket {
        uint64 hash = 0xcbf29ce484222325ULL;
        
        static constexpr uint64 FNV_PRIME = 0x100000001b3ULL;
        
        void mix(uint64 value) noexcept {
            hash ^= value;
            hash *= FNV_PRIME;
        }
        
        template <typename T>
        void submitNumber(T v) noexcept {
            static_assert(std::is_arithmetic_v<T>, "T must be numeric");
            
            if constexpr (std::is_floating_point_v<T>) {
                if (v == 0) v = std::copysign(0.0, 1.0);
            }
            
            const uint8* bytes = reinterpret_cast<const uint8*>(&v);
            for (uint64 i = 0; i < sizeof(T); i++) {
                mix(bytes[i]);
            }
        }
        
        void submitBool(bool b) noexcept { mix(b ? 1 : 0); }

        template <typename T>
        void submitOptionalNumber(std::optional<T> v) noexcept {
            if (v.has_value()) {
                submitBool(true);
                submitNumber(v.value());
            } else submitBool(false);
        }
    };
}
