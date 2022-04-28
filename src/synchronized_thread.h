#pragma once
#include <vector>
#include <mutex>
#include "semaphore.h"
#include "thread.h"

class CSynchronizedTask;

//! Thread for executing CSynchronizedTask. It allows to wait for task to finish. Only one task can be added at any time.
class CSynchronizedThread : public CThread
{
private:
    std::vector<CSynchronizedTask*> m_tasks;            //!< Array of tasks (should be of size 0 or 1)
    std::mutex                      m_mutex;            //!< Tasks access mutex
    tSemaphore                      m_startSemaphore;   //!< Task start semaphore
    tSemaphore                      m_finishSemaphore;  //!< Task finish semaphore

public:
    //! Constructor
    CSynchronizedThread();

    //! Add task to thread
    void AddTask(CSynchronizedTask* task);

    //! Thread function
    void Loop();

    //! Stop and join thread
    void StopAndJoin();

    //! Wait for task to finish;
    void WaitForTaskFinished();

private:
    //! Static thread function
    static void ThreadFunc(CThread* thread);
};
