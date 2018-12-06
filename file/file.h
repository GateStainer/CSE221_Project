//
// Created by Push on 12/1/18.
//

#ifndef CSE221_PROJECT_FILE_H
#define CSE221_PROJECT_FILE_H
//BLOCK size is 4k
#define BLOCK 4096

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

//Run measurements of File System part
void file_measure();

//Print out the result of file cache
void file_cache();

//Print out the overhead of sequential and random read
void file_read();

//Print out the overhead of multiple processes sequentially reading
void file_multi_read();

#endif //CSE221_PROJECT_FILE_H
