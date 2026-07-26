void entrypoint() {
    using namespace gshm_socket;
    using namespace gnumeric::types;

    const char* name = "/gshm_socket_test";

    try {
        auto server = Server::Make(name, [](const void* ptr, uint64 size) {
            std::cout << "server received: " << std::string((const char*)ptr, size) << std::endl;
        });

        std::cout << "server created" << std::endl;

        std::thread([&]() {
            std::string msg;

            while (true) {
                std::cout << ">> ";
                std::cin >> msg;

                if (msg == ".shutdown") {
                    server->shutdown();
                    return;
                }

                server->send(msg.c_str(), msg.size());
            }
        }).detach();

        while (!server->getShutdown()) {
            server->recv();
        }

        std::cout << "server shutdown" << std::endl;
    } catch (...) {
        auto client = Client::Make(name, [](const void* ptr, uint64 size) {
            std::cout << "client received: " << std::string((const char*)ptr, size) << std::endl;
        });

        std::cout << "client created" << std::endl;

        std::thread([&]() {
            std::string msg;

            while (true) {
                std::cout << ">> ";
                std::cin >> msg;
                client->send(msg.c_str(), msg.size());
            }
        }).detach();

        while (!client->getShutdown()) {
            client->recv();
        }

        std::cout << "server shutdown" << std::endl;
    }
}
