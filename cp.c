#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>
#include <malloc.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <utime.h>
#include <unistd.h>

extern int errno;

#define BAD -1
#define GOOD 0

#define MAX_PATH 4096

const char help_string [] = "Usage: cp [OPTION]... SOURCE DEST\nCopy SOURCE file to DEST file\n\n\
Mandatory arguments to long options are mandatory for short options too.\n\
\t-f, --force                   if an existing destination file cannot be\n\
\t\t\t\t\topened, remove it and try again\n\
\t-i, --interactive             prompt before overwrite\n\
\t-p  --preserve                preserve the file's metadata, if possible\n\
\t-v, --verbose                 explain what is being done\n\
\t-h, --help                    display this help and exit\n";

unsigned long file_size(FILE* file);
int copy_file(FILE *src, FILE *dest);
int copy_metadata(const char *src_name, const char *dest_name);

int main(int argc, char **argv) {
    const struct option long_option[] = {
        {"help", no_argument, NULL, 'h'},
        {"verbose", no_argument, NULL, 'v'}, 
        {"interactive", no_argument, NULL, 'i'},
        {"force", no_argument, NULL, 'f'},
        {"preserve", no_argument, NULL, 'p'},
        {NULL, no_argument, NULL, 0}
    };

    int long_index = 0, opt = 0;
    const char short_option[] = "hvifp";
    bool flag_h = false, flag_v = false, flag_i = false, flag_f = false, flag_p = false;

    while ((opt = getopt_long(argc, argv, short_option,
                              long_option, &long_index)) != -1) {
        switch (opt) {
            case 'h':
                flag_h = true;
                break;
            case 'v':
                flag_v = true;
                break;
            case 'i':
                flag_i = true;
                break;
            case 'f':
                flag_f = true;
                break;
            case 'p':
                flag_p = true;
                break;
            default:
                /* system prints the 'switch unknown' message on its own */
                return 0;
        }
    }

    if (flag_h) {
        printf(help_string);
        return 0;
    }

    if (optind < argc - 2) {
        printf("too many arguments, abort.\n");
        return 0;
    } else if (optind > argc - 2) {
        printf("not enough arguments, abort.\n");
    }
    const char *src_name = argv[optind], *dest_name = argv[optind + 1];

    FILE *src = fopen(src_name, "r");
    if (src == NULL) {
        printf("failed to open '%s', abort.\n", src_name);
        return 0;
    }
    if (flag_i) {
        FILE *dest_read = fopen(dest_name, "r");
        if (dest_read != NULL || (errno != ENOENT && errno != EISDIR)) {
            printf("overwrite '%s'? ", dest_name);
            char answer[4] = {};
            scanf("%3s", answer);
            if (strcmp(answer, "yes") != 0 && answer[0] != 'y') {
                fclose(dest_read);
                fclose(src);
                return 0;
            }
        }
        if (dest_read != NULL) {
            fclose(dest_read);
        }
    }
    FILE *dest = fopen(dest_name, "w");
    if (dest == NULL) {
        if (errno = EACCES) {
            if (flag_f) {
                remove(dest_name);
                dest = fopen(dest_name, "w");
            } else {
                printf("no write permission for dest file, abort.\n");
                fclose(src);
                return 0;
            }
        } else {
            printf("failed to open '%s', abort.\n", dest_name);
            fclose(src);
            return 0;
        }
    }

    int cf_res = copy_file(src, dest);
    fclose(src);
    fclose(dest);

    int cm_res = GOOD;
    if (flag_p && cf_res == GOOD) {
        cm_res = copy_metadata(src_name, dest_name);
    }

    if (flag_v && cf_res == GOOD) {
        if (cm_res == GOOD) {
            printf("'%s' -> '%s'\n", src_name, dest_name);
        } else {
            printf("'%s' -> '%s' (no metadata)\n", src_name, dest_name);
        }
    }

    return 0;
}

unsigned long file_size(FILE *file) {
    fseek(file, 0, SEEK_END);
    unsigned long size = (unsigned long) ftell (file);
    rewind (file);
    return size;
}

int copy_file(FILE *src, FILE *dest) {
    unsigned long src_size = file_size(src);
    char *buf = malloc(src_size * sizeof(char));

    unsigned long read = fread(buf, sizeof(char), src_size, src);
    if (read != src_size) {
        printf("an error occured while trying to read the source file, abort.\n");
        free(buf);
        return BAD;
    }

    unsigned long wrote = fwrite(buf, sizeof(char), src_size, dest);
    if (wrote != src_size) {
        printf("an error occured while trying to write to the dest file, abort.\n");
        free(buf);
        return BAD;
    }

    free(buf);
    return GOOD;
}

int copy_metadata(const char *src_name, const char *dest_name) {
    struct stat filestat = {};
    if (stat(src_name, &filestat) != 0) {
        printf("failed to read metadata from the source file, abort.\n");
        return BAD;
    }

    struct utimbuf time;
    time.actime = filestat.st_atime;
    time.modtime = filestat.st_mtime;
    if (utime(dest_name, &time) != 0 ||
                        chmod(dest_name, filestat.st_mode) != 0 ||
                        chown(dest_name, filestat.st_uid, filestat.st_gid) != 0) {
        printf("failed to write metadata to the dest file, abort.\n");
        return BAD;
    }

    return GOOD;
}
