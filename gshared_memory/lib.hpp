namespace gshared_memory {
    using Handle = struct __ShmHandle*;

    bool isExists(const std::string& name);
    Handle create(const std::string& name, size_t size);
    Handle open(const std::string& name);
    size_t getSize(Handle handle);
    void* map(Handle handle);
    void unmap(Handle handle, void* ptr);
    void destroy(Handle handle);

    namespace {
        size_t getPageSize() {
            #ifdef _WIN32
            SYSTEM_INFO si;
            GetSystemInfo(&si);
            return si.dwPageSize;
            #else
            return sysconf(_SC_PAGESIZE);
            #endif
        }

        size_t roundUpToPageSize(size_t size) {
            auto pageSize = getPageSize();
            return ((size + pageSize - 1) / pageSize) * pageSize;
        }
    }

    #ifdef _WIN32
    static_assert(sizeof(Handle) >= sizeof(HANDLE), "Handle must be at least as large as HANDLE");

    bool isExists(const std::string& name) {
        HANDLE hMapFile = OpenFileMappingA(
            FILE_MAP_READ,
            FALSE,
            name.c_str()
        );

        if (hMapFile == NULL) {
            return false;
        }

        CloseHandle(hMapFile);
        return true;
    }

    Handle create(const std::string& name, size_t size) {
        if (isExists(name)) {
            throw std::runtime_error("shared memory already exists");
        }

        size = roundUpToPageSize(size);

        HANDLE hMapFile = CreateFileMappingA(
            INVALID_HANDLE_VALUE,
            NULL,
            PAGE_READWRITE,
            (DWORD)(size >> 32),
            (DWORD)(size & 0xFFFFFFFF),
            name.c_str()
        );

        if (hMapFile == NULL) {
            throw std::runtime_error("failed to create shared memory");
        }

        return (Handle)hMapFile;
    }

    Handle open(const std::string& name) {
        HANDLE hMapFile = OpenFileMappingA(
            FILE_MAP_ALL_ACCESS,
            FALSE,
            name.c_str()
        );

        if (hMapFile == NULL) {
            throw std::runtime_error("failed to open shared memory");
        }

        return (Handle)hMapFile;
    }

    size_t getSize(Handle handle) {
        LPVOID ptr = MapViewOfFile((HANDLE)handle, FILE_MAP_READ, 0, 0, 0);

        if (ptr == NULL) {
            throw std::runtime_error("failed to map shared memory");
        }
        
        MEMORY_BASIC_INFORMATION mbi = { 0 };
        VirtualQuery(ptr, &mbi, sizeof(mbi));
        
        UnmapViewOfFile(ptr);
        return mbi.RegionSize;
    }

    void* map(Handle handle) {
        LPVOID ptr = MapViewOfFile(
            (HANDLE)handle,
            FILE_MAP_ALL_ACCESS,
            0, 0,
            getSize(handle)
        );

        if (ptr == NULL) {
            throw std::runtime_error("failed to map shared memory");
        }

        return (void*)ptr;
    }

    void unmap(Handle, void* ptr) {
        if (!UnmapViewOfFile((LPCVOID)ptr)) {
            throw std::runtime_error("failed to unmap shared memory");
        }
    }

    void destroy(Handle handle) {
        CloseHandle((HANDLE)handle);
    }

    #else
    static_assert(sizeof(Handle) >= sizeof(int), "Handle must be at least as large as int");

    namespace {
        struct ShmInfo {
            std::string name;
            bool isCreator;
        };

        std::unordered_map<Handle, ShmInfo> shmInfoMap;
        std::mutex shmInfoMapMutex;
    }

    bool isExists(const std::string& name) {
        int fd = shm_open(name.c_str(), O_RDONLY, 0666);
        if (fd == -1) return false;
        close(fd);
        return true;
    }

    Handle create(const std::string& name, size_t size) {
        int fd = shm_open(name.c_str(), O_CREAT | O_EXCL | O_RDWR, 0666);

        if (fd == -1) {
            throw std::runtime_error("failed to create shared memory");
        }

        size = roundUpToPageSize(size);
        ftruncate(fd, size);

        auto h = (Handle)(uintptr_t)fd;
        std::lock_guard<std::mutex> lock(shmInfoMapMutex);
        shmInfoMap[h] = { .name = name, .isCreator = true };
        return h;
    }

    Handle open(const std::string& name) {
        int fd = shm_open(name.c_str(), O_RDWR, 0666);

        if (fd == -1) {
            throw std::runtime_error("failed to open shared memory");
        }

        auto h = (Handle)(uintptr_t)fd;
        std::lock_guard<std::mutex> lock(shmInfoMapMutex);
        shmInfoMap[h] = { .name = name, .isCreator = false };
        return h;
    }

    size_t getSize(Handle handle) {
        struct stat sb;
        if (fstat((int)(uintptr_t)handle, &sb) == -1) {
            throw std::runtime_error("failed to get shared memory size");
        }

        return sb.st_size;
    }

    void* map(Handle handle) {
        auto* ptr = (char*)mmap(
            NULL,
            getSize(handle),
            PROT_READ | PROT_WRITE,
            MAP_SHARED,
            (int)(uintptr_t)handle,
            0
        );

        if (ptr == MAP_FAILED) {
            throw std::runtime_error("failed to map shared memory");
        }

        return (void*)ptr;
    }

    void unmap(Handle handle, void* ptr) {
        if (munmap(ptr, getSize(handle)) != 0) {
            throw std::runtime_error("failed to unmap shared memory");
        }
    }

    void destroy(Handle handle) {
        std::lock_guard<std::mutex> lock(shmInfoMapMutex);
        if (shmInfoMap.find(handle) == shmInfoMap.end()) {
            throw std::runtime_error("invalid handle");
        }

        auto info = shmInfoMap[handle];
        shmInfoMap.erase(handle);

        close((int)(uintptr_t)handle);

        if (info.isCreator) {
            shm_unlink(info.name.c_str());
        }
    }

    #endif

    using gsp::gsp;

    struct SharedMemory {
        static gsp<SharedMemory> Create(const std::string& name, size_t size) {
            auto handle = create(name, size);

            auto* shm = new SharedMemory();
            shm->handle = handle;
            return gsp<SharedMemory>(shm);
        }

        static gsp<SharedMemory> Open(const std::string& name) {
            auto handle = open(name);

            auto* shm = new SharedMemory();
            shm->handle = handle;
            return gsp<SharedMemory>(shm);
        }

        size_t getSize() const {
            return gshared_memory::getSize(handle);
        }

        void* getPtr() {
            if (!ptr) ptr = map(handle);
            return ptr;
        }

        ~SharedMemory() {
            if (ptr) unmap(handle, ptr);
            destroy(handle);
        }

        private:
        Handle handle;
        void* ptr;
    };
}
