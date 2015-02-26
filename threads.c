#include "threads.h"

#include <stdlib.h>
#include <time.h>

void writing_phase(int file_num, char const *filenames[])
{
	int i, rand_number, total_lines = 0;

	/* We create a pthread_t array with a file_num number of elements.*/
	pthread_t * threads = (pthread_t *)
		malloc(file_num * sizeof(pthread_t));

	/* We create a thread_params array with a file_num number of elements.*/
	thread_params * params = (thread_params *)
		malloc(file_num * sizeof(thread_params));

	srand(time(NULL));
	for (i = 0; i < file_num; i++) {
		rand_number = (rand() % 100) + 1;
		printf("Writing %d lines in file \"%s\".\n", 
			rand_number, filenames[i+1]);

		/* We assign the needed fields on each thread_params structure. */
		params[i].file = fopen(filenames[i+1], "wt");
		params[i].writing_lines_num = rand_number;
		total_lines += rand_number;

		/* We create each thread with the defaults attributes, save its ID in an
		 * element of threads and execute the thread_writing function. */
		pthread_create(&threads[i], NULL,
			(void *) &thread_writing,
			(void *) &params[i]
		);
	}

	/* We wait for every thread to terminate. */
	for (i = 0; i < file_num; i++)
		pthread_join(threads[i], (void *) NULL);

	printf("Total of writen lines: %d.\n\n", total_lines);
	free(threads);
	free(params);
}

void reading_phase(int file_num, char const *filenames[])
{
	int i, *lines_num, total_lines = 0;

	/* We create a pthread_t array with a file_num number of elements.*/
	pthread_t * threads = (pthread_t *)
		malloc(file_num * sizeof(pthread_t));

	/* We create a thread_params array with a file_num number of elements.*/
	thread_params * params = (thread_params *)
		malloc(file_num * sizeof(thread_params));

	for (i = 0; i < file_num; i++) {
		/* We assign the needed fields on each thread_params structure. */
		params[i].file = fopen(filenames[i+1], "rt");
		params[i].reading_lines_num = 0;

		/* We create each thread with the defaults attributes, save its ID in an
		 * element of threads and execute the thread_reading function. */
		pthread_create(&threads[i], NULL,
			(void *) &thread_reading,
			(void *) &params[i]
		);
	}

	/* We wait for every thread to terminate and receive the number of lines 
	 * that were read from the file in the lines_num variable. */
	for (i = 0; i < file_num; i++) {
		pthread_join(threads[i], (void *) &lines_num);
		printf("%d lines read from file \"%s\".\n", *lines_num, filenames[i+1]);
		total_lines += (*lines_num);
	}

	printf("Total of read lines: %d.\n\n", total_lines);
	free(threads);
	free(params);
}


void * thread_writing(void * params)
{
	/* We cast the parameters that were passed to the function for easier use 
	 * within the same. */
	thread_params * aux = (thread_params *) params;
	int i;

	/* We write the required number of lines to the file. */
	for (i = 0; i < aux->writing_lines_num; i++)
		fprintf(aux->file, "Random line %d\n", i + 1);
	fclose(aux->file);

	/* We terminate the thread. */
	pthread_exit((void *) NULL);
}

void * thread_reading(void * params)
{
	/* We cast the parameters that were passed to the function for easier use 
	 * within the same. */
	thread_params * aux = (thread_params *) params;
	char c;

	/* We count the number of lines in the file. */
	while ((c = getc(aux->file)) != EOF)
		if (c == '\n')
			aux->reading_lines_num++;
	fclose(aux->file);

	/* We terminate the thread and return the number of read lines. */
	pthread_exit((void *) &aux->reading_lines_num);
}
