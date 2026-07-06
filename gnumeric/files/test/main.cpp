void entrypoint() {
    using namespace gnumeric::types;

    uint16 v = 65535;
    std::cout << "v: " << v << std::endl;

    v++;
    std::cout << "v: " << v << std::endl; // overflow

    std::cout << "clamp: " << gnumeric::utils::clamp<uint16, uint32>(9999999) << std::endl;
}
