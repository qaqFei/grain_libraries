namespace gsp {
    template <typename T>
    struct gsp {
        struct RefCnt {
            T* ptr;
            std::atomic<int> count{1};
            
            explicit RefCnt(T* p) : ptr(p) {}
            void ref() noexcept { ++count; }
            void unref() noexcept {
                if (--count == 0) {
                    delete ptr;
                    delete this;
                }
            }
        };
        
        RefCnt* fCtrl;

        explicit gsp(RefCnt* ctrl) : fCtrl(ctrl) {}
        using element_type = T;
        constexpr gsp() noexcept : fCtrl(nullptr) {}
        constexpr gsp(std::nullptr_t) noexcept : fCtrl(nullptr) {}
        explicit gsp(T* ptr) : fCtrl(ptr ? new RefCnt(ptr) : nullptr) {}
        gsp(const gsp& o) noexcept : fCtrl(o.fCtrl) { if (fCtrl) fCtrl->ref(); }
        gsp(gsp&& o) noexcept : fCtrl(o.fCtrl) { o.fCtrl = nullptr; }
        
        template <typename U> 
        gsp(const gsp<U>& o) noexcept 
            : fCtrl(reinterpret_cast<RefCnt*>(o.fCtrl)) { 
            if (fCtrl) fCtrl->ref(); 
        }
        
        template <typename U> 
        gsp(gsp<U>&& o) noexcept 
            : fCtrl(reinterpret_cast<RefCnt*>(o.fCtrl)) { 
            o.fCtrl = nullptr; 
        }
        
        ~gsp() { if (fCtrl) fCtrl->unref(); }

        gsp& operator=(const gsp& o) noexcept {
            if (o.fCtrl != fCtrl) {
                if (o.fCtrl) const_cast<gsp&>(o).fCtrl->ref();
                auto* old = fCtrl;
                fCtrl = const_cast<RefCnt*>(o.fCtrl);
                if (old) old->unref();
            }
            return *this;
        }
        
        gsp& operator=(gsp&& o) noexcept {
            if (o.fCtrl != fCtrl) {
                auto* old = fCtrl;
                fCtrl = o.fCtrl;
                o.fCtrl = nullptr;
                if (old) old->unref();
            }
            return *this;
        }
        
        gsp& operator=(std::nullptr_t) noexcept {
            reset();
            return *this;
        }

        T& operator*() const { return *fCtrl->ptr; }
        T* operator->() const { return fCtrl->ptr; }
        T* get() const noexcept { return fCtrl ? fCtrl->ptr : nullptr; }
        explicit operator bool() const noexcept { return fCtrl != nullptr; }

        void reset(T* ptr = nullptr) noexcept {
            if (fCtrl && fCtrl->ptr == ptr) {
                return;
            }
            auto* old = fCtrl;
            fCtrl = ptr ? new RefCnt(ptr) : nullptr;
            if (old) old->unref();
        }
        
        void swap(gsp& o) noexcept {
            std::swap(fCtrl, o.fCtrl);
        }

        RefCnt* release_ctrl() noexcept {
            auto* c = fCtrl;
            fCtrl = nullptr;
            return c;
        }
    };

    template <typename T, typename U>
    bool operator==(const gsp<T>& a, const gsp<U>& b) noexcept { return a.get() == b.get(); }
    template <typename T, typename U>
    bool operator!=(const gsp<T>& a, const gsp<U>& b) noexcept { return a.get() != b.get(); }
    template <typename T>
    bool operator==(const gsp<T>& a, std::nullptr_t) noexcept { return !a; }
    template <typename T>
    bool operator!=(const gsp<T>& a, std::nullptr_t) noexcept { return (bool)a; }
    template <typename T>
    bool operator==(std::nullptr_t, const gsp<T>& a) noexcept { return !a; }
    template <typename T>
    bool operator!=(std::nullptr_t, const gsp<T>& a) noexcept { return (bool)a; }
}
