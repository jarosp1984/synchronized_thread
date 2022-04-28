#pragma once
#include <assert.h>

class CSynchronizedThread;

//! Task for asynchronous execution on CSynchronizedThread
class CSynchronizedTask
{
protected:    
    bool                    m_result = false;       //!< Operation result
    bool                    m_resultRead = false;   //!< Result read status (to make sure wait operation occured before deletion)
    CSynchronizedThread*    m_thread = nullptr;     //!< Thread running the task

public:    
    //! Task constructor
    CSynchronizedTask()
    {}


    //! Task destructor
    virtual ~CSynchronizedTask() { assert(m_resultRead); }

    //! Get thread
    CSynchronizedThread* GetThread() const { return m_thread; }

    //! Set thread
    void SetThread(CSynchronizedThread* thread) { m_thread = thread; }

    //! Get task result and set m_resultRead
    bool GetResult() { m_resultRead = true; return m_result; }

    //! Set task result
    void SetResult(bool res) { m_result = res; }

    //! Run task
    virtual bool Run() = 0;
};
