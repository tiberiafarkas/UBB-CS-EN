#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	(void) argc;
	(void) argv;
	int c1_to_c2[2], c2_to_c1[2];
	if (pipe(c1_to_c2) == -1)
		perror("error on creating pipe");
	
	if (pipe(c2_to_c1) == -1)
		perror("error on creating pipe");
	
	int c1, c2;
	c1 = fork();
	
	if ( c1 == -1 ) {
		perror("error on fork");
	} else if ( c1 == 0 ) {
		//child
		// 0 1
		srand(getpid());
		//we need to read from c2 and write to c2
		close(c1_to_c2[0]);
		close(c2_to_c1[1]);
		int n;
		
		if ( read(c2_to_c1[0], &n, sizeof(int)) < 0 ) {
			perror("c1: error on read from pipe\n");
		}

		printf("c1: read number: %d\n", n);

		while ( n != 10 ) {
			n = random() % 10 + 1;
			
			if ( write(c1_to_c2[1], &n, sizeof(int)) < 0 ) {
				perror("c1: error on write to pipe\n");
			}

			if ( n == 10 )
				break;

			if ( read(c2_to_c1[0], &n, sizeof(int)) < 0 ) {
				perror("c2: error on reading from pipe\n");
			}
			
			printf("c1: read number %d\n", n);
		}

		close(c1_to_c2[1]);
		close(c2_to_c1[0]);
		exit(0);
	}

	c2 = fork();
	
	if ( c2 == -1 ) {
		perror("error on fork");
	} else if ( c2 == 0 ) { 
		//child 2
		srand(getpid());
		close(c1_to_c2[1]);
		close(c2_to_c1[0]);
	
		int n = 5;
	
		while ( n != 10 ) {
			n = random() % 10 + 1;
			
			if ( write(c2_to_c1[1], &n, sizeof(int)) < 0 ) {
				perror("c2: error on write to pipe\n");
			}
			
			if ( n == 10 ) 
				break;

			if ( read(c1_to_c2[0], &n, sizeof(int)) < 0 ) {
				perror("c1: error on read from pipe\n");
			}

			printf("c2: read number %d\n", n);

		}

		close(c2_to_c1[1]);
		close(c1_to_c2[0]);
		exit(0);

	}

	wait(0);
	wait(0);
	return 0;
}
