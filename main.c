//
// Created by Push on 11/19/18.
//

#include <stdio.h>
#include <unistd.h>
#include "cpu/cpu.h"

void inline measured_function(volatile int *var)
{
	(*var) = 1;
}



int main()
{
    cpu_measure();
	return 0;
}



