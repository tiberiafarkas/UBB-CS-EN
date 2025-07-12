#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	int p[2];
	if ( -1 == pipe(p) ) {
		perror("error creating pipe");
	}

	int f = fork();
	if ( -1 == f ) { 
		perror("Error on fork");
		exit(1);
	} else if ( 0 == f ) {	//aici e procesul fiu
		close(p[0]); //inchidem capetele pipeului pentru ca pipeul asteapta ca cine are dreptul sa-i scrie

		FILE *cmd_out = popen("ps -ef | awk 'NR > 1 {print $5}'", "r"); //i-am dat r pentru ca vreau sa citesc din outputul comenzii
		char *buff = malloc(101 * sizeof(char));
		int k = 0;

		while ( ( k = fread(buff, 1, 100, cmd_out) ) > 0 ) { //fread returneaza cati bytes sunt cititi
			//buff[k] = 0;  //ne asiguram ca sirul are la final caracterul null asa ca il fortam noi sa fie just in case - asta foloseam atunci cand parintele nu facea nimic decat wait
			
			write(p[1], &k, sizeof(int));

			if ( k > 0 )  
				write(p[1], buff, k);
			//printf("%s", buff);
		}
		
		write(p[1], &k, sizeof(int));
		free(buff);
		pclose(cmd_out);
		close(p[1]);
		exit(0);
	} else {
		//aici lucreaza parintele
		close(p[1]);
		char *buff = malloc(101 * sizeof(char));
	      	int k = -1;
		while ( k != 0 ) {
			read(p[0], &k, sizeof(int));
			if ( k == 0 )
				break;
			
			read(p[0], buff, k);
			buff[k] = 0;
			printf("%s", buff);
		}

 		close(p[0]);
		wait(NULL);		
	}
	return 0;
}
