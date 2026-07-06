namespace gdata {
    using namespace gnumeric::types;

    struct Data {
        std::vector<uint8> data;

        static Data MakeFromFile(const std::string& fn) {
            std::ifstream file(std::filesystem::path((const char8_t*)fn.c_str()), std::ios::binary | std::ios::ate);
            if (!file) throw std::runtime_error("failed to read file");

            uint64 size = file.tellg();
            file.seekg(0);
            std::vector<uint8> buffer(size);
            if (!file.read((char*)buffer.data(), size)) throw std::runtime_error("failed to read file");
            file.close();

            return { .data = std::move(buffer) };
        }

        static bool MakeFromFile(Data& data, const std::string& fn) {
            try {
                data = MakeFromFile(fn);
                return true;
            } catch (...) {
                return false;
            }
        }

        static std::optional<Data> MakeFromFileOptional(const std::string& fn) {
            try {
                return MakeFromFile(fn);
            } catch (...) {
                return std::nullopt;
            }
        }

        static Data MakeFromGrain(const std::string& key) {
            int size = 0;
            void* data = grain::get_embed_file(key.c_str(), &size);
            if (!data) throw std::runtime_error("failed to read grain file: " + key);

            return { .data = std::vector<uint8>((uint8*)data, (uint8*)data + size) };
        }

        std::string toString() const {
            return std::string((char*)data.data(), data.size());
        }

        uint64 getHash() const {
            ghash_bucket::Bucket bucket;
            for (uint8 byte : data) bucket.submitNumber(byte);
            return bucket.hash;
        }

        bool isStartsWith(const Data& other) const noexcept {
            if (data.size() < other.data.size()) return false;
            return std::memcmp(data.data(), other.data.data(), other.data.size()) == 0;
        }

        bool isEndsWith(const Data& other) const noexcept {
            if (data.size() < other.data.size()) return false;
            return std::memcmp(data.data() + data.size() - other.data.size(), other.data.data(), other.data.size()) == 0;
        }

        bool isStartsWith(const std::string& other) const noexcept {
            if (data.size() < other.size()) return false;
            return std::memcmp(data.data(), other.data(), other.size()) == 0;
        }

        bool isEndsWith(const std::string& other) const noexcept {
            if (data.size() < other.size()) return false;
            return std::memcmp(data.data() + data.size() - other.size(), other.data(), other.size()) == 0;
        }

        bool empty() const noexcept {
            return data.empty();
        }
    };
}
