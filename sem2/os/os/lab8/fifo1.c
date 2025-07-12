#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
	int f = fork();
	if ( -1 == f ) { 
		perror("Error on fork");
		exit(1);
	} else if ( 0 == f ) {	//aici e procesul fiu
		int w_fifo = open("./fifo", O_WRONLY);
		
		FILE *cmd_out = popen("ps -ef | awk 'NR > 1 {print $5}'", "r"); //i-am dat r pentru ca vreau sa citesc din outputul comenzii
		char *buff = malloc(101 * sizeof(char));
		int k = 0;

		while ( ( k = fread(buff, 1, 100, cmd_out) ) > 0 ) { //fread returneaza cati bytes sunt cititi
			//buff[k] = 0;  //ne asiguram ca sirul are la final caracterul null asa ca il fortam noi sa fie just in case - asta foloseam atunci cand parintele nu facea nimic decat wait
			
			write(w_fifo, &k, sizeof(int));  
			write(w_fifo, buff, k);
			//printf("%s", buff);
		}
		
		write(w_fifo, &k, sizeof(int));
		free(buff);
		pclose(cmd_out);
		close(w_fifo);
		exit(0);

	} else {
		//aici lucreaza parintele
		int r_fifo = open("./fifo", O_RDONLY);

		char *buff = malloc(101 * sizeof(char));
	      	int k = -1;
		while ( k != 0 ) {
			read(r_fifo, &k, sizeof(int));
			if ( k == 0 )
				break;
			
			read(r_fifo, buff, k);
			buff[k] = 0;
			printf("%s", buff);
		}

 		close(r_fifo);
		wait(NULL);		
	}
	return 0;
}
