//Write a C program that creates 2^N threads that race to the finish (N is a command line argument). The threads must pass through N checkpoint. The checkpoint with number X will allow half as many threads to pass simultaneously than checkpoint number X - 1 (N >= X >=1). Checkpoint 0 (the first one) will allow 2^(N-1) to pass simultaneously through it.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
	pthread_barrier_t *br;
	int n, id;
} data;

void *f(void *arg) {
	data d = *((data*) arg);
	
	printf("Thread %d starting...\n", d.id);
	
	for ( int i = 0; i < d.n; ++i ) {
		
		printf("Thread %d passed the checkpoint %d\n", d.id, i);
		pthread_barrier_wait(&d.br[i]);
	}
		
	printf("Thread %d finished its job\n", d.id);
	return NULL;
}

int main(int argc, char *argv[]) {
	if ( argc != 2 ) {
		perror("you must provided exactly one argument");
		exit(1);
	}

	int n = atoi(argv[1]);
	int p = 1;
	int i;

	for ( i = 0; i < n; ++i ) 
		p *= 2;

	pthread_t *th = malloc(p * sizeof(pthread_t));
	pthread_barrier_t *br = malloc(n * sizeof(pthread_barrier_t));

	int step = 1;
	for ( i = 0; i < n; ++i ) {
		pthread_barrier_init(&br[i], NULL, p/step);
		step *= 2;
	}

	data *arg = malloc(p * sizeof(data));

	for ( i = 0; i < p; ++i ) {
		arg[i].br = br;
		arg[i].n = n;
		arg[i].id = i;
		
		pthread_create(&th[i], NULL, f, (void *) &arg[i]);
	}
	
	for ( i = 0; i < p; ++i ) 
		pthread_join(th[i], NULL);

	for ( i = 0; i < n; ++i ) 
		pthread_barrier_destroy(&br[i]);

	free(th);
	free(br);
	free(arg);

	return 0;
}
