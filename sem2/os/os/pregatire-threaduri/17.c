//Write a C program that reads a number N and creates 2 threads. One of the threads will generate an even number and will append it to an array that is passed as a parameter to the thread. The other thread will do the same, but using odd numbers. Implement a synchronization between the two threads so that they alternate in appending numbers to the array, until they reach the maximum length N.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mtx;
pthread_cond_t c;

typedef struct {
	int *arr;
	int *turn;
	int *n;
} ceva;


void *par(void *arg) {
	ceva d = *((ceva*)arg);
	
	pthread_mutex_lock(&mtx);

	while ( *(d.turn) % 2 != 0 ) {
		pthread_cond_wait(&c, &mtx);
	} 

	while ( *(d.turn) < *(d.n) ) {
		int nr = random() % 99 * 2;
		d.arr[*(d.turn)] = nr;
		*(d.turn) += 1;

		printf("T1: %d\n", nr);

		pthread_cond_signal(&c);
		
		while ( *(d.turn) % 2 != 0 && *(d.turn) < *(d.n) )
			pthread_cond_wait(&c, &mtx);
	}

	pthread_cond_signal(&c);
	pthread_mutex_unlock(&mtx);
	return NULL;
}

void *impar(void *arg) {
	ceva d = *((ceva*)arg);

	pthread_mutex_lock(&mtx);

	while ( *(d.turn) % 2 != 1 ) {
		pthread_cond_wait(&c, &mtx);
	}
		
	while( (*d.turn) < (*d.n) ) {
		int nr = random() % 99;
		nr = nr + ( nr + 1 ) % 2;
		d.arr[(*d.turn)] = nr;
		(*d.turn) += 1;
	
		printf("T2: %d\n", nr);

		pthread_cond_signal(&c);

		while ( (*d.turn) % 2 != 1 && *(d.turn) < *(d.n) ) 
			pthread_cond_wait(&c, &mtx);
	}

	pthread_cond_signal(&c);
	pthread_mutex_unlock(&mtx);
	return NULL;
}


int main(int argc, char *argv[]) {
	if ( argc != 2 ) {
		perror("plese provide one argument");
	}

	int n = atoi(argv[1]);
	srand(time(0));
	
	pthread_mutex_init(&mtx, NULL);
	pthread_cond_init(&c, NULL);

	pthread_t th[2];
	int *arr = malloc(n*sizeof(int));
	int turn = 0;
	ceva arg[2];
	
	arg[0].arr = arr;
	arg[0].turn = &turn;
	arg[0].n = &n;

	arg[1].arr = arr;
	arg[1].turn = &turn;
	arg[1].n = &n;

	pthread_create(&th[0], NULL, par, (void *) &arg[0]);
	pthread_create(&th[1], NULL, impar, (void *) &arg[1]);

	pthread_join(th[0], NULL);
	pthread_join(th[1], NULL);	

	pthread_mutex_destroy(&mtx);
	pthread_cond_destroy(&c);
	
	return 0;
}
