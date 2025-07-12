#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	if ( argc < 2 ) 
		perror("please provide at least one argument");
	
	int n = atoi(argv[1]);
	int p_to_c[2], c_to_p[2];
	
	if ( pipe(p_to_c) == -1 ) 
		perror("error creating the pipe");
	
	if ( pipe(c_to_p) == -1 ) 
		perror("error creating the pipe");

	int cpid = fork();
	
	if ( cpid == -1 ) 
		perror("error creating the fork");
	else if ( cpid == 0 ) { 
		//child process
		//child reads from the parrent and writes to the parent
		// => close the write p_to_c
		// => close the read c_to_p
		close(p_to_c[1]); //close the write
		close(c_to_p[0]); //close the read
		double avg = 0;
		int a;
		
		for ( int i = 1; i <= n; ++i  ) {
			if (read(p_to_c[0], &a, sizeof(int)) < 0) {
				perror("error on read from parent");
				close(p_to_c[0]);
				close(c_to_p[1]);	
			}
			avg += a; 
		}
		
		avg = avg / n;
		
		if ( write(c_to_p[1], &avg, sizeof(double)) < 0 ) {
 			perror("error on write to parent");
		}
		
		//close the pipes
		close(p_to_c[0]);
		close(c_to_p[1]);
		exit(0);
		
	} else {
		//parrent process
		//writes to child the random numbers
		//=> close unused pipes 
		close(p_to_c[0]);
		close(c_to_p[1]);

		for ( int i = 1; i <= n; ++i ) {
			int a = random() % 100;
			printf("generated number: %d\n", a);

			if ( write(p_to_c[1], &a, sizeof(a)) < 0 ) {
				perror("error on write the number to child");
				close(p_to_c[1]);
				close(c_to_p[0]);
			}
		}
		wait(0); //wait for the child
		
		double avg;
		if ( read(c_to_p[0], &avg, sizeof(double)) < 0 ) 
			perror("error on reading the average from child");
		
		printf("average: %f\n", avg);
		
		close(c_to_p[0]);
		close(p_to_c[1]); 
	}

	return 0;
}

