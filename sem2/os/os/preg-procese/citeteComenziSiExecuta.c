#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {

	char tmp[255] = {0};
	
	while(fgets(tmp, 255, stdin)[0] != '0') {
		char* v[] = {"bash", "-c", tmp, NULL};
		int child = fork();
		if(child == 0) {
			// execlp("bash", "bash", "-c", tmp, NULL);
			execvp("bash", v);
		}
	}


	return 0;
}

