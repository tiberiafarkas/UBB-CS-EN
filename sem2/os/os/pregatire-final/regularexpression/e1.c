#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
	char *a[3] = {"A", "B", "C"};
	for ( int i = 0; i < 3; ++i ) {
		execl("/bin/echo", "/bin/echo", a[i], NULL);
	}
	return 0;
}

/*
execl():

Replaces the current process with a new one.
The process image is replaced by the new program.
After a successful call to execl(), nothing after it is executed — the current process is gone and replaced.

The loop starts with i = 0.

s[0] is "A", so it executes:

execl("/bin/echo", "/bin/echo", "A", NULL);

This replaces the current process with /bin/echo that prints A
Since the process is replaced, the loop does not continue to i = 1 or i = 2.
So, only "A" is printed, and the rest is never executed.

If you want to print all three strings (A, B, C), you must fork before calling execl, like:

for (int i = 0; i < 3; i++) {
    if (fork() == 0) {
        execl("/bin/echo", "/bin/echo", s[i], NULL);
        exit(1); // If execl fails
    }
}

