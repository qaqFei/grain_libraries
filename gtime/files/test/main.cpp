void entrypoint() {
    std::cout << "current time: " << gtime::steady() << std::endl;
    
    gtime::Timer timer;
    while (timer.elapsed() < 2.0) {
        std::cout << "elapsed time: " << timer.elapsed() << std::endl;
    }
}
