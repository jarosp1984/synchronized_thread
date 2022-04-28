#include "synchronized_future.h"
#include "synchronized_task.h"
#include "synchronized_thread.h"

CSynchronizedFuture::CSynchronizedFuture(CSynchronizedFuture&& other)
{
    m_task = other.m_task;
    other.m_task = nullptr;
}

void CSynchronizedFuture::operator=(CSynchronizedFuture&& other)
{
    if(m_task)
    {
        delete m_task;
        m_task = nullptr;
    }

    m_task = other.m_task;
    other.m_task = nullptr;
}

CSynchronizedFuture::~CSynchronizedFuture()
{
    if(m_task)
    {
        delete m_task;
        m_task = nullptr;
    }
}

bool CSynchronizedFuture::WaitAndGetResult()
{
    if(m_task)
    {
        m_task->GetThread()->WaitForTaskFinished();
        bool res = m_task->GetResult();
        return res;
    }
    else
    {
        return false;
    }
}
