#pragma once

#include <mutex>
#include <condition_variable>

//! Simple sempahore
class CSemaphore
{
private:
    std::mutex              m_mutex;        //!< Internal mutex
    std::condition_variable m_cv;           //!< Internal conditional variable
    int                     m_count = 0;    //!< The counter

public:
    //! Release semaphore
    void Release();

    //! Acquire sempahore
    void Acquire();
};

typedef CSemaphore tSemaphore;
