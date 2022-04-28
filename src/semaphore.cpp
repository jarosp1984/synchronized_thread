#include "semaphore.h"

void CSemaphore::Release()
{
    std::unique_lock<std::mutex> lock(m_mutex);
    m_count++;
    m_cv.notify_one();
}

void CSemaphore::Acquire()
{
    std::unique_lock<std::mutex> lock(m_mutex);

    while(m_count == 0){
        m_cv.wait(lock);
    }
    m_count--;
}
