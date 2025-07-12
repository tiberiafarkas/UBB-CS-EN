#include <stdio.h>
#include <unistd.h>

int main() {
	for (int i = 0; i < 4; ++i ) {
		printf("i=%d, Process %d\n", i, getpid());
		if ( fork() && i % 2 == 1 ) {
			printf("Process %d break\n", getpid());
			break;
		}
	}
	return 0;
}
