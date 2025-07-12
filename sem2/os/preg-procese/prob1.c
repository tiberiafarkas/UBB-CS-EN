#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
	if ( argc != 2 ) 
		perror("Sunt necesare 2 argumente");

	int n = atoi(argv[1]);

	for ( int i = 1; i <= n; ++i ) {
		int f = fork();
		if ( f < 0 ) {
			perror("Eroare la fork");
		}
		else if ( f == 0 ) {
			//avem copil
			printf("Procesul copil:\n");
			printf("Pid copil: %d\n", getpid());
			printf("Pid parinte: %d\n", getppid());
			exit(0);
		} 
		else {
			//avem parinte
			printf("Procesul parinte:\n");
			printf("Pid parinte: %d\n", getpid());
			printf("Pid copil: %d\n", f);
		}
		//wait(0); aici asteapta pana se termina fiecare proces copil si atunci nu lucreaza procesele in paralel
	}

	for ( int i = 1; i <= n; ++i ) 
		wait(0);

	return 0;
}
