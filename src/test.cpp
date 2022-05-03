#include "synchronized_thread.h"
#include "synchronized_future.h"
#include "synchronized_task.h"

#define DO_TEST(_cond) if(!_cond) { puts("FAILED"); return 1; } else { puts("PASSED"); }

int main()
{
    {
        printf("TEST 1: Null task: ");
        CSynchronizedFuture future(nullptr);

        bool res = future.WaitAndGetResult();
        
        DO_TEST(res==false)
    }

    {
        class CSampleTask1 : public CSynchronizedTask
        {
            virtual bool Run() override
            {
                return true;
            }
        };

        printf("TEST 2: Sample task: ");
        CSynchronizedThread thread;
        CSampleTask1* task = new CSampleTask1();
        
        CSynchronizedFuture future(task);
        thread.AddTask(task);

        bool res = future.WaitAndGetResult();

        DO_TEST(res==true)

        thread.StopAndJoin();
    }

    return 0;
}
