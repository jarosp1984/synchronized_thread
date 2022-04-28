#pragma once
#include <thread>
#include <atomic>

//! Thread for looped activity. Contains std::thread.
class CThread
{
protected:
    std::atomic_bool    m_run;      ///< Thread functions can test this variable inside their loops.
    std::thread         m_thread;

public:
    template <class _Fn, class... _Args>
    explicit CThread(_Fn&& _Fx, _Args&&... _Ax)
        : m_run( true )
        , m_thread( std::thread(std::forward<_Fn>(_Fx), this, std::forward<_Args>(_Ax)...) )
    {}

    void Stop()
    {
        m_run = false;
    }

    void Join()
    {
        m_thread.join();
    }
};
