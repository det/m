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
        void then(Future f, Callback c);

        // Checks for futures which are ready and calls cooresponding callbacks.
        void update();

    private:
        template <class Callback, class Future>
        std::enable_if_t<arity_v<Callback>>  call(Callback& c, Future&& f) { c(std::forward<Future>(f)); }
        template <class Callback, class Future>
        std::enable_if_t<!arity_v<Callback>> call(Callback& c, Future&&) { c(); }

        std::list<std::function<bool()>> mCallbacks;
    };

    template <class Future, class Callback>
    void Continuator::then(Future f, Callback c) {
        auto wrapper = [this, f = std::move(f), c = std::move(c)]() mutable {
            if (f.wait_for(std::chrono::seconds{0}) == std::future_status::ready) {
                call(c, std::move(f));
                return true;
            }
            return false;
        };

        mCallbacks.emplace_back([wrapper = std::make_shared<decltype(wrapper)>(std::move(wrapper))] {
            return (*wrapper)();
        });
    }

    inline void Continuator::update() {
        mCallbacks.remove_if([](const auto& wrapper) { return wrapper(); });
    }
}
