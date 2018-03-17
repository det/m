#pragma once
#include <cmath>

//  See easings.net and gizma.com/easing for examples and math
//
//  b: start value
//  c: change in value
//  s: percent complete (0-1)
namespace m {
    template <class T>
    constexpr T linear(const T& b, const T& c, double s) {
        return b + c*s;
    }

    struct Sine {
        static constexpr auto pi = 3.1415926535897932385;

        template <class T>
        static T easeIn(const T& b, const T& c, double s) {
            return -c * cos(s * (pi/2)) + c + b;
        }

        template <class T>
        static T easeOut(const T& b, const T& c, double s) {
            return c * sin(s * (pi/2)) + b;
        }

        template <class T>
        static T easeInOut(const T& b, const T& c, double s) {
            return -c/2 * (cos(pi*s) - 1) + b;
        }
    };

    struct Quadratic {
        template <class T>
        static constexpr T easeIn(const T& b, const T& c, double s) {
            return c*s*s + b;
        }

        template <class T>
        static constexpr T easeOut(const T& b, const T& c, double s) {
            return -c * s*(s-2) + b;
        }

        template <class T>
        static constexpr T easeInOut(const T& b, const T& c, double s) {
            s *= 2;
            if (s < 1)
                return c/2 * s*s + b;
            s -= 1;
            return -c/2 * (s*(s-2) - 1) + b;
        }
    };

    struct Cubic {
        template <class T>
        static constexpr T easeIn(const T& b, const T& c, double s) {
            return c * s*s*s + b;
        }

        template <class T>
        static constexpr T easeOut(const T& b, const T& c, double s) {
            s -= 1;
            return c * (s*s*s + 1) + b;
        }

        template <class T>
        static constexpr T easeInOut(const T& b, const T& c, double s) {
            s *= 2;
            if (s < 1)
                return c/2 * s*s*s + b;
            s -= 2;
            return c/2 * (s*s*s + 2) + b;
        }
    };

    struct Quartic {
        template <class T>
        static constexpr T easeIn(const T& b, const T& c, double s) {
            return c * s*s*s*s + b;
        }

        template <class T>
        static constexpr T easeOut(const T& b, const T& c, double s) {
            s -= 1;
            return -c * (s*s*s*s - 1) + b;
        }

        template <class T>
        static constexpr T easeInOut(const T& b, const T& c, double s) {
            s *= 2;
            if (s < 1)
                return c/2 * s*s*s*s + b;
            s -= 2;
            return -c/2 * (s*s*s*s - 2) + b;
        }
    };

    struct Quintic {
        template <class T>
        static constexpr T easeIn(const T& b, const T& c, double s) {
            return c * s*s*s*s*s + b;
        }

        template <class T>
        static constexpr T easeOut(const T& b, const T& c, double s) {
            s -= 1;
            return c*(s*s*s*s*s + 1) + b;
        }

        template <class T>
        static constexpr T easeInOut(const T& b, const T& c, double s) {
            s *= 2;
            if (s < 1)
                return c/2 * s*s*s*s*s + b;
            s -= 2;
            return c/2 * (s*s*s*s*s + 2) + b;
        }
    };

    struct Exponential {
        template <class T>
        static T easeIn(const T& b, const T& c, double s) {
            return c * pow(2, 10 * (s - 1)) + b;
        }

        template <class T>
        static T easeOut(const T& b, const T& c, double s) {
            return c * (-pow(2, -10 * s) + 1) + b;
        }

        template <class T>
        static T easeInOut(const T& b, const T& c, double s) {
            s *= 2;
            if (s < 1)
                return c/2 * pow(2, 10 * (s - 1)) + b;
            s -= 1;
            return c/2 * (-pow(2, -10 * s) + 2) + b;
        }
    };

    struct Circular {
        template <class T>
        static T easeIn(const T& b, const T& c, double s) {
            return -c * (sqrt(1 - s*s) - 1) + b;
        }

        template <class T>
        static T easeOut(const T& b, const T& c, double s) {
            s -= 1;
            return c * sqrt(1 - s*s) + b;
        }

        template <class T>
        static T easeInOut(const T& b, const T& c, double s) {
            s *= 2;
            if (s < 1)
                return -c/2 * (sqrt(1 - s*s) - 1) + b;
            s -= 2;
            return c/2 * (sqrt(1 - s*s) + 1) + b;
        }
    };

    struct Back {
        template <class T>
        static constexpr T easeIn(const T& b, const T& c, double s) {
            constexpr auto f = 1.70158;
            return c * s*s * ((f+1)*s - f) + b;
        }

        template <class T>
        static constexpr T easeOut(const T& b, const T& c, double s) {
            constexpr auto f = 1.70158;
            s -= 1;
            return c * (s*s * ((f+1)*s + f) + 1) + b;
        }

        template <class T>
        static constexpr T easeInOut(const T& b, const T& c, double s) {
            constexpr auto f = 1.70158 * 1.525;
            s *= 2;
            if (s < 1)
                return c/2 * (s*s * ((f+1)*s - f)) + b;
            s -= 2;
            return c/2 * (s*s * ((f+1)*s + f) + 2) + b;
        }
    };
}
