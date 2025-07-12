#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void read_from_fd(int fd, int max, char *buf) {
    int read_bytes = 0;
    while(read_bytes < max) {
        int k;
        if((k = read(fd, buf + read_bytes, (max - read_bytes) * sizeof(char))) > 0) {
            read_bytes += k;
        }
    }
}


int main(int argc, char *argv[]) {
	if ( argc < 2 ) {
		perror("you must provide at least one argument");
		exit(1);
	}

	
	if ( mkfifo("./pb8a", 0600) < 0 ) {
		perror("error making the first fifo");
		exit(1);
	}

	if ( mkfifo("./prob8b", 0600) < 0 ) {  
		perror("error making the second fifo");
		exit(1);
	}

	int w_fifo = open("./pb8a", O_WRONLY);
	if ( w_fifo == -1 ) {
		perror("error opening fifo");
		exit(1);
	}
	
	int r_fifo = open("./prob8b", O_RDONLY);
	if ( r_fifo == -1 ) {
		perror("error opening fifo");
		exit(1);
	}

	int len = 0;

	for ( int i = 1; i < argc; ++i ) {
		len += strlen(argv[i]) + 1;
	}

	char *rez = malloc((len + 1) * sizeof(char));
 	memset(rez, 0, (len + 1) * sizeof(char)); 	
	for ( int i = 1; i < argc; ++i ) {
		int size = strlen(argv[i]);
		if ( write(w_fifo, &size, sizeof(int)) < 0 ) 
			perror("error on writing the length");

		if ( write(w_fifo, argv[i], size * sizeof(char)) < 0 ) 
			perror("error on writing the string");

		if ( read(r_fifo, &size, sizeof(int)) < 0 ) 
			perror("error on reading the length");
		
		char *buf = malloc((size+1) * sizeof(char));

		read_from_fd(r_fifo, size, buf);
		buf[size] = 0;
		
		strcat(rez, buf);
		strcat(rez, " "); 
		
		free(buf);
	}

	//we need to pass a signal to let the other process know it wont receive any more arguments
	
	int stop = -1;
	if ( write(w_fifo, &stop, sizeof(int)) < 0 ) 
		perror("error passing the stop");
	
	rez[len] = 0;
	printf("%s\n", rez);
	free(rez);
	
	close(w_fifo);
	close(r_fifo);
	
	if ( unlink("./pb8a") < 0 ) 
		perror("error deleting the fifo");
	
	if ( unlink("./prob8b") < 0 ) 
		perror("error deleting the fifo");

	return 0;

}
