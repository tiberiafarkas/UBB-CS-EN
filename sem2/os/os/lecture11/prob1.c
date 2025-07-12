/* padure -> stup -> albinele produc miere
dupa ce albina si-a produs capacitatea maxima de miere, un grup de ursi vinein padure si incep sa manance miere (albinele inca produc)
daca ursii termina mierea, padurarul este trezit si aduce din camara miere
ca sa nu stricam stupul, doar 3 ursi pot manca de o data

albinele -> threaduri
ursii -> threaduri / rezolvam cu semafoare
padurarul -> threaduri / variabila conditionala
mierea -> intreg 
cand ursul n-are miere -> trezeste padurarul
ne trebe mutex ca sa protejam mierea
la bariera stau si ursii si albinele pana cand toate albinele ajung la majorat

in varianta cu bariera scoatem tot ce e legat de nealbine

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int miere;
int nealbine = 100;

pthread_mutex_t m;
pthread_cond_t c;
pthread_cond_t c2;
//pthread_barrier_t b;
sem_t s;

void* albina(void* a) {
	int k = 0;
	while(1) {
		pthread_mutex_lock(&m);
		miere++;
		pthread_mutex_unlock(&m);
		
		k++;
		printf("+");
		
		if ( k == 30 ) {
			pthread_mutex_lock(&m);
			nealbine--;
			printf("#\n");
			if ( nealbine == 0 ) {
				pthread_cond_broadcast(&c2);
			} 
			pthread_mutex_unlock(&m);
			//pthread_barrier_wait(&b);
		}
		
	}
	return NULL;
}

void* urs(void* a) {
//	pthread_barrier_wait(&b);

	pthread_mutex_lock(&m);
	while(nealbine > 0) {
		pthread_cond_wait(&c2, &m);
	}
	pthread_mutex_unlock(&m);
	
	while(1) {
		sem_wait(&s);
		pthread_mutex_lock(&m);

		if ( miere < 50 ) {
			printf("A");
			pthread_mutex_unlock(&m);
			pthread_cond_signal(&c);
			sem_post(&s);
			continue;
		}
		
		miere -= 50;
	
		pthread_mutex_unlock(&m);
		sem_post(&s);
		
		printf("-");
	}	

	return NULL;
}

void* padurar(void* a) {
	while(1) {
		pthread_mutex_lock(&m);

		while ( miere >= 50 ) {
			pthread_cond_wait(&c, &m);
		}

		miere += 200;
		pthread_mutex_unlock(&m);
		printf("M");
		
	}

	return NULL;
}

int main() {
	int i;
	pthread_t albine[100];
	pthread_t ursi[5];
	pthread_t sefu_la_miere;

	pthread_mutex_init(&m, NULL);
	pthread_cond_init(&c, NULL);
	pthread_cond_init(&c2, NULL);
	sem_init(&s, 0, 3);

	for ( i = 0; i < 100; ++i ) 
		pthread_create(&albine[i], NULL, albina, NULL);

	for ( i = 0; i < 5; ++i ) 
		pthread_create(&ursi[i], NULL, urs, NULL);

	pthread_create(&sefu_la_miere, NULL, padurar, NULL);
	

	for ( i = 0; i < 100; ++i ) 
		pthread_join(albine[i], NULL);

	for ( i = 0; i < 5; ++i ) 
		pthread_join(ursi[i], NULL);
	
	pthread_join(sefu_la_miere, NULL);

	pthread_mutex_destroy(&m);
	pthread_cond_destroy(&c);
	pthread_cond_destroy(&c2);
	sem_destroy(&s);

	return 0;
}
