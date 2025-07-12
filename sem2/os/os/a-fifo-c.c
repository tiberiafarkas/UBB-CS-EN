#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>



//pe asta il folosesti cand faci 2 fifouri "a2b" si "b2a", ma rog, in mnt nu te lasa sa faci fifouri so find out why and where you can do it
//mkfifo a2b
//mkfifo b2a

int main() {
	int a2b, b2a, n = 20;
	
	mkfifo("a2b", 0600);
	mkfifo("b2a", 0600);

	a2b = open("a2b", O_WRONLY);
	b2a = open("b2a", O_RDONLY);

	write(a2b, &n, sizeof(int));
	while(1) {
		if ( read(b2a, &n, sizeof(int)) <= 0 ) {
			break;
		}
		if ( n <= 0 )
			break;
		printf("A %d -> %d\n", n, n-1);
		n--;
		write(a2b, &n, sizeof(int));
	}
	close(a2b);
	close(b2a);

	unlink("a2b");
	unlink("b2a");

	return 0;
}
