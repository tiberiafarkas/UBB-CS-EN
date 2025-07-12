#include <stdio.h>

int main() {
	FILE *fd = popen("wc -l", "w");
	fprintf(fd, "Hello\nword\n");
	return 0;
}
