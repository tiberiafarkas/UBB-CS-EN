/*Write a C program that reads a number n from standard input and creates n threads, numbered from 0 to n - 1. Each thread places a random number between 10 and 20 on the position indicated by its id in an array of integers. After all threads have placed their number in the array, each thread repeats the following:
- Checks if the number on its own position is greater than 0.
- If yes, it substracts 1 from all numbers of the array, except the one on its own position.
- If not, the thread terminates.
- If there are no numbers in the array that are greater than 0, except the number on the thread's index position, the thread terminates.
After all threads terminate, the main process prints the array of integers. Use appropriate synchronization mechanisms.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

typedef struct{
	int id, *arr, n, *set;
	pthread_mutex_t *mtx;
	pthread_barrier_t *br;
} data;

void *f(void *arg) {
	data d = *((data *) arg);
	
	if ( !d.set[d.id] ) {
		int nr = random() % 11 + 10;

		printf("Thread %d generated: %d\n", d.id, nr);

		pthread_mutex_lock(d.mtx);
		d.arr[d.id] = nr;
		d.set[d.id] = 1;
		pthread_mutex_unlock(d.mtx);

	}		

	pthread_barrier_wait(d.br);

	while ( 1 ) { 
		if ( d.arr[d.id] <= 0 ) {
			break;
		}

		int ok = 0;
		
		pthread_mutex_lock(d.mtx);

		for ( int i = 0; i < d.n && !ok; ++i ) {
			if ( d.arr[i] > 0 && i != d.id ) 
				ok = 1;
		}

		if ( !ok ) 
			break;

		for ( int i = 0; i < d.n; ++i ) {
			printf("%d ", d.arr[i]);
			if ( i != d.id ) 
				d.arr[i] -= 1;
		}
		
		printf("\n");

		pthread_mutex_unlock(d.mtx);
	}

	printf("Thread %d finihed its job\n", d.id);
	pthread_mutex_unlock(d.mtx);	
	return NULL;
}

int main(int argc, char *argv[]) {
	if ( argc != 2 ) {
		perror("provide one argument");
		exit(1);
	}

	int n = atoi(argv[1]);

	pthread_t *th =	malloc(n * sizeof(pthread_t));
	pthread_mutex_t mtx;
	pthread_barrier_t br;
	
	pthread_mutex_init(&mtx, NULL);
	pthread_barrier_init(&br, NULL, n);

	int *arr = malloc(n * sizeof(int));
	int *set = malloc(n * sizeof(int));
	memset(set, 0, sizeof(int));
	data *arg = malloc(n * sizeof(data));

	for ( int i = 0; i < n; ++i ) {
		arg[i].mtx = &mtx;
		arg[i].br = &br;
		arg[i].id = i;
		arg[i].n = n;
		arg[i].arr = arr;
		arg[i].set = set;

		pthread_create(&th[i], NULL, f, (void *) &arg[i]);
	}

	for ( int i = 0; i < n; ++i ) 
		pthread_join(th[i], NULL);

	for ( int i = 0; i < n; ++i ) 
		printf("%d ", arr[i]);

	pthread_mutex_destroy(&mtx);
	pthread_barrier_destroy(&br);
	free(arg);
	free(th);
	free(arr);
	free(set);
	return 0;
}

