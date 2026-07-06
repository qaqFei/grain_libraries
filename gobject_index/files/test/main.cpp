void entrypoint() {
    using namespace gobject_index;

    ObjectIndexer indexer;
    std::cout << indexer.get() << std::endl;
    std::cout << indexer.get() << std::endl;

    ObjectIndexGenerator<int> gen;
    std::cout << gen.get(1) << std::endl;
    std::cout << gen.get(2) << std::endl;
    std::cout << gen.get(1) << std::endl;
    std::cout << gen.get(3) << std::endl;
}
