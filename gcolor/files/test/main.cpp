void entrypoint() {
    using namespace gcolor;

    auto p = [](Color c) { std::cout << c.r << "," << c.g << "," << c.b << "," << c.a << std::endl; };

    Color c {}; p(c);
    c = Color::Red(); p(c);
    c = Color::FromCss("aliceblue"); p(c);
    c = Color::FromCss("#ff00ff"); p(c);
    c = Color::FromCss("rgb(255, 0, 255)"); p(c);
    c = Color::FromCss("oklch(0.5, 0.5, 0.5)"); p(c);
    c = Color::Red().applyAlpha(0.4); p(c);
    c = Color::Red() * 0.5; p(c);

    ColorLink link;
    link.steps.push_back({ 0.0, Color::Red() });
    link.steps.push_back({ 0.5, Color::Blue() });
    link.steps.push_back({ 1.0, Color::Green() });
    p(link.get(0.0));
    p(link.get(0.3));
    p(link.get(0.7));
    p(link.get(1.7));
}
