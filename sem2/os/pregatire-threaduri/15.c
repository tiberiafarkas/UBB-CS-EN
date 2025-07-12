//Scrieti un program care primeste la linia de comanda siruri de caractere. Pentru fiecare sir de caractere programul creeaza un thread care calculeaza numarul de cifre, litere si caractere speciale (orice nu e litera sau cifra). Programul principal asteapta ca thread-urile sa isi incheie executia si afiseaza rezultatele totale (numarul total de cifre, litere si caractere speciale din toate argumentele primite la linia de comanda) si apoi se incheie. Folositi sincronizare eficienta. Nu folositi variabile globale.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

typedef struct{
	int *let, *dig, *car;
	pthread_mutex_t *mtx;
	char *str;
} data;

void *f(void *arg) {
	data d = *((data *) arg);
	int l = 0, dg = 0, c = 0;
	
	for ( size_t i = 0; i < strlen(d.str); ++i ) {
		if ( ( d.str[i] >= 'a' && d.str[i] <= 'z' ) || (d.str[i] >= 'A' && d.str[i] <= 'Z' ) ) 
			l++;
		else if ( d.str[i] >= '0' && d.str[i] <= '9' )
			dg++;
		else 
			c++;	
	}

	pthread_mutex_lock(&d.mtx[0]);
	*(d.let) += l;
	pthread_mutex_unlock(&d.mtx[0]);

	pthread_mutex_lock(&d.mtx[1]);
	*(d.dig) += dg;
	pthread_mutex_unlock(&d.mtx[1]);

	pthread_mutex_lock(&d.mtx[2]);
	*(d.car) += c;
	pthread_mutex_unlock(&d.mtx[2]);

	return NULL;
}

int main(int argc, char *argv[]) {
	if (argc < 2) {
		perror("provide at least one argument");
	}

	int	n = argc - 1;

	pthread_t *th = malloc(n * sizeof(pthread_t));
	data *args = malloc(n * sizeof(data));
	pthread_mutex_t *mtx = malloc(3 * sizeof(pthread_mutex_t));
	
	int *let = malloc(sizeof(int));
	int *dig = malloc(sizeof(int));
	int *car = malloc(sizeof(int));

	*let = 0, *dig = 0, *car = 0;

	for ( int i = 0; i < 3; ++i ) {
		pthread_mutex_init(&mtx[i], NULL);
	}

	for ( int i = 0; i < n; ++i ) {
		args[i].let = let;
		args[i].dig = dig;
		args[i].car = car;
		args[i].str = argv[i+1];
		args[i].mtx = mtx;

		pthread_create(&th[i], NULL, f, (void *) &args[i]);
	}

	for ( int i = 0; i < n; ++i ) { 
		pthread_join(th[i], NULL);
	}

	printf("Total number of letters: %d\nTotal number of digits: %d\nTotal number of characters: %d\n", *let, *dig, *car);

	for ( int i = 0; i < 3; ++i ) {
		pthread_mutex_destroy(&mtx[i]);
	}

	free(th);
	free(args);
	free(mtx);
	free(let);
	free(dig);
	free(car);
	
	return 0;
}
		
	
