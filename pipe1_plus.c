#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

enum { READ = 0, WRITE = 1 };

void std_to_stream(int desc);
void stream_sum(int desc);

int main() {
    int status;
    int pipdes[2];
    pipe(pipdes);
    pid_t cpid = fork();

    if (cpid == (pid_t)0) {
        /** child process */
        std_to_stream(pipdes[WRITE]);
        close(pipdes[WRITE]);
    } else {
        /** parent process */
        waitpid(cpid, &status, 0);
        stream_sum(pipdes[READ]);
        close(pipdes[READ]);
    }

    return 0;
}

void std_to_stream(int desc) {
    FILE *stream = fdopen(desc, "w");
    int nval = 0, val = 0;
    scanf("%d", &nval);
    fprintf(stream, "%d ", nval);
    for (int i = 0; i < nval; ++i) {
        scanf("%d", &val);
        fprintf(stream, "%d ", val);
    }
    fclose(stream);
}


void stream_sum(int desc) {
    FILE *stream = fdopen(desc, "r");
    int nval = 0, val = 0, sum = 0;
    fscanf(stream, "%d", &nval);
    for (int i = 0; i < nval; ++i) {
        fscanf(stream, "%d", &val);
        sum += val;
    }
    printf("%d\n", sum);
    fclose(stream);
}
