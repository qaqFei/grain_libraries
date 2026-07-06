using namespace gnumeric::types;

std::string foo(int64 v) {
    std::cout << "reset: " << v << std::endl;
    return std::to_string(v * 2);
}

void entrypoint() {
    gskvcache::SKVCache<int64, std::string> cache;
    
    std::cout << cache.get(1, foo) << std::endl;
    std::cout << cache.get(2, foo) << std::endl;
    std::cout << cache.get(2, foo) << std::endl;
    std::cout << cache.get(3, foo) << std::endl;
}
