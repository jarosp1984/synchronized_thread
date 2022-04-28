#pragma once

#include <mutex>
#include <condition_variable>

//! Simple sempahore
class CSemaphore
{
private:
    std::mutex              m_mutex;
    std::condition_variable m_cv;
    int                     m_count = 0;

public:
    //! Release semaphore
    void Release();

    //! Acquire sempahore
    void Acquire();
};

typedef CSemaphore tSemaphore;
