#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <malloc.h>
#include <string.h>
#include <sys/stat.h>

enum { READ = 0, WRITE = 1 };
enum { DEFAULT_NAMEBUF_CAP = 256 };

unsigned long file_size(FILE *file);
void dump_file_to_console(const char *filename);
void stream_print_files(int desc);

int main()  {
    int status;
    int pipdes[2];
    pipe(pipdes);
    pid_t cpid = fork();

    if (cpid == (pid_t)0) {
        /** child process */
        int tmp_desc = dup(STDOUT_FILENO);
        dup2(pipdes[WRITE], STDOUT_FILENO);
        if (execl("./ls", "ls", (char *)NULL) == -1) {
            printf("no 'ls' executable found in directory, abort.\n");
        }
        dup2(tmp_desc, STDOUT_FILENO);
        close(pipdes[WRITE]);
    } else {
        /** parent process */
        waitpid(cpid, &status, 0);
        stream_print_files(pipdes[READ]);
        close(pipdes[READ]);
    }

    return 0;
}

void dump_file_to_console(const char *filename) {
    struct stat filestat = {};
    stat(filename, &filestat);
    if (S_ISDIR(filestat.st_mode) ||
                S_IXUSR & filestat.st_mode ||
                S_IXGRP & filestat.st_mode ||
                S_IXOTH & filestat.st_mode ||
                (filename[strlen(filename) - 1] == 'o' &&
                filename[strlen(filename) - 2] == '.')) {
        return;
    }

    FILE *file = fopen(filename, "r");
    unsigned long fsize = file_size(file);
    char *buf = (char *)malloc(fsize * sizeof(char));

    fread(buf, sizeof(char), fsize, file);
    printf("%s:\n\n", filename);
    write(STDOUT_FILENO, buf, fsize);
    printf("\n\n\n");

    free(buf);
    fclose(file);
}

void stream_print_files(int desc) {
    FILE *file = fdopen(desc, "r");
    unsigned namebuf_size = 0, namebuf_cap = DEFAULT_NAMEBUF_CAP;
    char *namebuf = (char *)malloc(DEFAULT_NAMEBUF_CAP * sizeof(char));
    for (char c = fgetc(file); c != '\n'; c = fgetc(file)) {
        if (c == ' ') {
            namebuf[namebuf_size] = '\0';
        } else {
            namebuf[namebuf_size] = c;
        }
        namebuf_size += 1;
        if (namebuf_size > namebuf_cap - 3) {
            namebuf_cap *= 2;
            namebuf = realloc(namebuf, namebuf_cap);
        }
    }

    namebuf[namebuf_size] = namebuf[namebuf_size + 1] = namebuf[namebuf_size + 2] = '\0';

    char *bufptr = namebuf;
    while (*bufptr != '\0') {
        dump_file_to_console(bufptr);
        bufptr = strchr(bufptr, '\0');
        bufptr += 2;
    }

    free(namebuf);
    fclose(file);
}

unsigned long file_size(FILE *file) {
    fseek(file, 0, SEEK_END);
    unsigned long size = (unsigned long) ftell (file);
    rewind (file);
    return size;
}
