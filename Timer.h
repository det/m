#pragma once
#include <chrono>
#include <cassert>
 
namespace m
{
    //-----------------------------------------------------------------------------
    template<typename Clock>
    class Timer
    {
    public:
        using clock    = Clock;
        using duration = typename clock::duration;
 
                 Timer()   noexcept;
 
        void     start()   noexcept;
        void     stop()    noexcept;
        void     restart() noexcept;
        void     reset()   noexcept;

        duration elapsed() const noexcept;
        bool     stopped() const noexcept;
 
    private:
        typename clock::time_point m_Start;
        duration                   m_Elapsed;
        bool                       m_Stopped;
    };
 
    //-----------------------------------------------------------------------------
    using SystemTimer  = Timer<std::chrono::system_clock>;
    using SteadyTimer  = Timer<std::chrono::steady_clock>;
    using HighResTimer = Timer<std::chrono::high_resolution_clock>;
 
    //-----------------------------------------------------------------------------
    template<typename Clock>
    Timer<Clock>::Timer() noexcept
        : m_Elapsed{duration::zero()}
        , m_Stopped{true}
    {
    }
 
    //-----------------------------------------------------------------------------
    template<typename Clock>
    void Timer<Clock>::start() noexcept
    {
        assert(m_Stopped);
        m_Start = clock::now();
        m_Stopped = false;        
    }
 
    //-----------------------------------------------------------------------------
    template<typename Clock>
    void Timer<Clock>::stop() noexcept
    {
        assert(!m_Stopped);
        m_Elapsed += clock::now() - m_Start;
        m_Stopped = true;
    }

    //-----------------------------------------------------------------------------
    template<typename Clock>
    void Timer<Clock>::restart() noexcept
    {
        m_Start = clock::now();
        m_Elapsed = duration::zero();
        m_Stopped = false;
    }
 
    //-----------------------------------------------------------------------------
    template<typename Clock>
    void Timer<Clock>::reset() noexcept
    {
        m_Elapsed = duration::zero();
        m_Stopped = true;
    }
 
    //-----------------------------------------------------------------------------
    template<typename Clock>
    typename Timer<Clock>::duration Timer<Clock>::elapsed() const noexcept
    {
        if(m_Stopped)
            return m_Elapsed;
        return m_Elapsed + clock::now() - m_Start;
    }
 
    //-----------------------------------------------------------------------------
    template<typename Clock>
    bool Timer<Clock>::stopped() const noexcept
    {
        return m_Stopped;
    }
}
