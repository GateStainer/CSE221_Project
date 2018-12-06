//
// Created by Push on 11/19/18.
//

#include "cpu.h"
#include <stdlib.h>
#include <pthread.h>

void cpu_measure()
{

    //cpu_cycle();
    //rdtsc_overhead();
    //loop_overhead();
    //procedureCall_overhead();
    //systemCall_overhead();
    //processCreate_overhead();
    //threadCreate_overhead();
    //processSwitch_overhead();
    //threadSwitch_overhead();

}

void cpu_cycle()
{
    unsigned long start = rdtsc_begin();
    sleep(10);
    unsigned long end = rdtsc_end();
    printf("There are %lu cycles in 10 seconds\n", (end - start));
}

void rdtsc_overhead()
{
    unsigned long sum = 0;
    for(int i=0; i<10000; i++)
    {
        unsigned long start = rdtsc_begin();
        unsigned long end = rdtsc_end();
        sum += (end - start);
    }
    printf("The average overhead time for rdtsc is %lu cpu cycles\n", (sum / 10000));
}

void loop_overhead()
{
    unsigned long start = rdtsc_begin();
    for(int i=0; i<10000; i++)
        ;
    unsigned long end = rdtsc_end();
    printf("The average overhead time for loop is %f cpu cycles\n", (double)(end - start) / 10000.0);
}


//Testing function0-7 with parameter 0-7
static __attribute__ ((noinline)) int func0(){return 0;}
static __attribute__ ((noinline)) int func1(int a1){return a1;}
static __attribute__ ((noinline)) int func2(int a1, int a2){return a1;}
static __attribute__ ((noinline)) int func3(int a1, int a2, int a3){return a1;}
static __attribute__ ((noinline)) int func4(int a1, int a2, int a3, int a4){return a1;}
static __attribute__ ((noinline)) int func5(int a1, int a2, int a3, int a4, int a5){return a1;}
static __attribute__ ((noinline)) int func6(int a1, int a2, int a3, int a4, int a5, int a6){return a1;}
static __attribute__ ((noinline)) int func7(int a1, int a2, int a3, int a4, int a5, int a6, int a7){return a1;}

void procedureCall_overhead()
{
    unsigned long start;
    unsigned long end;


    start = rdtsc_begin();
    for(int i=0; i<10000; i++)
    {
        func0();
    }
    end = rdtsc_end();
    printf("Calling func0 takes %f cpu cycles in average\n", (double)(end - start) /10000.0 - 5.0);

    start = rdtsc_begin();
    for(int i=0; i<10000; i++)
    {
        func1(i);
    }
    end = rdtsc_end();
    printf("Calling func1 takes %f cpu cycles in average\n", (double)(end - start) /10000.0 - 5.0);

    start = rdtsc_begin();
    for(int i=0; i<10000; i++)
    {
        func2(i, i);
    }
    end = rdtsc_end();
    printf("Calling func2 takes %f cpu cycles in average\n", (double)(end - start) /10000.0 - 5.0);

    start = rdtsc_begin();
    for(int i=0; i<10000; i++)
    {
        func3(i, i, i);
    }
    end = rdtsc_end();
    printf("Calling func3 takes %f cpu cycles in average\n", (double)(end - start) /10000.0 - 5.0);

    start = rdtsc_begin();
    for(int i=0; i<10000; i++)
    {
        func4(i, i, i, i);
    }
    end = rdtsc_end();
    printf("Calling func4 takes %f cpu cycles in average\n", (double)(end - start) /10000.0 - 5.0);

    start = rdtsc_begin();
    for(int i=0; i<10000; i++)
    {
        func5(i, i, i, i, i);
    }
    end = rdtsc_end();
    printf("Calling func5 takes %f cpu cycles in average\n", (double)(end - start) /10000.0 - 5.0);

    start = rdtsc_begin();
    for(int i=0; i<10000; i++)
    {
        func6(i, i, i, i, i, i);
    }
    end = rdtsc_end();
    printf("Calling func6 takes %f cpu cycles in average\n", (double)(end - start) /10000.0 - 5.0);

    start = rdtsc_begin();
    for(int i=0; i<10000; i++)
    {
        func7(i, i, i, i, i, i, i);
    }
    end = rdtsc_end();
    printf("Calling func7 takes %f cpu cycles in average\n", (double)(end - start) /10000.0 - 5.0);
}

void systemCall_overhead()
{
    unsigned long start = rdtsc_begin();

    getpid();
    unsigned long end = rdtsc_end();
    printf("The average overhead time for getpid is %f cpu cycles\n", (double)(end - start));
}

void processCreate_overhead()
{
    unsigned long start, end;
    unsigned long sum = 0;
    start = rdtsc_begin();
    for(int i=0; i<10000; i++)
    {
        pid_t pid = fork();
        if(pid == 0)
            exit(0);
        else
        {
            wait(NULL);
        }
    }
    end = rdtsc_end();
    printf("The average overhead for fork() is %f cpu cycles\n", (double)(end - start) / 10000.0);
}

void* runThread(void* c)
{
    pthread_exit(NULL);
}

void threadCreate_overhead()
{
    pthread_t td;
    unsigned long start, end;
    start = rdtsc_begin();
    for(int i=0; i<10000; i++)
    {
        pthread_create(&td, NULL, runThread, NULL);
        pthread_join(td, NULL);
    }
    end = rdtsc_end();
    printf("The average overhead for pthread_create() is %f cpu cylces\n", (double)(end - start) / 10000.0);
}


unsigned long processSwithchTime(int *fd)
{
    unsigned long start, end;
    pid_t  pid;
    unsigned long res = 0;
    if((pid = fork()) != 0)
    {
        start = rdtsc_begin();
        wait(NULL);
        read(fd[0], (void*)&end, sizeof(unsigned long));
    }
    else
    {
        end = rdtsc_end();
        write(fd[1], (void*)&end, sizeof(unsigned long));
        exit(0);
    }
    if(end > start)
        res += (end - start);
    return res;
}

void processSwitch_overhead()
{
    int fd[2];
    pipe(fd);
    unsigned long sum = 0;
    for(int i=0; i<10000; i++)
    {
        unsigned long res = processSwithchTime(fd);
        if(res > 0)
            sum += res;
    }
    printf("The average overhead for process context switch is %f cpu cylces\n", (double)(sum) / 10000.0);
}



static inline void *foo(void * a) {
    unsigned long t = rdtsc_end();

    write(fd[1], (void*)&t, sizeof(unsigned long));
    pthread_exit(NULL);
}

unsigned long threadSwitchTime()
{
    unsigned long start, end;
    pthread_t pt;
    pipe(fd);
    pthread_create(&pt, NULL, foo, NULL);
    start = rdtsc_begin();
    pthread_join(pt, NULL);
    read(fd[0], (void*)&end, sizeof(unsigned long));
    return end - start;
}

void threadSwitch_overhead()
{
    unsigned long sum = 0;
    for(int i=0; i<10000; i++)
    {
        unsigned long res = threadSwitchTime();
        if(res > 0)
            sum += res;
    }
    printf("The average overhead for thread context switch is %f cpu cycles\n", (double)(sum) / 10000.0);
}

