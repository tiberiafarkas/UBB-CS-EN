#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <string.h>

pthread_mutex_t *mtx;

struct original {
    FILE *f;
    int no_lines, no_words, no_char;
};

void *fun(void *o) {
	char *line = NULL;
	size_t len = 0;
	int nread;	
	struct original *p = (struct original *) o;
	while ( 1 ) {
		pthread_mutex_lock(mtx);
		
		nread = getline(&line, &len, p->f);
		
		if ( nread == -1 ) {
			pthread_mutex_unlock(mtx);
			break;
		}	 

		p->no_char += nread;
		p->no_lines += 1;

		char *po = strtok(line, " \t\r\n");
		while ( po != NULL ) {
			p->no_words += 1;
			po = strtok(NULL, " \t\r\n");
		}

		//printf("Number of lines %d\nNumber of words %d\nNumber of characters %d\n\n", p->no_lines, p->no_words, p->no_char);
		pthread_mutex_unlock(mtx);	
	
	}

	free(line);
	return NULL;
}

int main(int argc, char* argv[]) {
	if ( argc < 3 ) {
		perror("not enough arguments");
	}

	FILE *f = fopen(argv[1], "r");

	if ( f == NULL ) {
		perror("error opening the file");
	}
	mtx = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mtx, NULL);

	int n = atoi(argv[2]), i;
	pthread_t th[10];
	
	struct original o;
	o.f = f;
	o.no_lines = 0;
	o.no_words = 0;
	o.no_char = 0;

	for ( i = 0; i < n; ++i ) 
		pthread_create(&th[i], NULL, fun, (void *) &o);

	for ( i = 0; i < n; ++i ) 
		pthread_join(th[i], NULL);
	
	printf("Number of lines %d\nNumber of words %d\nNumber of characters %d\n", o.no_lines, o.no_words, o.no_char);

	pthread_mutex_destroy(mtx);
	
	free(mtx);
	fclose(f);
	return 0;
}
