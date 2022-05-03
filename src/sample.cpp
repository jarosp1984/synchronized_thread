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
        return false;
    }
};

int main()
{
    // Starting the thread
    CSynchronizedThread thread;

    // Working with task 1
    {
        CSampleTask1* task = new CSampleTask1();

        thread.AddTask(task);
        CSynchronizedFuture future(task);

        //Do some work on main thread
        printf("Doing main thread job 1\n");

        bool res = future.WaitAndGetResult();
        printf("Task 1 result: %s\n", res ? "true" : "false");
    }

    // Working with task 2
    {
        CSampleTask2* task = new CSampleTask2();

        thread.AddTask(task);
        CSynchronizedFuture future(task);

        //Do some work on main thread
        printf("Doing main thread job 2\n");

        bool res = future.WaitAndGetResult();
        printf("Task 2 result: %s\n", res ? "true" : "false");
    }

    // Stopping the thread
    thread.StopAndJoin();
    return 0;
}
