#pragma once
#include <mutex>
#include <condition_variable>

namespace m {
    class Semaphore {
    public:
        using native_handle_type = std::condition_variable::native_handle_type;

        explicit Semaphore(size_t count = 0);
        Semaphore(const Semaphore&) = delete;
        Semaphore(Semaphore&&) = delete;
        Semaphore& operator=(const Semaphore&) = delete;
        Semaphore& operator=(Semaphore&&) = delete;

        void notify();
        void wait();
        bool try_wait();
        template<class Rep, class Period>
        bool wait_for(const std::chrono::duration<Rep, Period>& d);
        template<class Clock, class Duration>
        bool wait_until(const std::chrono::time_point<Clock, Duration>& t);

        native_handle_type native_handle();

    private:
        size_t                  mCount = 0;
        std::mutex              mMutex;
        std::condition_variable mCv;
    };

    inline Semaphore::Semaphore(size_t count)
        : mCount{count}
    {}

    inline void Semaphore::notify() {
        std::lock_guard<std::mutex> lock{mMutex};
        ++mCount;
        mCv.notify_one();
    }

    inline void Semaphore::wait() {
        std::unique_lock<std::mutex> lock{mMutex};
        mCv.wait(lock, [&]{ return mCount > 0; });
        --mCount;
    }

    inline bool semaphore::try_wait() {
        std::lock_guard<std::mutex> lock{mutex};

        if (count > 0) {
            --count;
            return true;
        }

        return false;
    }

    template<class Rep, class Period>
    bool Semaphore::wait_for(const std::chrono::duration<Rep, Period>& d) {
        std::unique_lock<std::mutex> lock{mMutex};
        auto finished = mCv.wait_for(lock, d, [&]{ return mCount > 0; });

        if (finished)
            --mCount;

        return finished;
    }

    template<class Clock, class Duration>
    bool Semaphore::wait_until(const std::chrono::time_point<Clock, Duration>& t) {
        std::unique_lock<std::mutex> lock{mMutex};
        auto finished = mCv.wait_until(lock, t, [&]{ return mCount > 0; });

        if (finished)
            --mCount;

        return finished;
    }

    inline Semaphore::native_handle_type Semaphore::native_handle() {
        return mCv.native_handle();
    }
}
