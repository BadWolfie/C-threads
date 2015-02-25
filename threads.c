#include "threads.h"

#include <stdlib.h>
#include <time.h>

void writing_phase(pthread_t * threads, int file_num, char const *filenames[])
{
	int i, rand_number, total_lines = 0;
	thread_params * params = (thread_params *)
		malloc(file_num * sizeof(thread_params));

	srand(time(NULL));
	for (i = 0; i < file_num; i++) {
		rand_number = (rand() % 100) + 1;
		printf("Writing %d lines in file \"%s\".\n", 
			rand_number, filenames[i+1]);

		params[i].file = fopen(filenames[i+1], "wt");
		params[i].writing_lines_num = rand_number;
		total_lines += rand_number;

		pthread_create(&threads[i], NULL,
			(void *) &thread_writing,
			(void *) &params[i]
		);
	}

	for (i = 0; i < file_num; i++)
		pthread_join(threads[i], (void *) NULL);

	printf("Total of writen lines: %d.\n\n", total_lines);
	free(params);
}

void reading_phase(pthread_t * threads, int file_num, char const *filenames[])
{
	int i, *lines_num, total_lines = 0;
	thread_params * params = (thread_params *)
		malloc(file_num * sizeof(thread_params));

	for (i = 0; i < file_num; i++) {
		params[i].file = fopen(filenames[i+1], "rt");
		params[i].reading_lines_num = 0;

		pthread_create(&threads[i], NULL,
			(void *) &thread_reading,
			(void *) &params[i]
		);
	}

	for (i = 0; i < file_num; i++) {
		pthread_join(threads[i], (void *) &lines_num);
		printf("%d lines read from file \"%s\".\n", *lines_num, filenames[i+1]);
		total_lines += (*lines_num);
	}

	printf("Total of read lines: %d.\n\n", total_lines);
	free(params);
}


void * thread_writing(void * params)
{
	thread_params * aux = (thread_params *) params;
	int i;

	for (i = 0; i < aux->writing_lines_num; i++)
		fprintf(aux->file, "Random line %d\n", i + 1);

	fclose(aux->file);
	pthread_exit((void *) NULL);
}

void * thread_reading(void * params)
{
	thread_params * aux = (thread_params *) params;
	char c;

	while ((c = getc(aux->file)) != EOF) {
		if (c == '\n')
			aux->reading_lines_num++;
	}

	fclose(aux->file);
	pthread_exit((void *) &aux->reading_lines_num);
}
