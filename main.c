#include "threads.h"
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	if (argc == 1) {
		puts("Run like this: ./threads <1st filename> ... <nth filename>");
		return 1;
	}

	puts("Executing writing phase:");
	writing_phase(argc - 1, argv);

	puts("Executing reading phase:");
	reading_phase(argc - 1, argv);

	return 0;
}