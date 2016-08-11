#pragma once
#include <mutex>
#include <condition_variable>

namespace m {
    template <typename Mutex, typename CondVar>
    class BasicSemaphore {
    public:
        using native_handle_type = typename CondVar::native_handle_type;

        explicit BasicSemaphore(size_t count = 0);
        BasicSemaphore(const BasicSemaphore&) = delete;
        BasicSemaphore(BasicSemaphore&&) = delete;
        BasicSemaphore& operator=(const BasicSemaphore&) = delete;
        BasicSemaphore& operator=(BasicSemaphore&&) = delete;

        void notify();
        void wait();
        bool try_wait();
        template<class Rep, class Period>
        bool wait_for(const std::chrono::duration<Rep, Period>& d);
        template<class Clock, class Duration>
        bool wait_until(const std::chrono::time_point<Clock, Duration>& t);

        native_handle_type native_handle();

    private:
        Mutex   mMutex;
        CondVar mCv;
        size_t  mCount;
    };

    using Semaphore = BasicSemaphore<std::mutex, std::condition_variable>;

    template <typename Mutex, typename CondVar>
    BasicSemaphore<Mutex, CondVar>::BasicSemaphore(size_t count)
        : mCount{count}
    {}

    template <typename Mutex, typename CondVar>
    void BasicSemaphore<Mutex, CondVar>::notify() {
        std::lock_guard<Mutex> lock{mMutex};
        ++mCount;
        mCv.notify_one();
    }

    template <typename Mutex, typename CondVar>
    void BasicSemaphore<Mutex, CondVar>::wait() {
        std::unique_lock<Mutex> lock{mMutex};
        mCv.wait(lock, [&]{ return mCount > 0; });
        --mCount;
    }

    template <typename Mutex, typename CondVar>
    bool BasicSemaphore<Mutex, CondVar>::try_wait() {
        std::lock_guard<Mutex> lock{mMutex};

        if (mCount > 0) {
            --mCount;
            return true;
        }

        return false;
    }

    template <typename Mutex, typename CondVar>
    template<class Rep, class Period>
    bool BasicSemaphore<Mutex, CondVar>::wait_for(const std::chrono::duration<Rep, Period>& d) {
        std::unique_lock<Mutex> lock{mMutex};
        auto finished = mCv.wait_for(lock, d, [&]{ return mCount > 0; });

        if (finished)
            --mCount;

        return finished;
    }

    template <typename Mutex, typename CondVar>
    template<class Clock, class Duration>
    bool BasicSemaphore<Mutex, CondVar>::wait_until(const std::chrono::time_point<Clock, Duration>& t) {
        std::unique_lock<Mutex> lock{mMutex};
        auto finished = mCv.wait_until(lock, t, [&]{ return mCount > 0; });

        if (finished)
            --mCount;

        return finished;
    }

    template <typename Mutex, typename CondVar>
    typename BasicSemaphore<Mutex, CondVar>::native_handle_type BasicSemaphore<Mutex, CondVar>::native_handle() {
        return mCv.native_handle();
    }
}
