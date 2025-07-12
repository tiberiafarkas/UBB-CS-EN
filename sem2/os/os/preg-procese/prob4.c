#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	struct timeval tv1, tv2;
	if ( argc < 2 ) 
		perror("provide at least 1 argument");
	
	gettimeofday(&tv1, NULL);
	int f = fork();

	if ( f < 0 ) 
		perror("error creating fork");
	else if ( f == 0 ) {
		if ( execv(argv[1], argv + 1) == -1 ) { 
			perror("error executing the given command");
			exit(0);
		}
	} else {
		wait(0);
		gettimeofday(&tv2, NULL);
		printf("Total time = %f seconds\n", (double)(tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec));
	}


	return 0;
}
