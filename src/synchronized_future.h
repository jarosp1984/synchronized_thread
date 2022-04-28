#pragma once

class CSynchronizedTask;

//! Class for getting result of asynchronous operation
class CSynchronizedFuture
{
private:
    CSynchronizedTask* m_task;  //!< The task we will be waiting for (can be nullptr)

public:    
    //! Constructor
    CSynchronizedFuture(CSynchronizedTask* task) : m_task(task) {}

    //! Move constructor
    CSynchronizedFuture(CSynchronizedFuture&& other);

    //! Copy constructor (DELETED)
    CSynchronizedFuture(CSynchronizedFuture& other) = delete;

    //! Destructor (deletes the task)
    ~CSynchronizedFuture();

    //! Wait for task to finish and get result (returns false if task is nullptr)
    bool WaitAndGetResult();

    //! Move operator
    void operator=(CSynchronizedFuture&& other);

    //! Copy operator (DELETED)
    void operator=(CSynchronizedFuture& other) = delete;
};
