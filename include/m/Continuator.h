#pragma once
#include <m/FunctionTraits.h>
#include <future>
#include <list>
#include <functional>

namespace m {
    class Continuator {
    public:
        Continuator() = default;
        Continuator(const Continuator&) = delete;
        Continuator(Continuator&&) = default;
        Continuator& operator=(const Continuator&) = delete;
        Continuator& operator=(Continuator&&) = default;

        // Register a callback to be called when the cooresponding future is ready. The
        // provided future must be valid (have a shared state).
        template <class Future, class Callback>
        void then(Future&& f, Callback&& c);

        // Checks for futures which are ready and calls cooresponding callbacks on the
        // current thread.
        void update();

    private:
        std::list<std::function<bool()>> mCallbacks;
    };

    template <class Future, class Callback>
    void Continuator::then(Future&& f, Callback&& c) {
        auto wrapper = [f = std::forward<Future>(f), c = std::forward<Callback>(c)]() mutable {
            if (f.wait_for(std::chrono::seconds{0}) != std::future_status::ready)
                return false;
            
            if constexpr (arity_zero<Callback>) c();
            else                                c(std::move(f));
            
            return true;
        };

        mCallbacks.emplace_back([wrapper = std::make_shared<decltype(wrapper)>(std::move(wrapper))] {
            return (*wrapper)();
        });
    }

    inline void Continuator::update() {
        mCallbacks.remove_if([](auto& wrapper) { return wrapper(); });
    }
}
