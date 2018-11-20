#include <stdio.h>
#include <unistd.h>


void inline measured_function(volatile int *var)
{
	(*var) = 1;
}

static inline unsigned long rdtsc_begin(void) {
	unsigned lo, hi;
	__asm__ __volatile__("cpuid\n\t"
		  "rdtsc\n\t"
		  "mov %%edx, %0\n\t"
		  "mov %%eax, %1\n\t"
		  : "=r" (hi), "=r" (lo)
		  :: "%rax", "%rbx", "%rcx", "%rdx");
	return (((unsigned long)hi << 32) | lo);
}

static inline unsigned long rdtsc_end(void) {
	unsigned lo, hi;
	__asm__ __volatile__("rdtscp\n\t"
		  "mov %%edx, %0\n\t"
		  "mov %%eax, %1\n\t"
		  "cpuid\n\t"
		  : "=r" (hi), "=r" (lo)
		  :: "%rax", "%rbx", "%rcx", "%rdx");
	return (((unsigned long)hi << 32) | lo);
}


int main()
{
	unsigned long start = rdtsc_begin();
	sleep(10);
	unsigned long end = rdtsc_end();
	printf("%lu\n", (end - start));

	return 0;
}



