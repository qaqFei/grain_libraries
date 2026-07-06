namespace gthread_safe_queue {
    template <typename T>
    struct ThreadSafeQueue {
        ~ThreadSafeQueue() {
            shutdown();
        }
        
        void enqueue(T frame) {
            {
                std::lock_guard<std::mutex> lock(mtx);
                if (done) return;
                queue.push(std::move(frame));
            }

            cv.notify_one();
        }
        
        bool wait_dequeue(T& frame) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this] { return !queue.empty() || done; });
            if (queue.empty()) return false;
            frame = std::move(queue.front());
            queue.pop();
            return true;
        }
        
        void shutdown() {
            {
                std::lock_guard<std::mutex> lock(mtx);
                done = true;
            }
            
            cv.notify_all();
        }
        
        auto size_approx() const {
            std::lock_guard<std::mutex> lock(mtx);
            return queue.size();
        }
        
    private:
        mutable std::mutex mtx;
        std::condition_variable cv;
        std::queue<T> queue;
        bool done = false;
    };
}
