#include <stdio.h>
#include <stdlib.h>                                                   
#include <unistd.h>                                                   
#include <sys/wait.h>
#include <string.h>

int main(int argc, char* argv[]) {
	for ( int i = 1; i < argc; ++i ) {
		int p[2], pID[2];
    	if ( pipe(p) == -1 ) {
        	perror("error creating pipe");
    	}
		if ( pipe(pID) == -1 ) {
			perror("error creating pipe");
		}
		
		int f = fork();	
		
		if ( f == -1 ) {
			perror("Error on fork");
		}

		if ( f == 0 ) {
			close(p[0]);	//close the read
			close(pID[0]);
			//child process
			
			int cPID = getpid();

			if ( execl(argv[i], argv[i], NULL) == -1 ) {
				//the command couldn't have been processed
								
				int k = 1;
				write(p[1], &k, sizeof(int));
				write(pID[1], &cPID, sizeof(int));

				exit(0); //daca exec nu merge, nu se inchide procesul si raman zombieurile deci trebuie dat exit 
 			} else {
				int k = 0;
				write(p[1], &k, sizeof(int)); //daca exec ruleaza cu succes se inchide automat
				//write(pID[1], &cPID, sizeof(int));
			}
		} else {
  			//parrent process
			close(p[1]); //close the write
			close(pID[1]);

			int k, pid;
			read(p[0], &k, sizeof(int));
			read(pID[0], &pid, sizeof(int));			

			//forkul returneaza pidul copilului
		
			if ( k == 1 ) {
				printf("Unable to run %s pid: %d\n", argv[i], pid);
			}

			close(p[0]);
			wait(NULL);
		}
	}
	return 0;
}
