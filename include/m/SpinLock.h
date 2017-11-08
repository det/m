#pragma once
#include <atomic>

namespace m {
    class SpinLock {
    public:
        SpinLock() = default;
        SpinLock(const SpinLock&) = delete;
        SpinLock(SpinLock&&) = delete;
        SpinLock& operator=(const SpinLock&) = delete;
        SpinLock& operator=(SpinLock&&) = delete;

        void lock() noexcept;
        bool tryLock() noexcept;
        void unlock() noexcept;

    private:
        std::atomic_flag mLocked = ATOMIC_FLAG_INIT;
    };

    inline void SpinLock::lock() noexcept {
        while (mLocked.test_and_set(std::memory_order_acquire)) {}
    }

    inline bool SpinLock::tryLock() noexcept {
        return !mLocked.test_and_set(std::memory_order_acquire);
    }

    inline void SpinLock::unlock() noexcept {
        mLocked.clear(std::memory_order_release);
    }
}
