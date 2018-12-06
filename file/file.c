//
// Created by Push on 12/1/18.
//
#include "file.h"
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>

void file_measure()
{
    //file_cache();
    //file_read();
    file_multi_read();
}

void file_cache()
{
    void* buffer = malloc(BLOCK);
    int fd = open("../file/4GB_file", O_RDONLY | O_SYNC);
    unsigned long file_size = (unsigned long)(1)*1024*1024*1024;
    unsigned long bytes_read = 0;
    lseek(fd, file_size-1, SEEK_SET);
    while(true)
    {
        lseek(fd, -2*BLOCK, SEEK_CUR);
        ssize_t bytes = read(fd, buffer, BLOCK);
        if(bytes <= 0 || bytes_read >= file_size)
            break;
        bytes_read += bytes;
    }
    close(fd);
    fd = open("../file/4GB_file", O_RDONLY | O_SYNC);
    bytes_read = 0;
    unsigned long start, end, sum;
    sum = 0;
    int count = 0;
    lseek(fd, file_size-1, SEEK_SET);
    while(true)
    {
        lseek(fd, -2*BLOCK, SEEK_CUR);
        start = rdtsc_begin();
        ssize_t bytes = read(fd, buffer, BLOCK);
        end = rdtsc_end();
        sum += (end - start);
        if(bytes <= 0 || bytes_read >= file_size)
            break;
        bytes_read += bytes;
        count++;
    }
    close(fd);
    free(buffer);
    printf("The average time for reading a 4k block is %f cpu cycles\n", (double)(sum) / (double)(count));
}

void file_seq_read()
{
	void* buffer = malloc(BLOCK);
	int fd = open("../file/4GB_file", O_RDONLY | O_SYNC);
	if(fcntl(fd, F_NOCACHE, 1) == -1)
		printf("Can't disable cache\n");
	unsigned long file_size = (unsigned long)(32)*1024*1024;
	unsigned long bytes_read = 0;
	unsigned long start, end, sum;
	sum = 0;
	int count = 0;
	while(true)
	{
		start = rdtsc_begin();
		ssize_t bytes = read(fd, buffer, BLOCK);
		end = rdtsc_end();
		if(bytes <= 0 || bytes_read >= file_size)
			break;
		bytes_read += bytes;
		sum += (end - start);
		count++;
	}
	close(fd);
	printf("The average time for reading a 4K block sequentially is %f cpu cycles\n", (double)(sum) / (double)(count));
}

void file_random_read()
{
	void* buffer = malloc(BLOCK);
	int fd = open("../file/4GB_file", O_RDONLY | O_SYNC);
	if(fcntl(fd, F_NOCACHE, 1) == -1)
		printf("Can't disable cache\n");
	unsigned long file_size = (unsigned long)(1024)*1024*1024;
	unsigned long bytes_read = 0;
	unsigned long start, end, sum;
	sum = 0;
	int num = file_size / BLOCK;
	for(int i=0; i<num; i++)
	{
		int k = rand() % num;
		start = rdtsc_begin();
		lseek(fd, k*BLOCK, SEEK_SET);
		read(fd, buffer, BLOCK);
		end = rdtsc_end();
		sum += (end - start);
	}
	close(fd);
	printf("The average time for reading a 4K block randomly is %f cpu cycles\n", (double)(sum) / (double)(num));
}

void file_read()
{
	//file_seq_read();
	file_random_read();
}

void readFile(int i)
{
	unsigned long sum = 0;
	void* buffer = malloc(BLOCK);
	char* files[] = {"../file/64MB_file_1", "../file/64MB_file_2", "../file/64MB_file_3", "../file/64MB_file_4", "../file/64MB_file_5", "../file/64MB_file_6", "../file/64MB_file_7", "../file/64MB_file_8"};
	int fd = open(files[i], O_RDONLY | O_SYNC);
	if(fcntl(fd, F_NOCACHE, 1) == -1)
		printf("Can't disable cache\n");
	unsigned start, end;
	int count = 0;
	while(true)
	{
		start = rdtsc_begin();
		ssize_t bytes = read(fd, buffer, BLOCK);
		end = rdtsc_end();
		if(bytes <= 0)
			break;
		sum += (end - start);
		count++;
	}
	printf("The average time for reading a 4K block sequentially in process %d is %f cpu cycles\n", i, (double)(sum) / (double)(count));
}

void file_multi_read()
{
	pid_t pids[8];
	int n = 8;
	unsigned sum = 0;
	for(int i=0; i<n; i++)
	{
		pids[i] = fork();
		if(pids[i] < 0)
		{
			perror("fork");
			abort();
		}
		else if(pids[i] == 0)
		{
			readFile(i);
			exit(0);
		}
	}
}