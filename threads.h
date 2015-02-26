#ifndef THREADS__H
#define THREADS__H

#include <pthread.h>
#include <stdio.h>

/**
 * Data structure where the parameters that are going to be passed to the 
 * threads are stored, it's a structure because that way we can pass more than 
 * one argument to a thread. 
 * If you only need to pass one argument, then use a primitive data type.
 */
typedef struct _thread_params
{
	/** Pointer to the file we need to write to or read from. */
	FILE * file;

	/** Number of lines to be writen in phase 1. */
	int writing_lines_num;
	
	/** Number of lines to be read in phase 2. */
	int reading_lines_num;
} thread_params;


/**
 * @details Function that executes the Phase 1: Writing.
 * 
 * @param threads Thread identifiers array.
 * @param file_num Number of files to be created.
 * @param filenames Names for the files mentioned above.
 */
void writing_phase(pthread_t * threads, int file_num, char const *filenames[]);

/**
 * @details Function that executes the Phase 2: Reading.
 * 
 * @param threads Thread identifiers array.
 * @param file_num Number of files to be created.
 * @param filenames Names for the files mentioned above.
 */
void reading_phase(pthread_t * threads, int file_num, char const *filenames[]);


/**
 * @details Function that the thread executes to do the writing.
 * 
 * @param params Any parameter that you need to pass to the function.
 * @return Anything
 */
void * thread_writing(void * params);

/**
 * @details Function that the thread executes to do the reading.
 * 
 * @param params Any parameter that you need to pass to the function.
 * @return Anything
 */
void * thread_reading(void * params);

#endif