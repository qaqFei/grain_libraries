struct A {
    int a, b;

    ~A() {
        std::cout << "~A" << std::endl;
    }
};

void entrypoint() {
    using gsp::gsp;

    auto* p = new A {1, 2};
    auto sp = gsp(p);

    sp->a = 3; sp->b = 4;
    std::cout << sp->a << " " << sp->b << std::endl;

    auto sp2 = sp;
    sp2->a = 5; sp2->b = 6;
    std::cout << sp->a << " " << sp->b << std::endl;
}
