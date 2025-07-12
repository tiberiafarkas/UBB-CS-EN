//se citesc 10 numere intr-un vector static de intregi
//sa se afiseze minimul si media lor
#include <stdio.h>
#include <malloc.h>

int main(int argc, char **argv) {
	int *vector = malloc(10 * sizeof(int));
	for ( int i = 0; i < 10; ++i ) {
		scanf("%d", &vector[i]);
	}
	int mini = -1;
	float med, sum = 0;

	for ( int i = 0; i < 10; ++i ) {
		sum += vector[i];
		if ( mini == -1 ) 
			mini = vector[i];
		else if ( vector[i] < mini ) 
			mini = vector[i];
	}
	med = sum / 10;
	printf("mini %d\n", mini);
	printf("average %f\n", med);
	
	free(vector);
	return 0;
}

