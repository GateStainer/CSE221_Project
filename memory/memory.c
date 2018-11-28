//
// Created by Push on 11/19/18.
//

#include <malloc.h>
#include "memory.h"

int REPEAT_TIMES = 10;
int ACCESS_TIMES = 1000;


double measure_ram_with_parameters(int array_size, int stride) {
    double average_cycles = 0;

    for (int repeat = 0; repeat < REPEAT_TIMES; repeat++) {
        int *array = malloc((size_t) array_size * sizeof(int));
        for (int i = 0; i < array_size; i++) {
            array[i] = (i + stride) % array_size;
        }
        unsigned long start = rdtsc_begin();
        int index = 0;
        for (int i = 0; i < ACCESS_TIMES; i++) {
            index = array[index];
        }
        unsigned long end = rdtsc_end();
        average_cycles += (double)(end-start) / ACCESS_TIMES;
        free(array);
    }
    average_cycles /= REPEAT_TIMES;
    printf("access memory for %d array and %d stride cost %g cycles in average\n", array_size, stride, average_cycles);
    return average_cycles;
}


void measure_ram(int array_size_len, int stride_len, FILE* f) {
    int array_sizes[array_size_len];   // 2K to 512M
    array_sizes[0] = 512;
    for (int i = 1; i < array_size_len; i++) {
        array_sizes[i] = array_sizes[i-1] * 4;
    }
    int strides[stride_len];
    strides[0] = 1;
    for (int i = 1; i < stride_len; i++) {
        strides[i] = strides[i-1] * 4;
    }
    for (int i = 0; i < array_size_len; i++) {
        for (int j = 0; j < stride_len; j++) {
            int array_size = array_sizes[i];
            int stride = strides[j];
            double cycles = measure_ram_with_parameters(array_size, stride);
            fprintf(f, "%d, %d, %g\n", array_size * 4, stride * 4, cycles);
        }
    }
}

void memory_measure() {
    FILE *f = fopen("ram-statistics.csv", "w");
    measure_ram(9, 11, f);
}