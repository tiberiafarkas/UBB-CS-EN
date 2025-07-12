//Write a C program that reads a number n from standard input and generates an array s of n random integers between 0 and 1000. After the array is created, the main process creates n + 1 threads. Each of the first n threads repeats the following steps until the array is sorted in ascending order:
//- generates 2 random integers between 0 and n-1, called i and j
//- if i < j and s[i] > s[j], exchanges the values of s[i] and s[j]
//- if i > j and s[i] < s[j], exchanges the values of s[i] and s[j]
//The n+1th thread waits until the array is sorted, after which it prints it to the console. Use appropriate synchronization mechanisms.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct{
	int n, id;
	int *arr;
	pthread_mutex_t *mtx;
	pthread_cond_t *c;
} data;

int flag;

void *f(void *arg) {
	data d = *((data *) arg);

 	while ( 1 ) {
		int sorted = 1;

		for ( int i = 0; i < d.n && sorted; ++i )
			for ( int j = i + 1; j < d.n && sorted; ++j ) 
				if ( d.arr[i] > d.arr[j] ) 
					sorted = 0;
		pthread_mutex_lock(d.mtx);
		
		if ( sorted ) {
			flag = 1;		
			pthread_cond_signal(d.c);
			pthread_mutex_unlock(d.mtx);
			break;
		}
	
		int i = random() % d.n;
		int j = random() % d.n;
			
		if ( ( i < j && d.arr[i] > d.arr[j] ) || ( i > j && d.arr[i] < d.arr[j] ) ) {
			 printf("Thread %d reverses the numbers on positions %d and %d: %d %d\n", d.id, i, j, d.arr[i], d.arr[j]);
			int aux = d.arr[i];
			d.arr[i] = d.arr[j];
			d.arr[j] = aux;
		} 

		pthread_mutex_unlock(d.mtx);	
	}
	

	return NULL;
}

void *printer(void *arg) {
	data d = *((data *) arg);
	
	pthread_mutex_lock(d.mtx);

	while ( !flag ) {
		pthread_cond_wait(d.c, d.mtx);
	}

	for ( int i = 0; i < d.n; ++i )
		printf("%d ", d.arr[i]);

	pthread_mutex_unlock(d.mtx);
	return NULL;	
}

int main(int argc, char *argv[]) {
	if ( argc != 2 ) {
		perror("please provide one argument");
		exit(0);
	}
	
	int n = atoi(argv[1]);
    srandom(time(NULL));	
	int *arr = malloc(n * sizeof(int));
	for ( int i = 0; i < n; ++i ) {
		int nr = random() % 1001;
		arr[i] = nr;
		printf("%d ", nr);
	}
	
	printf("\n");

	pthread_t *th = malloc((n + 1) * sizeof(pthread_t));
	pthread_mutex_t mtx;
	pthread_cond_t c;
	
	pthread_mutex_init(&mtx, NULL);
	pthread_cond_init(&c, NULL);

	data *arg = malloc((n + 1) * sizeof(data));

	for ( int i = 0; i < n; ++i ) {
		arg[i].mtx = &mtx;
		arg[i].c = &c;
		arg[i].id = i;
		arg[i].n = n;
		arg[i].arr = arr;		

		pthread_create(&th[i], NULL, f, (void *) &arg[i]);
	}

	arg[n].mtx = &mtx;
	arg[n].c = &c;
	arg[n].id = n;
	arg[n].n = n;
	arg[n].arr = arr;

	pthread_create(&th[n], NULL, printer, (void *) &arg[n]);

	for ( int i = 0; i < n + 1; ++i ) 
		pthread_join(th[i], NULL);

	pthread_mutex_destroy(&mtx);
	pthread_cond_destroy(&c);
	
	free(arg);
	free(th);
	free(arr);	

	return 0;
}
