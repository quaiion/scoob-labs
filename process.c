#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t ch = fork();
    if (ch == 0) {
        sleep(15);
        printf("child process from child: %d\ninitial process from child: %d\n", getpid(), getppid());
    } else {
        int wstat;
        wait(&wstat);
        printf("initial process from initial: %d\ninitial's parent process: %d\nchild process from initial: %d\n", getpid(), getppid(), ch);
    }
    return 0;
}
