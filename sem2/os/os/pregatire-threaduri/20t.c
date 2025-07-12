//Write a C program that takes as command line arguments 2 numbers: N and M. The program will simulate a thread race that have to pass through M checkpoints. Through each checkpoint the threads must pass one at a time (no 2 threads can be inside the same checkpoint). Each thread that enters a checkpoint will wait between 100 and 200 milliseconds (usleep(100000) makes a thread or process wait for 100 milliseconds) and will print a message indicating the thread number and the checkpoint number, then it will exit the checkpoint. Ensure that no thread will try to pass through a checkpoint until all threads have passed the current checkpoint.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

//n threads
//m barriers

typedef struct{
	int m, id;
	pthread_mutex_t *mtx;
	pthread_barrier_t *br;
} data;

void *f(void *arg) {
	data d = *((data *) arg);
	
	//pthread_barrier_wait(d.br);
	
	for ( int i = 0; i < d.m; ++i ) {
		pthread_barrier_wait(d.br);
	//	pthread_mutex_lock(&d.mtx[i]);	
		printf("Thread %d entered the checkpoint %d\n", d.id, i);
		
		int s = (random() % 101 + 100) * 1000;
		usleep(s);
	//	pthread_mutex_unlock(&d.mtx[i]);
	}
	
	printf("Thread %d finished its job\n", d.id);	

	return NULL;
}

int main(int argc, char *argv[]) {
	if ( argc != 3 ) {
		perror("invalid number of arguments provided");
		exit(1);
	}

	int n = atoi(argv[1]);	
	int m = atoi(argv[2]);
	
	pthread_t *th = malloc(n * sizeof(pthread_t));
	pthread_barrier_t br;
	//pthread_mutex_t *mtx = malloc(m * sizeof(pthread_mutex_t));

	pthread_barrier_init(&br, NULL, n);
	//pthread_mutex_init(&mtx, NULL);
	
	//for ( int i = 0; i < m; ++i ) 
	//	pthread_mutex_init(&mtx[i], NULL);

	data *arg = malloc(n * sizeof(data));

	for ( int i = 0; i < n; ++i ) { 
		arg[i].m = m;
		arg[i].id = i;
	//	arg[i].mtx = mtx;
		arg[i].br = &br;
	
		pthread_create(&th[i], NULL, f, (void *) &arg[i]);
	}

	for ( int i = 0; i < n; ++i ) {
		pthread_join(th[i], NULL);
	}

	//for ( int i = 0; i < m; ++i )
	//	pthread_mutex_destroy(&mtx[i]);

	//pthread_mutex_destroy(&mtx);
	pthread_barrier_destroy(&br);
	
	free(th);
	free(arg);
	//free(mtx);

	return 0;
}
