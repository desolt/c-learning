#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
    pid_t ls_pid = fork();
    if (ls_pid != 0) {
        return EXIT_SUCCESS;
    } else {
        char *args[] = {
            "ls",
            "--color=auto",
            NULL
        };

        execvp("ls", args);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
