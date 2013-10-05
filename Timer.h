#pragma once
#include <chrono>
 
namespace m
{
    //-----------------------------------------------------------------------------
    template<typename Clock>
    class Timer
    {
    public:
        using clock      = Clock;
        using rep        = typename clock::rep;
        using period     = typename clock::period;
        using duration   = typename clock::duration;
        using time_point = typename clock::time_point;
 
        constexpr       Timer() noexcept;
 
        void            Start() noexcept;
        void            Pause() noexcept;
        void            Reset() noexcept;
 
        duration        Elapsed() const noexcept;
        constexpr bool  Paused() const noexcept;
 
    private:
        time_point      m_Start;
        duration        m_Elapsed;
        bool            m_Paused;
    };
 
    //-----------------------------------------------------------------------------
    using SystemTimer  = Timer<std::chrono::system_clock>;
    using SteadyTimer  = Timer<std::chrono::steady_clock>;
    using HighResTimer = Timer<std::chrono::high_resolution_clock>;
 
    //-----------------------------------------------------------------------------
    template<typename Clock>
    constexpr Timer<Clock>::Timer() noexcept
        : m_Elapsed{duration::zero()}
        , m_Paused{true}
    {
    }
 
    //-----------------------------------------------------------------------------
    template<typename Clock>
    void Timer<Clock>::Start() noexcept
    {
        if(m_Paused)
        {
            m_Start = clock::now();
            m_Paused = false;
        }
    }
 
    //-----------------------------------------------------------------------------
    template<typename Clock>
    void Timer<Clock>::Pause() noexcept
    {
        if(!m_Paused)
        {
            m_Elapsed += clock::now() - m_Start;
            m_Paused = true;
        }
    }
 
    //-----------------------------------------------------------------------------
    template<typename Clock>
    void Timer<Clock>::Reset() noexcept
    {
        m_Elapsed = duration::zero();
        m_Paused = true;
    }
 
    //-----------------------------------------------------------------------------
    template<typename Clock>
    typename Timer<Clock>::duration Timer<Clock>::Elapsed() const noexcept
    {
        if(m_Paused)
            return m_Elapsed;
        return m_Elapsed + clock::now() - m_Start;
    }
 
    //-----------------------------------------------------------------------------
    template<typename Clock>
    constexpr bool Timer<Clock>::Paused() const noexcept
    {
        return m_Paused;
    }
}
