#include <stdio.h>
#include <string.h>

int main() {
	char s[64];
	int i;
	char *p;

	while (1) {
		p = fgets(s, 64, stdin);
		if ( p == NULL ) {
			break;
		}
		for ( i = 0; i < (int)strlen(s); ++i ) {
			if ( i < (int)strlen(s)-1 ) 
				s[i] = '*';
		}
		fputs(s, stdout);
	}
	return 0;
}

