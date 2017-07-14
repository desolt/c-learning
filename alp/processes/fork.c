#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t child_pid = fork();
    if (child_pid != 0) {
        printf("The child's process ID is %d.\n", (int) child_pid);
        printf("The main parent process ID is %d.\n", (int) getppid());
    } else {
        printf("Hello, %d!\n", (int) getppid());
    }

    return EXIT_SUCCESS;
}
