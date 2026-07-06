void entrypoint() {
    using gdata::Data;

    auto data = Data::MakeFromFile("./lib.hpp");
    std::cout << data.toString() << std::endl;

    std::cout << "from grain: " << Data::MakeFromGrain("test/test").toString() << std::endl;
}
