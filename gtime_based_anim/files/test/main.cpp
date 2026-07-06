void entrypoint() {
    gtime_based_anim::TimeBasedAnim anim {
        .duration = 0.5
    };

    std::cout << anim.get(0.0) << std::endl;

    anim.set(0.3, 5.0);
    std::cout << anim.get(0.45) << std::endl;

    anim.set(0.65, 2.5);
    std::cout << anim.get(1.0) << std::endl;
}
