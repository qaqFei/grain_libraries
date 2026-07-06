void entrypoint() {
    auto data = gdata::Data::MakeFromGrain("test/test_image");
    auto img = gimage::decode(data);
    std::cout << &img << ": " << img.width << "x" << img.height << std::endl;
}
