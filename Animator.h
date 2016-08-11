#pragma once
#include "Interpolators.h"
#include <chrono>

namespace m {
    template <typename T, typename Clock = std::chrono::steady_clock>
    class Animator {
    public:
        using Interpolator = T(*)(const T&, const T&, double);

        explicit Animator(T initial = T{}) noexcept;

        void target(T target, typename Clock::duration duration, Interpolator interpolator = Linear<T>) noexcept;
        void reset(T value) noexcept;

        T current() const noexcept;
        const T& initial() const noexcept;
        const T& target() const noexcept;
        const typename Clock::duration& duration() const;

    private:
        T                          mInitial;
        T                          mTarget;
        typename Clock::time_point mStart;
        typename Clock::duration   mDuration = Clock::duration::zero();
        Interpolator               mInterpolator = nullptr;
    };

    template <typename T, typename Clock>
    Animator<T, Clock>::Animator(T initial) noexcept
        : mInitial{std::move(initial)}
        , mTarget{mInitial}
    {}

    template <typename T, typename Clock>
    void Animator<T, Clock>::target(T target, typename Clock::duration duration, Interpolator interpolator) noexcept {
        mInitial      = current();
        mTarget       = std::move(target);
        mStart        = Clock::now();
        mDuration     = std::move(duration);
        mInterpolator = std::move(interpolator);
    }

    template <typename T, typename Clock>
    void Animator<T, Clock>::reset(T value) noexcept {
        mInitial      = std::move(value);
        mTarget       = mInitial;
        mStart        = {};
        mDuration     = Clock::duration::zero();
        mInterpolator = nullptr;
    }

    template <typename T, typename Clock>
    T Animator<T, Clock>::current() const {
        auto elapsed = Clock::now() - mStart;

        if (elapsed >= mDuration)
            return mTarget;

        auto t = std::chrono::duration<double>(elapsed).count(),
             d = std::chrono::duration<double>(mDuration).count();

        return mInterpolator(mInitial, mTarget-mInitial, t/d);
    }

    template <typename T, typename Clock>
    const T& Animator<T, Clock>::initial() const noexcept {
        return mInitial;
    }

    template <typename T, typename Clock>
    const T& Animator<T, Clock>::target() const  noexcept {
        return mTarget;
    }

    template <typename T, typename Clock>
    const Animator<T, Clock>::duration& Animator<T, Clock>::duration() const noexcept {
        return mDuration;
    }
}
