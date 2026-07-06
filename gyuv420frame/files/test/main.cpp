void entrypoint() {
    auto frame = gyuv420frame::YUV420Frame::Make(512, 512);
    std::cout << frame.get() << ": " << frame->width << "x" << frame->height << " u: " << (void*)frame->u() << std::endl;
}
