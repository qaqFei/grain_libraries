namespace gbyte_rwer {
    using namespace gnumeric::types;
    using gsp::gsp;

    enum class ByteEndian {
        Native,
        Little,
        Big
    };

    template<ByteEndian E>
    struct ByteWriter {
        std::vector<uint8> data;

        static gsp<ByteWriter<E>> Make() {
            auto* writer = new ByteWriter<E>();
            return gsp<ByteWriter<E>>(writer);
        }

        void writeBytes(const gdata::Data& data) noexcept { this->data.insert(this->data.end(), data.data.begin(), data.data.end()); }
        void writeBytes(const uint8* data, uint64 size) noexcept { this->data.insert(this->data.end(), data, data + size); }
        void writeBytes(const std::string& data) noexcept { writeBytes((const uint8*)data.data(), data.size()); }
        void writeBytes(const std::vector<uint8>& data) noexcept { writeBytes(data.data(), data.size()); }

        template<typename T>
        static T byte_swap(T val) noexcept {
            if constexpr (sizeof(T) == 1) return val;
            else if constexpr (sizeof(T) == 2) {
                uint16 ret;
                memcpy(&ret, &val, sizeof(T));
                ret = __builtin_bswap16(ret);
                memcpy(&val, &ret, sizeof(T));
                return val;
            } else if constexpr (sizeof(T) == 4) {
                uint32 ret;
                memcpy(&ret, &val, sizeof(T));
                ret = __builtin_bswap32(ret);
                memcpy(&val, &ret, sizeof(T));
                return val;
            } else if constexpr (sizeof(T) == 8) {
                uint64 ret;
                memcpy(&ret, &val, sizeof(T));
                ret = __builtin_bswap64(ret);
                memcpy(&val, &ret, sizeof(T));
                return val;
            } else {
                static_assert(!sizeof(T), "Unsupported size");
                return val;
            }
        }

        template<typename T>
        static T from_native(T val) noexcept {
            if constexpr (E == ByteEndian::Native) return val;
            #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
                else if constexpr (E == ByteEndian::Little) return val;
                else return byte_swap(val);
            #else
                else if constexpr (E == ByteEndian::Big) return val;
                else return byte_swap(val);
            #endif
        }

        template<typename T>
        void write(T value) noexcept {
            static_assert(std::is_trivially_copyable_v<T>);
            T write_val = from_native(value);
            writeBytes((uint8*)&write_val, sizeof(T));
        }

        gdata::Data toData() const {
            return { .data = data };
        }
    };

    // TODO: ByteReader
}
