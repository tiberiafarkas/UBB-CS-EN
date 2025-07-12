#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void createProc(int n, int curr) {
	if ( curr == n ) {
		printf("all processes have been created\n");
		return;
	}
	int f = fork();
	if ( f < 0 ) 
		perror("error creating fork");
	else if ( f == 0 ) { //proces copil
		printf("process: %d\n", curr+1);
		createProc(n, curr+1);
		exit(0);
	}
	wait(0);
}

int main(int argc, char *argv[]) {
	if ( argc != 2 ) 
		perror("2 arguments must be provided");
	
	int n = atoi(argv[1]);
	createProc(n, 0);

	return 0;
}
