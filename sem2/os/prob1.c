#include <malloc.h>
#include <string.h>


int main(

    int argc,

    char **argv

    )

{
	

    char **c;



    c = malloc(3 * sizeof(char**));

    for ( int i = 0; i < 3; ++i ) 
	    c[i] = malloc(10 * sizeof(char*));

    strcpy(c[0], "hello");

    strcpy(c[1], "world");

    strcpy(c[2], "!");

    for(int i = 0; i < 3; i++) 
	    free(c[i]);

    free(c);

    return 0;

}
