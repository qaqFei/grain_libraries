void entrypoint() {
    using gshared_memory::SharedMemory;

    const char* name = "/gshared_memory_test";

    if (gshared_memory::isExists(name)) {
        std::cout << "exists" << std::endl;

        auto mem = SharedMemory::Open(name);
        std::cout << "opened" << std::endl;

        std::cout << "read: " << *(int*)mem->getPtr() << std::endl;
    } else {
        std::cout << "not exists" << std::endl;

        auto mem = SharedMemory::Create(name, 1024);
        std::cout << "created 1kb shared memory" << std::endl;

        *(int*)mem->getPtr() = 42;
        std::cout << "wrote 42" << std::endl;

        std::cout << "enter to exit" << std::endl;
        std::cin.get();
    }
}
