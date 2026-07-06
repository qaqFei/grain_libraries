namespace gskvcache {
    template <typename T1, typename T2>
    struct SKVCache {
        T1 key;
        T2 value;

        template <typename F>
        [[gnu::always_inline, gnu::hot]]
        const T2& get(const T1& k, F&& reseter) noexcept {
            if (__builtin_expect(key != k, 0)) {
                key = k;
                value = reseter(key);
            }

            return value;
        }
    };
}
