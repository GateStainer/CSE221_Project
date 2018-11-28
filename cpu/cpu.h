//
// Created by Push on 11/19/18.
//

#ifndef CPU_H
#define CPU_H

#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <unistd.h>

static int fd[2];

//Run measurements of CPU part
void cpu_measure();

//Call this function when starting measurement.
//@Return current cpu timeID
static unsigned long inline rdtsc_begin(void) {
    unsigned lo, hi;
    __asm__ __volatile__("cpuid\n\t"
                         "rdtsc\n\t"
                         "mov %%edx, %0\n\t"
                         "mov %%eax, %1\n\t"
    : "=r" (hi), "=r" (lo)
    :: "%rax", "%rbx", "%rcx", "%rdx");
    return (((unsigned long)hi << 32) | lo);
}

//Call this function when ending measurement.
//@Return current cpu timeID
static unsigned long inline rdtsc_end(void) {
    unsigned lo, hi;
    __asm__ __volatile__("rdtscp\n\t"
                         "mov %%edx, %0\n\t"
                         "mov %%eax, %1\n\t"
                         "cpuid\n\t"
    : "=r" (hi), "=r" (lo)
    :: "%rax", "%rbx", "%rcx", "%rdx");
    return (((unsigned long)hi << 32) | lo);
}

//Print out cpu cycles in 10 seconds
//This function use rdtsc to calculate cpu cycles in 10 seconds
//Overhead of rdtsc can be ignored
void cpu_cycle();

//Print out the overhead of rdtsc.
//This function runs rdtsc 10,000 times and calculate average running time.
void rdtsc_overhead();

//Print out the average cpu cycles for a loop
void loop_overhead();

//Print out the cpu overhead for a procedure call, with parameter from 0 to 7
void procedureCall_overhead();

//Print out the cpu overhead for a system call
//TODO: Compare different types of system calls
void systemCall_overhead();

//Print out the cpu overhead for fork()
void processCreate_overhead();

//Print out the cpu overhead for pthread_create()
void threadCreate_overhead();

//Print out the cpu overhead for process switch
void processSwitch_overhead();

void threadSwitch_overhead();

#endif //CPU_H
