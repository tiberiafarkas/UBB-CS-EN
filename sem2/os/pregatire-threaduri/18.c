//Create a C program that converts all lowecase letters from the command line arguments to uppercase letters and prints the result. Use a thread for each given argument.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

typedef struct{
	char *str;
	pthread_mutex_t *mtx;
} data;

void *f(void *arg) {
	data d = *((data*) arg);
	printf("initial string %s\n", d.str);	
	pthread_mutex_lock(d.mtx);
	for ( size_t i = 0; i < strlen(d.str); ++i ) {
		if ( d.str[i] >= 'a' && d.str[i] <= 'z' ) 
			d.str[i] -= 32;
	}
	pthread_mutex_unlock(d.mtx);

	printf("the string is: %s\n", d.str);
	free(d.str);
	return NULL;
}

int main(int argc, char *argv[]) {
	if ( argc < 2 ) {
		perror("no arguments provided");
		exit(1);
	}
	
	int n = argc - 1;
	pthread_t *th = malloc(n * sizeof(pthread_t));
	pthread_mutex_t *mtx = malloc(sizeof(pthread_mutex_t));
	data *arg = malloc(n * sizeof(data));	

	pthread_mutex_init(mtx, NULL);
	
	for ( int i = 0; i < n; ++i ) {
		int len = strlen(argv[i+1]);
			
		printf("%s\n", argv[i+1]);

		arg[i].str = malloc((len + 1) * sizeof(char));
		memset(arg[i].str, 0, len+1);
		strcpy(arg[i].str, argv[i+1]);

//		arg[i].str = argv[i+1]; nu merge asa incearca sa dea free la ce e pe argv[i+1] care e pe stack
		arg[i].mtx = mtx;
		
		pthread_create(&th[i], NULL, f, (void *) &arg[i]);
	}

	for ( int i = 0; i < n; ++i ) {
		pthread_join(th[i], NULL);
	}
	
	pthread_mutex_destroy(mtx);
	free(th);
	free(arg);
	free(mtx);

	return 0;
}
