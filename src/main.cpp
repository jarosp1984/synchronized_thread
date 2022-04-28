#include "synchronized_thread.h"
#include "synchronized_future.h"
#include "synchronized_task.h"

//! Sample task 1
class CSampleTask1 : public CSynchronizedTask
{
    virtual bool Run() override
    {
        printf("Sample task 1 started\n");

        printf("Sample task 1 ended\n");
        return true;
    }
};

//! Sample task 2
class CSampleTask2 : public CSynchronizedTask
{
    virtual bool Run() override
    {
        printf("Sample task 2 started\n");

        printf("Sample task 2 ended\n");
        return true;
    }
};

int main()
{
    // Starting the thread
    CSynchronizedThread thread;

    // Doing the job
    {
        CSampleTask1* task = new CSampleTask1();

        thread.AddTask(task);
        CSynchronizedFuture future(task);

        future.WaitAndGetResult();
    }

    {
        CSampleTask2* task = new CSampleTask2();

        thread.AddTask(task);
        CSynchronizedFuture future(task);

        future.WaitAndGetResult();
    }

    // Stopping the thread
    thread.StopAndJoin();
    return 0;
}
