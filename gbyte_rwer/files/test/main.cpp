void entrypoint() {
    using namespace gbyte_rwer;
    using namespace gnumeric::types;

    auto writer = ByteWriter<ByteEndian::Little>::Make();
    writer->writeBytes("Hello, world!");
    writer->write<uint64>(1234567890);
    writer->write<uint8>(42);

    auto data = writer->toData();
    std::cout << data.toString() << std::endl;
}
