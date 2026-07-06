template <typename T, size_t Alignment>
using aligned_vector = std::vector<T, galigned_alloc::AlignedAllocator<T, Alignment>>;

void entrypoint() {
    aligned_vector<int, 16> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    std::cout << vec[0] << std::endl;
    std::cout << vec[1] << std::endl;
    std::cout << vec[2] << std::endl;
    std::cout << "ptr: " << &vec[0] << std::endl;
}
