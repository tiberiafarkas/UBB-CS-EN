#include <stdio.h>
#include <pthread.h>

void *f(void* a) {
	(void) a;
	for ( int i = 0; i < 1000; ++i )
		printf("threaduletz\n");
	return NULL;
}

int main() {
	pthread_t t;
	pthread_create(&t, NULL, f, NULL);
	for ( int i = 0; i < 1000; ++i )
		printf("mainuletz\n");
	pthread_join(t, NULL); //daca nu facem join pe threaduri comportamentul este nedefinit SO JOIN IS FCKING MANDATORY!!
	

	return 0;
}

