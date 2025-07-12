#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	(void) argc;
	(void) argv;

	int w_fifo = open("./p7a", O_WRONLY);
	
	if ( w_fifo == -1 ) { 
		perror("error on opening w_fifo in A"); 
		exit(1);
	}

	int r_fifo = open("./p7b", O_RDONLY);

	if ( r_fifo == -1 ) {
		perror("error on opening r_fifo in A");
		exit(1);
	}

	srandom(getpid());

	int n = 0;

	while ( n != 10 ) {
		n = random() % 10 + 1;
		
		if ( write(w_fifo, &n, sizeof(int)) < 0 ) {
			perror("error on write to child");
			break;
		}

		if ( n == 10 ) 
			break;

		printf("A sends: %d\n", n);
		
		if ( read(r_fifo, &n, sizeof(int)) < 0 ) { 
			perror("error on read from child");
			break;
		}

		printf("A receives: %d\n", n);
	}

	close(w_fifo);
	close(r_fifo);

	
	return 0;
}
