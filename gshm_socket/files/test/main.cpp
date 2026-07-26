using namespace gnumeric::types;

void entrypoint() {
    const char* name = "/gshm_socket_test";

    try {
        auto server = gshm_socket::Server::Make(name, [](const void* ptr, uint64 size) {
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

        server->runForever();
        std::cout << "server shutdown" << std::endl;
    } catch (...) {
        auto client = gshm_socket::Client::Make(name, [](const void* ptr, uint64 size) {
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

        client->runForever();
        std::cout << "server shutdown" << std::endl;
    }
}

static std::unordered_map<uint64, gsp::gsp<gshm_socket::Server>> servers;
static std::unordered_map<uint64, gsp::gsp<gshm_socket::Client>> clients;

bool writeStringToBuffer(const std::string& str, char* buffer, uint64 bufferSize, uint64* sizeDst) {
    *sizeDst = str.size();
    if (str.size() > bufferSize) return false;
    std::copy(str.begin(), str.end(), buffer);
    return true;
}

extern "C" GRAIN_EXPORT void* createServer(
    const char* name,
    void (*callback)(void*, const void*, uint64), void* userdata,
    bool* success
) {
    try {
        auto server = gshm_socket::Server::Make(name, [callback, userdata](const void* ptr, uint64 size) { callback(userdata, ptr, size); });
        *success = true;
        return (servers[(uint64)server.get()] = server).get();
    } catch (...) { }

    *success = false;
    return nullptr;
}

extern "C" GRAIN_EXPORT bool serverGetName(void* server, char* buffer, uint64 bufferSize, uint64* size) { return writeStringToBuffer(servers[(uint64)server]->getName(), buffer, bufferSize, size); }
extern "C" GRAIN_EXPORT bool serverGetShutdown(void* server) { return servers[(uint64)server]->getShutdown(); }
extern "C" GRAIN_EXPORT void serverSend(void* server, const void* data, uint64 size) { servers[(uint64)server]->send(data, size); }
extern "C" GRAIN_EXPORT void serverRecv(void* server) { servers[(uint64)server]->recv(); }
extern "C" GRAIN_EXPORT void serverShutdown(void* server) { servers[(uint64)server]->shutdown(); }
extern "C" GRAIN_EXPORT void destroyServer(void* server) { servers.erase((uint64)server); }

extern "C" GRAIN_EXPORT void* createClient(
    const char* name,
    void (*callback)(void*, const void*, uint64), void* userdata,
    bool* success
) {
    try {
        auto client = gshm_socket::Client::Make(name, [callback, userdata](const void* ptr, uint64 size) { callback(userdata, ptr, size); });
        *success = true;
        return (clients[(uint64)client.get()] = client).get();
    } catch (...) { }

    *success = false;
    return nullptr;
}

extern "C" GRAIN_EXPORT bool clientGetName(void* client, char* buffer, uint64 bufferSize, uint64* size) { return writeStringToBuffer(clients[(uint64)client]->getName(), buffer, bufferSize, size); }
extern "C" GRAIN_EXPORT bool clientGetShutdown(void* client) { return clients[(uint64)client]->getShutdown(); }
extern "C" GRAIN_EXPORT void clientSend(void* client, const void* data, uint64 size) { clients[(uint64)client]->send(data, size); }
extern "C" GRAIN_EXPORT void clientRecv(void* client) { clients[(uint64)client]->recv(); }
extern "C" GRAIN_EXPORT void destroyClient(void* client) { clients.erase((uint64)client); }
