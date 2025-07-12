#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mtx;
pthread_cond_t c;
pthread_barrier_t b;
int n, m, count;

typedef struct {
    int idx;
    int *potato;
    //pthread_mutex_t *mt	x;
} data;

void *f(void *arg) {
    data *d = (data*) arg;
	pthread_barrier_wait(&b);
    while(1) { 

		pthread_mutex_lock(&mtx);		
	
		while (*(d->potato) < 0) 
			pthread_cond_wait(&c, &mtx);
		
		if ( count == 1 ) {
			printf("We have a winner!!! Thread: %d\n", d->idx);
			pthread_cond_signal(&c);
			pthread_mutex_unlock(&mtx);
			break;
		}

        // *((*d).potato)
        //if(*(d->potato) < 0) {
        //    pthread_mutex_unlock(&mtx);
        //    break;
       // }

        int sub = rand() % 91 + 10;
        //printf("Thread with id %d has subtracted %d from %d\n", d->idx, sub, *(d->potato));

        *(d->potato) -= sub;
        if(*(d->potato) < 0) {
            printf("Thread with id %d has exploded!\n", d->idx);
            pthread_mutex_unlock(&mtx);
			pthread_cond_signal(&c);
            break;
        }

        pthread_mutex_unlock(&mtx);
        int sleep = rand() % 101 + 100;
        usleep(sleep * 100);

    }

    return NULL;

}

void *mama(void *arg) {
	data *d = (data*) arg;

	while (1) {
		pthread_mutex_lock(&mtx);	
	
		if ( count == 1 ) {
            printf("Game ended!!\n");
          	pthread_cond_broadcast(&c);
			pthread_mutex_unlock(&mtx);
            break;
        }

		while(*(d->potato) > 0) {
			pthread_cond_wait(&c, &mtx);
		}
	
		*(d->potato) = rand() % 9001 + 1000;
		
		//if ( count == 1 ) {
		//	printf("Game ended!!\n");
		//	pthread_cond_broadcast(&c);
		//	pthread_mutex_unlock(&mtx);
		//	break;
		//}

		count--;
		pthread_cond_broadcast(&c);
		pthread_mutex_unlock(&mtx);
	}
	return NULL;
}

int main(int argc, char *argv[]){
    if(argc != 2) {
        perror("Please provide exactly one argument!\n");
        exit(0);
    }

    m = atoi(argv[1]);
    n = m - 1;
	count = n;
	srand(getpid());
    int potato = rand() % 9001 + 1000;

    printf("Main has generated %d\n", potato);

    pthread_t th[m];
    data *args = malloc(sizeof(data) * m);
    //pthread_mutex_t mtx;
    pthread_mutex_init(&mtx, NULL);
	pthread_barrier_init(&b, NULL, n);
	pthread_cond_init(&c, NULL);

    for(int i = 0; i < n; i++) {
        args[i].idx = i + 1;
        args[i].potato = &potato;
        //args[i].mtx = &mtx;
        pthread_create(&th[i], NULL, f, (void *) &args[i]);
    }

	args[n].potato = &potato;
	pthread_create(&th[n], NULL, mama, (void *) &args[n]);

    for(int i = 0; i < m; i++) {
        pthread_join(th[i], NULL);
    }

    pthread_mutex_destroy(&mtx);
	pthread_barrier_destroy(&b);
	pthread_cond_destroy(&c);
    free(args);

    return 0;
}
