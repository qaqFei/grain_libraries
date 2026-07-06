namespace galigned_stl {
    using galigned_alloc::AlignedAllocator;
    
    template <typename T, size_t Alignment>
    using aligned_vector = std::vector<T, AlignedAllocator<T, Alignment>>;

    template <typename T, size_t Alignment>
    using aligned_list = std::list<T, AlignedAllocator<T, Alignment>>;

    template <typename T, size_t Alignment>
    using aligned_deque = std::deque<T, AlignedAllocator<T, Alignment>>;

    template <typename T, size_t Alignment>
    using aligned_forward_list = std::forward_list<T, AlignedAllocator<T, Alignment>>;
    
    template <typename Key, typename Value, size_t Alignment>
    using aligned_map = std::map<Key, Value, std::less<Key>, AlignedAllocator<std::pair<const Key, Value>, Alignment>>;

    template <typename Key, typename Value, size_t Alignment>
    using aligned_multimap = std::multimap<Key, Value, std::less<Key>, AlignedAllocator<std::pair<const Key, Value>, Alignment>>;

    template <typename Key, size_t Alignment>
    using aligned_set = std::set<Key, std::less<Key>, AlignedAllocator<Key, Alignment>>;

    template <typename Key, size_t Alignment>
    using aligned_multiset = std::multiset<Key, std::less<Key>, AlignedAllocator<Key, Alignment>>;
    
    template <typename Key, typename Value, size_t Alignment>
    using aligned_unordered_map = std::unordered_map<Key, Value, std::hash<Key>, std::equal_to<Key>, AlignedAllocator<std::pair<const Key, Value>, Alignment>>;

    template <typename Key, typename Value, size_t Alignment>
    using aligned_unordered_multimap = std::unordered_multimap<Key, Value, std::hash<Key>, std::equal_to<Key>, AlignedAllocator<std::pair<const Key, Value>, Alignment>>;

    template <typename Key, size_t Alignment>
    using aligned_unordered_set = std::unordered_set<Key, std::hash<Key>, std::equal_to<Key>, AlignedAllocator<Key, Alignment>>;

    template <typename Key, size_t Alignment>
    using aligned_unordered_multiset = std::unordered_multiset<Key, std::hash<Key>, std::equal_to<Key>, AlignedAllocator<Key, Alignment>>;
}
