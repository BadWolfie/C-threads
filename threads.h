#ifndef THREADS__H
#define THREADS__H

#include <pthread.h>
#include <stdio.h>

typedef struct _thread_params
{
	FILE * file;
	int reading_lines_num;
	int writing_lines_num;
} thread_params;

void writing_phase(pthread_t * threads, int file_num, char const *filenames[]);
void reading_phase(pthread_t * threads, int file_num, char const *filenames[]);

void * thread_writing(void * params);
void * thread_reading(void * params);

#endif