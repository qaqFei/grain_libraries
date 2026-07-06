void entrypoint() {
    gframerate_meter::FramerateMeter meter;

    while (true) {
        meter.frame();
        std::cout << meter.get() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
