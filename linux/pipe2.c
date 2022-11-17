#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <malloc.h>

enum { READ = 0, WRITE = 1 };

unsigned long file_size(FILE *file);
void file_stream_copy(int strdesc, FILE *file, unsigned long file_size);
void stream_file_copy(int strdesc, FILE *file, unsigned long file_size);

int main(int argc, char *argv[])  {
    if (argc != 3) {
        printf("too few arguments, abort.\n");
    }

    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        printf("'%s': no such file in directory, abort.\n", argv[1]);
        fclose(input_file);
        return 0;
    }
    FILE *output_file = fopen(argv[2], "w");
    unsigned long fsize = file_size(input_file);

    int status;
    int pipdes[2];
    pipe(pipdes);
    pid_t cpid = fork();

    if (cpid == (pid_t)0) {
        /** child process */
        file_stream_copy(pipdes[WRITE], input_file, fsize);
        fclose(input_file);
    } else {
        /** parent process */
        waitpid(cpid, &status, 0);
        stream_file_copy(pipdes[READ], output_file, fsize);
        fclose(output_file);
    }

    return 0;
}

void file_stream_copy(int strdesc, FILE *file, unsigned long file_size) {
    char *buf = (char *)malloc(file_size * sizeof(char));
    fread(buf, sizeof(char), file_size, file);
    write(strdesc, buf, file_size);
    free(buf);
    close(strdesc);
}

void stream_file_copy(int strdesc, FILE *file, unsigned long file_size) {
    char *buf = malloc(file_size * sizeof(char));
    read(strdesc, buf, file_size);
    fwrite(buf, sizeof(char), file_size, file);
    free(buf);
    close(strdesc);
}

unsigned long file_size(FILE *file) {
    fseek(file, 0, SEEK_END);
    unsigned long size = (unsigned long) ftell (file);
    rewind (file);
    return size;
}
