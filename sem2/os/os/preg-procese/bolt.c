/*
Scrieti un program C care implementeaza un joc de boltz. Se creeaza exact N procese (numerotate de la 1 la N, unde N este dat) incrementeaza pe rand un numar, pornind de la 1, si il trimit unui proces "vecin". Procesul 1 porneste jocul incrementand numarul si trimitandu-l procesului 2, care il incrementeaza si il trimite procesului 3, si asa mai departe. Procesul N va trimite numarul procesului 1, si ciclul se repeta. Fiecare proces va afisa numarul inainte sa il trilita, cu exceptia cazului in care numarul contine cifra 7 sau este multiplu de 7, caz in care procesul va afisa cuvantul "boltz". Ca procesele sa isi incheie executia, implementati ca un proces sa nu afiseze "boltz" intr-o situatie in care ar trebui sa afiseze "boltz", cu o probabilitate de 1/3. In acest caz, toate procesele se vor opri.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

unsigned int n;

int cond7(unsigned int n) {
	if(n % 7 == 0) return 1;
	while(n) {
		if(n % 10 == 7) return 1;
		n /= 10;
	}
	return 0;
}

int cond30() {
	srand((getpid() ^ time(NULL)));
	
	return rand() % 100 + 1 <= 30;
}

void f(int** pipe, unsigned int i) {
	if(i > n - 1) return;

	if(fork() == 0) {
		f(pipe, i + 1);
		return;
	}


	// Not a child
	
	// pipes[0] = "p2a"
	// [1] = "a2b"
	// [2] = "b2c"
	// [n - 1] = "n - 1 to p"

	// we write to "i to i + 1" (pipe[i][1])
	// we read from "i - 1 to i" (pipe[i - 1][0])
	int readFrom = i;
	int writeTo = i == n - 1 ? 0 : i + 1;

	printf("%d: from: %d, to %d\n", i, readFrom, writeTo);

	close(pipe[writeTo][0]);
	close(pipe[readFrom][1]);
	
	for(int j = 0; j < (int)n; j++) { //fuck u stupid psycho
// opsies?
		if(j == readFrom || j == writeTo) continue;
		close(pipe[j][0]); close(pipe[j][1]);
	}

	while(1) {
		int recieved;
		if(read(pipe[readFrom][0], &recieved, sizeof(int)) < 0) break;
		
		if(recieved == -1) {
			// propagam din nou
			printf("P(%d): Recieved exit signal. Closing\n", i);
			write(pipe[writeTo][1], &recieved, 4);
			break;
		}

		// if conditie etc
		if(cond7(recieved)) {
			// Daca nu ar trebui a crie
			// propagam la retul
			if(cond30()) {
				printf("P(%d): something bad happened! exiting...\n", i);
				int val = -1;
				write(pipe[writeTo][1], &val, 4);
				break;
			}
			
			printf("boltz!\n");
		} else {

			printf("P(%d) [%d]: %d -> %d\n", i, getppid(), recieved, recieved + 1);
		} 
		recieved++;
		if(write(pipe[writeTo][1], &recieved, 4) < 0) break;

	}
	
	wait(NULL);
	close(pipe[writeTo][1]);
	close(pipe[readFrom][0]);
}

int main(int argc, char* argv[]) {
	if(argc != 2) {
		printf("Program takes exactly 1 argument.\n");
		exit(1);
	}

	n = (unsigned int)atoi(argv[1]);
	
	int** pipes = malloc(n * sizeof(int*));
	for(int i = 0; i < (int)n; i++) {
		pipes[i] = malloc( 2 * sizeof(int));
		pipe(pipes[i]);
	}

	int val = 1;
	write(pipes[0][1], &val, 4);
	f(pipes, 0);

	for(int i = 0; i < (int)n; ++i) free(pipes[i]);
	free(pipes);	

	return 0;
}
