#pragma once
#include "Interpolators.h"
#include <chrono>

namespace m {
    template <typename T, typename Clock = std::chrono::steady_clock>
    class Animator {
    public:
        using Interpolator = T(*)(const T&, const T&, double);

        explicit Animator(T initial = T{});

        void target(T target, typename Clock::duration duration, Interpolator interpolator = Linear<T>);
        void reset(T value);

        T current() const;
        const T& initial() const;
        const T& target() const;
        const typename Clock::duration& duration() const;

    private:
        T                          mInitial;
        T                          mTarget;
        typename Clock::time_point mStart;
        typename Clock::duration   mDuration = Clock::duration::zero();
        Interpolator               mInterpolator = nullptr;
    };

    template <typename T, typename Clock>
    Animator<T, Clock>::Animator(T initial)
        : mInitial{std::move(initial)}
        , mTarget{mInitial}
    {}

    template <typename T, typename Clock>
    void Animator<T, Clock>::target(T target, typename Clock::duration duration, Interpolator interpolator) {
        mInitial      = current();
        mTarget       = std::move(target);
        mStart        = Clock::now();
        mDuration     = std::move(duration);
        mInterpolator = std::move(interpolator);
    }

    template <typename T, typename Clock>
    void Animator<T, Clock>::reset(T value) {
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
    const T& Animator<T, Clock>::initial() const {
        return mInitial;
    }

    template <typename T, typename Clock>
    const T& Animator<T, Clock>::target() const {
        return mTarget;
    }

    template <typename T, typename Clock>
    const Animator<T, Clock>::duration& Animator<T, Clock>::duration() const {
        return mDuration;
    }
}
