#pragma once
#include <m/Interpolators.h>
#include <chrono>

namespace m {
    template <class T, class Clock = std::chrono::steady_clock>
    class Animator {
    public:
        using Interpolator = T(*)(const T&, const T&, double);

        explicit Animator(T initial = T{}) noexcept;

        void     target(T target, typename Clock::duration duration, Interpolator interpolator = linear<T>) noexcept;
        void     reset(T value) noexcept;

        T        current() const noexcept;
        const T& initial() const noexcept;
        const T& target() const noexcept;
        const typename Clock::duration& duration() const noexcept;
        bool     complete() const noexcept;

    private:
        T                          mInitial;
        T                          mTarget;
        typename Clock::time_point mStart;
        typename Clock::duration   mDuration = Clock::duration::zero();
        Interpolator               mInterpolator = nullptr;
    };

    template <class T, class Clock>
    Animator<T, Clock>::Animator(T initial) noexcept
        : mInitial{std::move(initial)}
        , mTarget{mInitial}
    {}

    template <class T, class Clock>
    void Animator<T, Clock>::target(T target, typename Clock::duration duration, Interpolator interpolator) noexcept {
        mInitial      = current();
        mTarget       = std::move(target);
        mStart        = Clock::now();
        mDuration     = std::move(duration);
        mInterpolator = std::move(interpolator);
    }

    template <class T, class Clock>
    void Animator<T, Clock>::reset(T value) noexcept {
        mInitial      = std::move(value);
        mTarget       = mInitial;
        mStart        = {};
        mDuration     = Clock::duration::zero();
        mInterpolator = nullptr;
    }

    template <class T, class Clock>
    T Animator<T, Clock>::current() const noexcept {
        if (!mInterpolator)
            return mTarget;

        auto elapsed = Clock::now() - mStart;

        if (elapsed >= mDuration)
            return mTarget;

        return mInterpolator(
            mInitial,
            mTarget - mInitial,
            elapsed / std::chrono::duration<double, typename Clock::duration::period>{mDuration}
        );
    }

    template <class T, class Clock>
    const T& Animator<T, Clock>::initial() const noexcept {
        return mInitial;
    }

    template <class T, class Clock>
    const T& Animator<T, Clock>::target() const  noexcept {
        return mTarget;
    }

    template <class T, class Clock>
    const typename Clock::duration& Animator<T, Clock>::duration() const noexcept {
        return mDuration;
    }

    template <class T, class Clock>
    bool Animator<T, Clock>::complete() const noexcept {
        return current() == mTarget;
    }
}
