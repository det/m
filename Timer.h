#pragma once
#include <chrono>

namespace m
{
    template<class Clock>
    class Timer
    {
    public:
        using clock    = Clock;
        using duration = typename clock::duration;

        Timer();

        void     start();
        void     stop();
        void     restart();
        void     reset();

        duration elapsed() const;
        bool     stopped() const noexcept;

    private:
        typename clock::time_point mStart;
        duration                   mElapsed;
        bool                       mStopped;
    };

    using SystemTimer  = Timer<std::chrono::system_clock>;
    using SteadyTimer  = Timer<std::chrono::steady_clock>;
    using HighResTimer = Timer<std::chrono::high_resolution_clock>;

    template<class Clock>
    Timer<Clock>::Timer()
        : mElapsed{duration::zero()}
        , mStopped{true}
    {
    }

    template<class Clock>
    void Timer<Clock>::start()
    {
        mStart   = clock::now();
        mStopped = false;
    }

    template<class Clock>
    void Timer<Clock>::stop()
    {
        mElapsed += clock::now() - mStart;
        mStopped = true;
    }

    template<class Clock>
    void Timer<Clock>::restart()
    {
        mStart   = clock::now();
        mElapsed = duration::zero();
        mStopped = false;
    }

    template<class Clock>
    void Timer<Clock>::reset()
    {
        mElapsed = duration::zero();
        mStopped = true;
    }

    template<class Clock>
    typename Timer<Clock>::duration Timer<Clock>::elapsed() const
    {
        if(mStopped)
            return mElapsed;
        return mElapsed + clock::now() - mStart;
    }

    template<class Clock>
    bool Timer<Clock>::stopped() const noexcept
    {
        return mStopped;
    }
}