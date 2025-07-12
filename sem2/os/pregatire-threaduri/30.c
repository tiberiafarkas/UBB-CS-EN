/*
Relay: Create a C program that reads a number n from the standard input and created 4 * n threads. The threads will be split into teams of 4. In each team the threads will be numbered from 0 and will run according to the relay rules:
- Thread 0 from each team starts, waits (usleep) for 100 and 200 milliseconds, then passes the control to thread 1
- Thread 1 waits between 100 and 200 milliseconds then passes the control to thread 2
- Thread 2 waits between 100 and 200 milliseconds then passes the control to thread 3
- Thread 3 waits between 100 and 200 milliseconds, then prints a message indicating that the team has finished, then terminates
The team from which thread 3 terminates first is considered the winning team. Use appropriate synchronization mechanisms.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{
	int id, team, curr;
	pthread_mutex_t *mtx;
	pthread_barrier_t *br;
	pthread_cond_t *c;
} data;

void *f(void *arg) {
	return NULL;
}

int main(int argc, char *argv[]) {
	if ( argc != 2 ) {
		perror("provide one argument");
		exit(1);
	}

	int n = atoi(argv[1]);
	pthread_t **th = malloc(4 * sizeof(pthread_t));
	pthread_mutex_t mtx;	
	pthread_barrier_t br;
	pthread_cond_t c;

	pthread_mutex_init(&mtx, NULL);
	pthread_barrier_init(&br, NULL, 4);
	pthread_cond_init(&c, NULL);

	data **arg = malloc(4 * sizeof(data*));
	
	for ( int i = 0; i < n; ++i ) {
		arg[i] = malloc(n * sizeof(int));
		th[i] = malloc(n * sizeof(int));
	}

	for ( int i = 0; i < n; ++i ) {
		for ( int j = 0; j < 4; ++j ) {
			arg[i][j].id = j;
			arg[i][j].mtx = &mtx;
			arg[i][j].br = &br;
			arg[i][j].c = &c;
			arg[i][j].team = i;
			arg[i][j].curr = 0;
	
			pthread_create(&th[i][j], NULL, f, (void *) *arg[i][j]);
		}
	}


	return 0;
}

