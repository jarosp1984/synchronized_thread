#include <assert.h>
#include "synchronized_thread.h"
#include "synchronized_task.h"

void CSynchronizedThread::ThreadFunc(CThread* thread)
{
    static_cast<CSynchronizedThread*>(thread)->Loop();
}

CSynchronizedThread::CSynchronizedThread()
    : CThread(ThreadFunc)
{}

void CSynchronizedThread::AddTask(CSynchronizedTask* task)
{    
    task->SetThread(this);
    m_mutex.lock();
    assert(m_tasks.size() == 0);
    m_tasks.push_back(task);
    m_mutex.unlock();
    m_startSemaphore.Release();
}


void CSynchronizedThread::Loop()
{
    while(m_run)
    {
        m_startSemaphore.Acquire();
        m_mutex.lock();
        if(m_tasks.size())
        {
            CSynchronizedTask* currentTask = m_tasks.front();
            m_tasks.erase(m_tasks.begin());
            currentTask->SetResult( currentTask->Run() );
        }
        m_mutex.unlock();
        m_finishSemaphore.Release();
    }
}

void CSynchronizedThread::WaitForTaskFinished()
{
    m_finishSemaphore.Acquire();
    assert(m_tasks.size() == 0);
}

void CSynchronizedThread::StopAndJoin()
{
    CThread::Stop();
    m_startSemaphore.Release();
    Join();
}
