namespace gshm_socket {
    using namespace gnumeric::types;
    using gsp::gsp;
    using gshared_memory::SharedMemory;

    using DataCallback = std::function<void(const void*, uint64)>;

    namespace {
        static constexpr uint64 SHM_SOCKET_VERSION = 1;

        struct alignas(8) ShmState {
            uint64 version = SHM_SOCKET_VERSION;

            bool isNotConnected;

            bool senderReady;
            bool senderReadyAck;
            uint64 senderSeq;
            uint64 senderDataSize;

            bool receiverReady;
            bool receiverReadyAck;
            uint64 receiverSeq;
            uint64 receiverDataSize;

            bool shutdown;
            bool shutdownAck;
        };

        void waitForSignal(bool* signal) {
            __sync_synchronize();
            while (!*signal) {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
            __sync_synchronize();
        }

        void waitForSignal(bool* signal1, bool* signal2) {
            __sync_synchronize();
            while (!*signal1 && !*signal2) { // 有一个完成即可
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
            __sync_synchronize();
        }

        bool readSignal(bool* signal) {
            __sync_synchronize();
            bool value = *signal;
            __sync_synchronize();
            return value;
        }

        void writeSignal(bool* signal, bool value) {
            __sync_synchronize();
            *signal = value;
            __sync_synchronize();
        }

        uint64 makeRandomSeq() {
            thread_local std::mt19937_64 rng {
                (uint64_t)(std::random_device {}()) ^
                std::chrono::steady_clock::now().time_since_epoch().count()
            };

            thread_local std::uniform_int_distribution<uint64> dist {
                0, std::numeric_limits<uint64>::max()
            };

            return dist(rng);
        }

        std::string makeDataMemoryName(uint64 seq) {
            return std::format("gshm_socket_data_{}", seq);
        }

        void doSend(bool* ready, bool* readyAck, uint64* seq, uint64* sizeDst, const void* data, uint64 size, gsp<SharedMemory>* mem) {
            waitForSignal(readyAck);

            if (!*mem || (*mem)->getSize() < size || (*mem)->getSize() > size * 2 + 1024 * 1024) {
                *seq = makeRandomSeq();
                *mem = SharedMemory::Create(makeDataMemoryName(*seq), size);
            }

            std::memcpy((*mem)->getPtr(), data, size);
            *sizeDst = size;

            writeSignal(readyAck, false);
            writeSignal(ready, true);
        }

        void doRecv(bool* ready, bool* readyAck, uint64* seq, uint64* size, bool* shutdown, const DataCallback& callback) {
            waitForSignal(ready, shutdown);

            if (readSignal(shutdown)) {
                return;
            }

            {
                auto mem = SharedMemory::Open(makeDataMemoryName(*seq));
                callback(mem->getPtr(), *size);
            }

            writeSignal(ready, false);
            writeSignal(readyAck, true);
        }
    }

    struct Server {
        static gsp<Server> Make(
            const std::string& name,
            const DataCallback& callback
        ) {
            auto s = gsp<Server>(new Server());
            s->name = name;
            s->callback = callback;
            s->init();
            return s;
        }

        std::string getName() const noexcept {
            return name;
        }

        bool getShutdown() noexcept {
            return readSignal(&getStatePointer().shutdown);
        }

        void send(const void* data, uint64 size) {
            auto& state = getStatePointer();

            doSend(
                &state.senderReady, &state.senderReadyAck,
                &state.senderSeq, &state.senderDataSize,
                data, size,
                &dataMemory
            );
        }

        void send(const gdata::Data& data) {
            send(data.data.data(), data.data.size());
        }

        void recv() {
            auto& state = getStatePointer();

            doRecv(
                &state.receiverReady, &state.receiverReadyAck,
                &state.receiverSeq, &state.receiverDataSize,
                &state.shutdown,
                callback
            );
        }

        void shutdown() {
            auto& state = getStatePointer();

            writeSignal(&state.shutdown, true);
            waitForSignal(&state.shutdownAck);
        }

        void runForever() {
            while (!getShutdown()) {
                recv();
            }
        }

        ~Server() {
            if (!mainMemory) return;
            shutdown();
        }

        private:
        std::string name;
        DataCallback callback;
        gsp<SharedMemory> mainMemory;
        gsp<SharedMemory> dataMemory;

        void init() {
            mainMemory = SharedMemory::Create(name, sizeof(ShmState));

            getStatePointer() = {
                .senderReadyAck = true,
                .receiverReadyAck = true
            };

            getStatePointer().isNotConnected = true;
        }

        ShmState& getStatePointer() {
            return *(ShmState*)mainMemory->getPtr();
        }
    };

    struct Client {
        static gsp<Client> Make(
            const std::string& name,
            const DataCallback& callback
        ) {
            auto c = gsp<Client>(new Client());
            c->name = name;
            c->callback = callback;
            c->init();
            return c;
        }

        std::string getName() const noexcept {
            return name;
        }

        bool getShutdown() noexcept {
            return shutdown;
        }

        void send(const void* data, uint64 size) {
            if (shutdown) return;

            auto& state = getStatePointer();

            doSend(
                &state.receiverReady, &state.receiverReadyAck,
                &state.receiverSeq, &state.receiverDataSize,
                data, size,
                &dataMemory
            );
        }

        void send(const gdata::Data& data) {
            send(data.data.data(), data.data.size());
        }

        void recv() {
            auto& state = getStatePointer();

            doRecv(
                &state.senderReady, &state.senderReadyAck,
                &state.senderSeq, &state.senderDataSize,
                &state.shutdown,
                callback
            );

            if (readSignal(&state.shutdown)) {
                shutdown = true;
                writeSignal(&state.shutdownAck, true);
            }
        }

        void runForever() {
            while (!getShutdown()) {
                recv();
            }
        }

        ~Client() {
            if (!mainMemory || shutdown) return;

            auto& state = getStatePointer();
            waitForSignal(&state.receiverReadyAck);
            writeSignal(&state.isNotConnected, true);
        }

        private:
        std::string name;
        DataCallback callback;
        gsp<SharedMemory> mainMemory;
        gsp<SharedMemory> dataMemory;
        std::atomic<bool> shutdown;

        void init() {
            mainMemory = SharedMemory::Open(name);

            if (mainMemory->getSize() < sizeof(ShmState)) {
                failedToCheckVersion("Invalid shared memory size");
            }

            auto& state = getStatePointer();
            if (state.version != SHM_SOCKET_VERSION) {
                failedToCheckVersion("Invalid shared memory version");
            }

            if (!readSignal(&state.isNotConnected)) {
                throw std::runtime_error("Server is already connected to another client");
            }

            writeSignal(&state.isNotConnected, false);
        }

        void failedToCheckVersion(const std::string& msg) {
            throw std::runtime_error(std::format("{}, maybe the server is not running in version {}", msg, SHM_SOCKET_VERSION));
        }

        ShmState& getStatePointer() {
            return *(ShmState*)mainMemory->getPtr();
        }
    };
}
