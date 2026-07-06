void entrypoint() {
    ghash_bucket::Bucket buk;

    buk.submitNumber(1);
    std::cout << buk.hash << std::endl;

    buk.submitOptionalNumber<gnumeric::types::uint16>(std::nullopt);
    std::cout << buk.hash << std::endl;

    buk.submitBool(true);
    std::cout << buk.hash << std::endl;
}
