#include <stdio.h>
#include <pthread.h>

int arr[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
//program care aduna numerele dupa cum ne-o aratat boian
//8 threaduri
//4 threaduri
//2 threaduri
pthread_barrier_t b;

//functia threadului care aduna
void *f(void *a) {
	int id = (int)(long)a;
	int k = 2;
	int n = 8;
	while ( n > 0 ) {
		if ( id < n ) 
			arr[k*id] += arr[k*id+k/2];
		
		//stam la bariera
		pthread_barrier_wait(&b);
		k *= 2;
		n /= 2;
	}
	return NULL;
}

int main() {
	int i;
	pthread_t t[8];
	pthread_barrier_init(&b, NULL, 8); //primeste 8 threaduri care sa astepte la ea

	for ( i = 0; i < 8; ++i ) 
		pthread_create(&t[i], NULL, f, (void *)(long)i);

	for ( i = 0; i < 8; ++i )
		pthread_join(t[i], NULL);

	pthread_barrier_destroy(&b);
	printf("%d\n", arr[0]);
	return 0;
}
