#include <stdio.h>
#include "shm.h"

int main() {
	int shmid;
	struct absp *x;

	shmid = shmget(987, 0, 0);
	if ( shmid < 0 ) {
		perror("nu s-a putut conecta la  memoria partajata");
		return 1;
	}

	x = shmat(shmid, 0, 0);

	while(1) {
		x->s = x->a + x->b;
		x->p = x->a * x->b;

		printf("%d %d %d %d\n", x->a, x->b, x->s, x->p);

		if ( x->s == x->p ) 
			break;
	}

	shmdt(x);

	return 0;
}
