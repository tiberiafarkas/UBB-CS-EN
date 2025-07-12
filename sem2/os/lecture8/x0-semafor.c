#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int turn = 0;
int board[3][3] = {{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}};
sem_t s0, s1;

//simulam un x si 0 in care facem doua threaduri care sa joace alternativ, acum e randul tau, dupa e randul lui

void show() {
	for ( int i = 0; i < 3; ++i ) { 
		for ( int j = 0; j < 3; ++j ) {
			printf("%d ", board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void *ju0(void *a) {
	int i, j, full;
	while (1) {
		sem_wait(&s0);
		if ( turn == 0 ) {
			for ( i = 0; i < 3; ++i ) {
				for ( j = 0; j < 3; ++j ) {
					if ( board[i][j] == -1 ) {
						board[i][j] = 0;
						full = 0;
						show();
						break;
					}
				}
				if ( !full ) 
					break;
			}
			turn = 1;
			if ( full ) {
				sem_post(&s1);
				break;
			}
		}
		sem_post(&s1);
	}

	(void) a;
	return NULL;
}

void *ju1(void *a) {
    int i, j, full;
    while (1) {
		sem_wait(&s1);
        if ( turn == 1 ) {
            for ( i = 0; i < 3; ++i ) {
                for ( j = 0; j < 3; ++j ) {
                    if ( board[i][j] == -1 ) {
                        board[i][j] = 1;
                        full = 0;
                        show();
                        break;
                    }
                }
                if ( !full )
                    break;
			}             

            turn = 0;
            if ( full ) {
				sem_post(&s0);
                break;
			}
        }
		sem_post(&s0);
    }

    (void) a;
    return NULL;
}

int main() {
	pthread_t t0, t1;
	sem_init(&s0, 0, 1);
	sem_init(&s1, 0, 1);
	sem_wait(&s1);
	pthread_create(&t0, NULL, ju0, NULL);
	pthread_create(&t1, NULL, ju1, NULL);
	pthread_join(t0, NULL);
	pthread_join(t1, NULL);
	sem_destroy(&s0);
	sem_destroy(&s1);

	return 0;
}
