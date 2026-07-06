void entrypoint() {
    using namespace ggeometry;

    Vec2 v(0.5);
    std::cout << "length: " << v.length() << std::endl;

    Rect r(0, 0, 1, 1);
    std::cout << "rextended x: " << r.extend(0.5).x << std::endl;

    Transform2D t {};
    t.translate(0.5, 0.5);
    t.scale(2.0, 2.0);
    std::cout << "transformed x: " << t.transformPoint(v).x << std::endl;

    std::cout << "point is leaving point: " << pointIsLeavingPoint({ 0.2, 0.2 }, -90, { 0.5, 0.5 }) << std::endl;
    std::cout << "point is leaving point: " << pointIsLeavingPoint({ 0.2, 0.2 }, 90, { 0.5, 0.5 }) << std::endl;
}
