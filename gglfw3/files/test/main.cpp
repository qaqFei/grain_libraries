void entrypoint() {
    using namespace gglfw3;

    gframerate_meter::FramerateMeter frMeter;

    auto win = Window::Make();
    win->create();

    while (!win->shouldClose()) {
        pollEvents();
        win->swapBuffers();
        
        frMeter.frame();
        std::cout << frMeter.get() << std::endl;
    }
}
