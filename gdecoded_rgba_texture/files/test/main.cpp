void entrypoint() {
    auto tex = gdecoded_rgba_texture::DecodedRGBATexture::Make(512, 512);
    std::cout << &tex << ": " << tex.width << "x" << tex.height << std::endl;
}
