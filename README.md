# C-threads
Code samples for the Posix threads API in C.

A Makefile has been added with instructions for compiling and running the program, so just execute `make` for compiling it and `make run` for running it.

### Usage
This program takes n-filenames as argument (will be created if they don't exist), creates the same number of threads and then executes two phases.
* Phase 1 - Writing files: Each file is assign to a thread, a random number of lines is writen in each of them and then shows the total number of lines that was writen in all of the files.

* Phase 2 - Reading files: Each file is assign to a thread, counts the number of lines in each of them and then shows the total number of lines that was read from all of the files.

## POSIX Threads
To use this API you need to add `#include <pthread.h>` to your code and use its functions for implementing threads, some of the important symbols included within this header which are used in this sample program are the following:

* `pthread_t`  
	Data type used for thread identifiers.  

* `pthread_create(pthread_t * thread, const pthread_attr_t * attr, void * (* start_routine) (void *), void * arg);`  
	Used to create a new thread with attributes specified by `attr`. If `attr` is `NULL`, the default attributes are used. Upon successful completion, `pthread_create()` stores the ID of the created thread in the location referenced by `thread` and then executes `start_routine` with `arg` as its argument.  

* `pthread_join(pthread_t thread, void ** value_ptr);`  
	This function suspends execution of the calling thread until the target `thread` terminates. On return from a successful `pthread_join()` call with a non-NULL `value_ptr` argument, the value passed to `pthread_exit()` by the terminating thread is made available in the location referenced by `value_ptr`.

* `pthread_exit(void * value_ptr);`  
	This function terminates the calling thread and makes the value `value_ptr` available to any successful join with the terminating thread. 

A function `start_routine` that can be executed by a thread has the following format:  
`void * start_routine(void * params);`  
where `params` can be anything that you need to pass as an argument to the thread or `NULL` if it doesn't need any.
