# C-threads
Code samples for the Posix threads API in C.

A Makefile has been added with instructions for compiling and running the program, so just execute `make` for compiling it and `make run` for running it.

## Usage
This program takes n-filenames as argument (will be created if they don't exist), creates the same number of threads and then executes two phases.
* Phase 1 - Writing files: Each file is assign to a thread, a random number of lines is writen in each of them and then shows the total number of lines that was writen in all of the files.
* Phase 2 - Reading files: Each file is assign to a thread, counts the number of lines in each of them and then shows the total number of lines that was read from all of the files.