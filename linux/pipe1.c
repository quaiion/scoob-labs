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
    int val = 0;
    while (scanf("%d", &val) != EOF) {
        fprintf(stream, "%d ", val);
    }
    fclose(stream);
}


void stream_sum(int desc) {
    FILE *stream = fdopen(desc, "r");
    int val = 0, sum = 0;
    while (fscanf(stream, "%d", &val) != EOF) {
        sum += val;
    }
    printf("%d\n", sum);
    fclose(stream);
}

// void stream_to_std(int desc) {
//     FILE *stream = fdopen(desc, "r");
//     int val = 0;
//     while (fscanf(stream, "%d", &val) != EOF) {
//         printf("%d ", val);
//     }
//     // while (1) {
//     //     printf("fscanf started\n");
//     //     int res = fscanf(stream, "%d", &val);
//     //     printf("fscanf ended\n");
//     //     if (res == EOF) break;
//     //     printf("res = %d\n", res);
//     //     printf("val = %d\n", val);
//     // }
//     fclose(stream);
// }
