void entrypoint() {
    using namespace gglfw3;
    using namespace gopengl::GL;

    auto win = Window::Make();
    win->hint330Core()->hintMsaa(4);
    win->create();

    auto gl = MakeGL33CoreInterface(getProcAddress);
    std::cout << "gl version: " << gl.glGetString(GL_VERSION) << std::endl;

    auto ctx = GL33Context::Make(gl);
    auto cvs = GL33Canvas::Make(ctx.get());
    
    auto image = ctx->createTextureFromDecoded(gimage::decode(gdata::Data::MakeFromGrain("test/test_image")));
    ctx->gaussianBlurToTexture(image.get(), 20.0);

    while (!win->shouldClose()) {
        ctx->setViewport(win->getSize());
        ctx->gl.glClearColor(1.0, 1.0, 1.0, 1.0);
        ctx->gl.glClear(GL_COLOR_BUFFER_BIT);

        cvs.save();
        cvs.translate({ 200.0, 100.0 });
        cvs.rotateDegrees(45.0 + gtime::steady() * 90.0);
        cvs.drawRect({
            .size = { 256.0, 277.0 },
            .texture = image.get()
        });
        cvs.restore();

        cvs.save();
        cvs.translate({ 200.0, 100.0 });
        cvs.rotateDegrees(gtime::steady() * 180.0);
        cvs.drawRect({
            .position = { -1000.0, -2.5 },
            .size = { 2000.0, 5.0 },
            .color = { 0.0, 0.0, 0.0, 1.0 }
        });
        cvs.restore();

        cvs.save();
        cvs.translate({ 200.0, 200.0 });
        cvs.rotateDegrees(gtime::steady() * 250.0);
        cvs.drawRect({
            .position = { -1000.0, -5.0 },
            .size = { 2000.0, 10.0 },
            .color = { 0.5, 0.5, 0.8, 1.0 }
        });
        cvs.restore();

        pollEvents();
        win->swapBuffers();
    }
}
