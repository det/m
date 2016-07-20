#pragma once
#include <chrono>

namespace m {
    template<typename Clock>
    class Timer {
    public:
        using clock    = Clock;
        using duration = typename clock::duration;

        void     start() noexcept;
        void     stop() noexcept;
        void     restart() noexcept;
        void     reset() noexcept;

        duration elapsed() const noexcept;
        bool     stopped() const noexcept;

    private:
        typename clock::time_point mStart;
        duration                   mElapsed = duration::zero();
        bool                       mStopped = true;
    };

    using SystemTimer  = Timer<std::chrono::system_clock>;
    using SteadyTimer  = Timer<std::chrono::steady_clock>;
    using HighResTimer = Timer<std::chrono::high_resolution_clock>;

    template<typename Clock>
    void Timer<Clock>::start() noexcept {
        mStart   = clock::now();
        mStopped = false;
    }

    template<typename Clock>
    void Timer<Clock>::stop() noexcept {
        if (!mStopped) {
            mElapsed += clock::now() - mStart;
            mStopped = true;
        }
    }

    template<typename Clock>
    void Timer<Clock>::restart() noexcept {
        mStart   = clock::now();
        mElapsed = duration::zero();
        mStopped = false;
    }

    template<typename Clock>
    void Timer<Clock>::reset() noexcept {
        mElapsed = duration::zero();
        mStopped = true;
    }

    template<typename Clock>
    typename Timer<Clock>::duration Timer<Clock>::elapsed() const noexcept {
        if (mStopped)
            return mElapsed;
        return mElapsed + clock::now() - mStart;
    }

    template<typename Clock>
    bool Timer<Clock>::stopped() const noexcept {
        return mStopped;
    }
}
