#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	(void) argc;
	(void) argv;
	
	int r_fifo = open("./p7a", O_RDONLY);
	if ( r_fifo == -1 ) {
		perror("error on opening fifo");
		exit(1);
	}

	int w_fifo = open("./p7b", O_WRONLY);
	if ( w_fifo == -1 ) {
		perror("error on opening fifo");
		exit(1);
	}

	srandom(getpid());

	int n = 0;
	
	while ( n != 10 ) {
		
		if ( read(r_fifo, &n, sizeof(int)) < 0 ) {
			perror("error on read from A");
			break;
		}

		printf("B receives: %d\n", n);

		n = random() % 10 + 1;
		if ( n == 10 ) 
			break;		

		if ( write(w_fifo, &n, sizeof(int)) < 0 ) {
			perror("error on write to A");
			break;
		}		

		printf("B sends: %d\n", n);
	}

	close(r_fifo);	
	close(w_fifo);
	return 0;
}
