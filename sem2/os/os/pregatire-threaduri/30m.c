
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


pthread_barrier_t* barriers;
pthread_barrier_t mainBarrier;

int winningTeam = -1;
pthread_mutex_t mainMutex;

typedef struct  {
	pthread_barrier_t *beforeBarrier, *afterBarrier;
	int threadNumber;
} variablePassTriple;

void* thread(void* passed) {

	pthread_barrier_wait(&mainBarrier);

	variablePassTriple *p = passed;
	int teamNumber = p->threadNumber / 4;
	int numberInTeam = p->threadNumber % 4;


	if(numberInTeam != 0) {
		pthread_barrier_wait(p->beforeBarrier);
	}

	printf("Member %d of team %d started.\n", numberInTeam, teamNumber);
	// Choose a random time to sleep
	int sleepTime = rand() % 100 + 100;
	usleep(sleepTime * 1000);

	if(numberInTeam == 3) {
		int succeed = pthread_mutex_trylock(&mainMutex);
		if(succeed == 0) {
			winningTeam = teamNumber;
			printf("team: %d: ========== F I N I S H ===========\n", teamNumber);
		}
		// free the resource
		free(passed);
		return NULL;
	}

	// else enter the next barrier
	pthread_barrier_wait(p->afterBarrier);


	free(passed);
	return NULL;
}


int n;
int main(int argc, char** argv) {
	if(argc != 2) {
		printf("The program takes one argument.\n");
		exit(1);
	}
	srand(time(NULL));

	n = atoi(argv[1]);

	pthread_barrier_init(&mainBarrier, 0, 4 * n);
	barriers = malloc(4 * n * sizeof(*barriers));
	for(int i = 0; i < 4 * n; i++) pthread_barrier_init(barriers + i, 0, 2);

	pthread_mutex_init(&mainMutex, 0);

	pthread_t *t = malloc(4 * n * sizeof(*t));

	for(int i = 0; i < 4 * n; i++) {
		variablePassTriple *res = malloc(sizeof(*res));
		res->threadNumber = i;
		res->beforeBarrier = (i % 4 == 0 ? NULL : &barriers[i - 1]);
		res->afterBarrier = (i % 4 == 3 ? NULL : &barriers[i]);

		int succeed = pthread_create(t + i, 0, thread, res);
		if(succeed != 0) {
			perror("Couldn't create thread!");
		}
	}

	for(int i = 0; i < 4 * n; i++) {
		pthread_join(t[i], NULL);
	}

	// print the winning team
	printf("Winning team: %d\n", winningTeam);

	for(int i = 0; i < 4 * n; i++) pthread_barrier_destroy(&barriers[i]);

	free(barriers);
	free(t);
	pthread_mutex_destroy(&mainMutex);
	pthread_barrier_destroy(&mainBarrier);

	return 0;
}

