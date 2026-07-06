#ifdef _WIN32
    #include <malloc.h>
#endif

namespace galigned_alloc {
    void* aligned_alloc(size_t alignment, size_t size) {
        #ifdef _WIN32
            return _aligned_malloc(size, alignment);
        #else
            if (alignment < alignof(std::max_align_t)) alignment = alignof(std::max_align_t);
            size = ((size + alignment - 1) / alignment) * alignment;
            return std::aligned_alloc(alignment, size);
        #endif
    }

    void aligned_free(void* ptr) noexcept {
        #ifdef _WIN32
            _aligned_free(ptr);
        #else
            free(ptr);
        #endif
    }

    template <typename T, size_t Alignment = alignof(T)>
    struct AlignedAllocator {
        static_assert(Alignment >= alignof(T), "Alignment must be at least alignof(T)");
        static_assert((Alignment & (Alignment - 1)) == 0, "Alignment must be power of two");

        using value_type = T;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;

        AlignedAllocator() noexcept = default;
        template <typename U> AlignedAllocator(const AlignedAllocator<U, Alignment>&) noexcept {}
        template <typename U> struct rebind { using other = AlignedAllocator<U, Alignment>; };

        [[nodiscard]] T* allocate(size_type n) {
            if (n == 0) return nullptr;
            if (n > std::numeric_limits<size_type>::max() / sizeof(T)) throw std::bad_array_new_length();
            size_type bytes = n * sizeof(T);
            bytes = ((bytes + Alignment - 1) / Alignment) * Alignment;
            void* ptr = aligned_alloc(Alignment, bytes);
            if (!ptr) throw std::bad_alloc();
            return (T*)ptr;
        }

        void deallocate(T* ptr, size_type) noexcept { aligned_free(ptr); }
    };

    template <typename T, size_t A1, typename U, size_t A2>
    bool operator==(const AlignedAllocator<T, A1>&, const AlignedAllocator<U, A2>&) noexcept { return A1 == A2; }
    template <typename T, size_t A1, typename U, size_t A2>
    bool operator!=(const AlignedAllocator<T, A1>&, const AlignedAllocator<U, A2>&) noexcept { return A1 != A2; }
}
