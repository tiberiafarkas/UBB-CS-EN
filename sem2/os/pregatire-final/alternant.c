#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

pthread_mutex_t ma, mb;

void* fa(void* args){
    for(int i=0; i<10000; i++) {
        pthread_mutex_lock(&ma);
        printf("a\n");
        pthread_mutex_unlock(&mb);
    }
    return NULL;
}

void* fb(void* args){
    for(int i=0; i<10000; i++) {
        pthread_mutex_lock(&mb);
        printf("b\n");
        pthread_mutex_unlock(&ma);
    }
    return NULL;
}

int main(){
    pthread_t ta, tb;
    pthread_mutex_init(&ma, NULL);
    pthread_mutex_init(&mb, NULL);
	pthread_mutex_lock(&mb);
    pthread_create(&ta, NULL, fa, NULL);
    pthread_create(&tb, NULL, fb, NULL);
    pthread_join(ta, NULL);
    pthread_join(tb, NULL);
    pthread_mutex_destroy(&ma);
    pthread_mutex_destroy(&mb);
    return 0;
}
