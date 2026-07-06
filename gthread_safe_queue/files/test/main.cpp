void entrypoint() {
    gthread_safe_queue::ThreadSafeQueue<int> q;
    
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    std::cout << "size: " << q.size_approx() << std::endl;

    std::thread([&q]() {
        std::thread([&q]() {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            q.shutdown();
        }).detach();

        while (true) {
            int v;
            if (q.wait_dequeue(v)) {
                std::cout << "dequeue: " << v << std::endl;
            } else {
                std::cout << "shutdown" << std::endl;
                break;
            }
        }
    }).join();
}
