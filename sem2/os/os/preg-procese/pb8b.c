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

int main() {
	int r_fifo = open("./pb8a", O_RDONLY);
	int w_fifo = open("./prob8b", O_WRONLY);

	if ( r_fifo < 0 ) 
		perror("error opening first fifo");
	
	if ( w_fifo < 0 ) 
		perror("error opening second fifo");
	
	while(1) {
		int len;
		if ( read(r_fifo, &len, sizeof(int)) < 0 ) 
			perror("error reading the length");
		
		if ( len < 0 ) {
			printf("the processes stop");
			break;
		}

		char *buf = malloc((len + 1) * sizeof(char));
		read_from_fd(r_fifo, len, buf); 


		for ( int j = 0; j < len; ++j ) {
			if ( buf[j] >= 'a' && buf[j] <= 'z' ) 
				buf[j] = buf[j] - 32;
		}
		buf[len] = 0;
		
		if ( write(w_fifo, &len, sizeof(int)) < 0 ) 
			perror("error writing the length");	

		if ( write(w_fifo, buf, len * sizeof(char)) < 0 ) 
			perror("error writing the changed string");
		
		free(buf);
	}

	close(r_fifo);
	close(w_fifo);
	return 0;
}
