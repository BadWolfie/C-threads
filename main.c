#include "threads.h"
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	if (argc == 1) {
		puts("Run like this: ./threads <1st filename> ... <nth filename>");
		return 1;
	}

	int threads_num = argc - 1;

	/* We create a pthread_t array with a threads_num number of elements.*/
	pthread_t * threads = (pthread_t *)
		malloc(threads_num * sizeof(pthread_t));

	puts("Executing writing phase:");
	writing_phase(threads, threads_num, argv);

	puts("Executing reading phase:");
	reading_phase(threads, threads_num, argv);

	free(threads);
	return 0;
}