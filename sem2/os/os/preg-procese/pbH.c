/*
Procesul parinte primeste un sir de caractere fara spatii de la stdin si face doi copii carora le trimite sirul.
Unul dintre copii pastreaza doar vocalele din sir si trimite noul sir la parinte
Celalalt copil pastreaza doar cifrele si trimite noul sir la parinte
parintele afiseaza la final cele doua siruri
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

void read_from_fd(int fd, int max, char* buf) {
	int read_bytes = 0;
	while ( read_bytes < max ) {
		int k = read(fd, buf + read_bytes, (max - read_bytes) * sizeof(char));
		if ( k > 0 ) 
			read_bytes += k;
	}
}


int main(int argc, char *argv[]) {
	(void) argc;
	(void) argv;
	//if ( argc < 2 ) {
	//	perror("you must provide an argument");
	//	exit(1);
	//}

	//int len = strlen(argv[1]);
	int p_to_c1[2], p_to_c2[2], c1_to_p[2], c2_to_p[2];
	
	if ( pipe(p_to_c1) < 0 ) {
		perror("error on creating the pipe");
		exit(1);
	}

	if ( pipe(p_to_c2) < 0 ) {
        perror("error on creating the pipe");
        exit(1);
    }

	if ( pipe(c1_to_p) < 0 ) {
        perror("error on creating the pipe");
        exit(1);
    }

	if ( pipe(c2_to_p) < 0 ) {
        perror("error on creating the pipe");
        exit(1);
    }
	
	int c1 = fork();
	
	if ( c1 == -1 ) { 
		perror("error creating the first chil");
		exit(1);
	} else if ( c1 == 0 ) {
		//citeste de la parinte si ii scrie la parinte
		close(p_to_c2[0]); close(p_to_c2[1]);
		close(c2_to_p[0]); close(c2_to_p[1]);
		close(p_to_c1[1]);
		close(c1_to_p[0]);
		
		int l;
		if ( read(p_to_c1[0], &l, sizeof(int)) < 0 ) {
			perror("error reading the length");
			exit(1);
		}

		char* buf = malloc((l + 1) * sizeof(char));
		
		read_from_fd(p_to_c1[0], l, buf);
		
		//if ( read(p_to_c1[0], buf, l * sizeof(char)) < 0 ) {
		//	perror("error reading the string");
		//	exit(1);	
		//}

		char* nb = malloc((l + 1) * sizeof(char));
		memset(nb, 0, (l + 1) * sizeof(char));
		int l2 = 0;

		for ( int i = 0; i < l; ++i ) {
 			if ( strchr("aeiouAEIOU", buf[i]) ) {
				nb[l2] = buf[i];
				l2++;
			}
		} 

		nb[l2] = 0; 
	
		if ( write(c1_to_p[1], &l2, sizeof(int)) < 0 ) {
			perror("error writing the length to parent");
			exit(1);
		}

		if ( write(c1_to_p[1], nb, l2 * sizeof(char)) < 0  ) { 
			perror("error writing the string to parent");
			exit(1);
		}
	
		free(buf);
		free(nb);
		close(c1_to_p[1]);
		close(p_to_c1[0]);	
		exit(0);
	}

	int c2 = fork();

	if ( c2 == -1 ) {
		perror("error creating the second child");
		exit(1);
	} else if ( c2 == 0 ) {
		close(p_to_c1[0]); close(p_to_c1[1]);
		close(c1_to_p[0]); close(c1_to_p[1]);
		close(p_to_c2[1]);
		close(c2_to_p[0]);
		
		int l;
		if ( read(p_to_c2[0], &l, sizeof(int)) < 0 ) { 
			perror("error reading the length");
			exit(1);
		} 

		char* buf = malloc((l + 1) * sizeof(char));
		
		read_from_fd(p_to_c2[0], l, buf);
		//if ( read(p_to_c2[0], buf, l * sizeof(char)) < 0 ) {
		//	perror("error reading the string");
		//	exit(1);	
		//}
		
		char* nb = malloc((l + 1) * sizeof(char));
		memset(nb, 0, (l + 1) * sizeof(char));
		int l2 = 0;
		
		for ( int i = 0; i < l; ++i ) {
			if ( strchr("0123456789", buf[i]) ) {
				nb[l2] = buf[i];
				l2++;
			}
		}
	
		nb[l2] = 0;

		if ( write(c2_to_p[1], &l2, sizeof(int)) < 0 ) {
			perror("error writing the length");
			exit(1);
		}

		if ( write(c2_to_p[1], nb, sizeof(char) * l2) < 0 ) {
			perror("error writing the string");
			exit(1);	
		}

		free(buf);
		free(nb);
		close(c2_to_p[1]);
		close(p_to_c2[0]);
		exit(0);
	}

	//parent
	close(p_to_c1[0]);
	close(p_to_c2[0]);
	close(c1_to_p[1]);
	close(c2_to_p[1]);

	char* input = malloc(256 * sizeof(char));
	if (fgets(input, 256, stdin) == NULL) {
		perror("Error reading the input");
		exit(1);
	}

	int len = strlen(input);

	if ( write(p_to_c1[1], &len, sizeof(int)) < 0 ) {
		perror("error writing the length");
		exit(1);
	}

	 if ( write(p_to_c1[1], input, len * sizeof(char)) < 0 ) {
        perror("error writing the string");
        exit(1);
    }

	 if ( write(p_to_c2[1], &len, sizeof(int)) < 0 ) {
        perror("error writing the length");
        exit(1);
    }

	 if ( write(p_to_c2[1], input, len * sizeof(char)) < 0 ) {
        perror("error writing the string");
        exit(1);
    }

	int l1, l2;
	 
	if ( read(c1_to_p[0], &l1, sizeof(int)) < 0 ) {
        perror("error reading the length");
        exit(1);
    }

	char* buf = malloc((l1 + 1) * sizeof(char));
	memset(buf, 0, (l1 + 1) * sizeof(char));
	read_from_fd(c1_to_p[0], l1, buf);
	//if ( read(c1_to_p[0], buf, l1 * sizeof(char)) < 0 ) {
    //    perror("error reading the length");
    //    exit(1);
    //}

	if ( read(c2_to_p[0], &l2, sizeof(int)) < 0 ) {
        perror("error reading the length");
        exit(1);
    }

	char* buf2 = malloc((l2 + 1) * sizeof(char));
	memset(buf2, 0, (l2 + 1) * sizeof(char));
	read_from_fd(c2_to_p[0], l2, buf2);
	//if ( read(c2_to_p[0], buf2, l2 * sizeof(char)) < 0 ) {
    //    perror("error reading the length");
    //    exit(1);
    //}
	
	//buf[l1] = 0;
	//buf[l2] = 0;

	printf("string only made from vowels: %s\n", buf);
	printf("string only made from digits: %s\n", buf2);

	close(c1_to_p[0]);
	close(c2_to_p[0]);
	close(p_to_c1[1]);
	close(p_to_c2[1]);

	free(input);
	free(buf);
	free(buf2);

	wait(0);
	wait(0);

	return 0;

}
