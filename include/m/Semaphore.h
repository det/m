#pragma once
#include <condition_variable>
#include <mutex>

namespace m {
    class Semaphore {
    public:
        explicit Semaphore(size_t count = 0);
        Semaphore(const Semaphore&) = delete;
        Semaphore(Semaphore&&) = delete;
        Semaphore& operator=(const Semaphore&) = delete;
        Semaphore& operator=(Semaphore&&) = delete;

        void notify();
        void wait();
        bool tryWait();
        template<class Rep, class Period>
        bool waitFor(const std::chrono::duration<Rep, Period>& d);
        template<class Clock, class Duration>
        bool waitUntil(const std::chrono::time_point<Clock, Duration>& t);

    private:
        std::mutex              mMutex;
        std::condition_variable mCv;
        size_t                  mCount;
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

    inline bool Semaphore::tryWait() {
        std::lock_guard<std::mutex> lock{mMutex};

        if (mCount == 0)
            return false;

        --mCount;
        return true;
    }

    template<class Rep, class Period>
    bool Semaphore::waitFor(const std::chrono::duration<Rep, Period>& d) {
        std::unique_lock<std::mutex> lock{mMutex};
        auto finished = mCv.wait_for(lock, d, [&]{ return mCount > 0; });

        if (finished)
            --mCount;

        return finished;
    }

    template<class Clock, class Duration>
    bool Semaphore::waitUntil(const std::chrono::time_point<Clock, Duration>& t) {
        std::unique_lock<std::mutex> lock{mMutex};
        auto finished = mCv.wait_until(lock, t, [&]{ return mCount > 0; });

        if (finished)
            --mCount;

        return finished;
    }
}
