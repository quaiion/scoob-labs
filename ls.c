#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

#define FUCKUP -1
#define QUIERES 0

#define MAX_PATH 4096

int list_dir(char *dirpath, bool flag_a, bool flag_l, bool flar_R,
             bool first_dir);
void print_stat(char *dirpath, const char *name, bool first_line);

int main(int argc, char **argv) {
    const struct option long_option[] = {
        {"all", no_argument, NULL, 'a'},
        {"long", no_argument, NULL, 'l'}, 
        {"recursive", no_argument, NULL, 'R'},
        {NULL, no_argument, NULL, 0}
    };

    int long_index = 0, opt = 0;
    const char short_option[] = "alR";
    bool flag_a = false, flag_l = false, flag_R = false;

    while ((opt = getopt_long(argc, argv, short_option,
                              long_option, &long_index)) != -1) {
        switch (opt) {
            case 'a':
                flag_a = true;
                break;
            case 'l':
                flag_l = true;
                break;
            case 'R':
                flag_R = true;
                break;
            default:
                /* system prints the 'switch unknown' message on its own */
                return 0;
        }
    }

    if (optind < argc - 1) {
        printf("too many arguments, abort.\n");
        return 0;
    }
    
    char *path = (char *)malloc(MAX_PATH * sizeof(char));
    if (optind == argc) {
        strcpy(path, ".");
    } else {
        strcpy(path, argv[optind]);
    }

    list_dir(path, flag_a, flag_l, flag_R, true);

    free(path);
    return 0;
}

int list_dir(char *dirpath, bool flag_a, bool flag_l, bool flag_R,
             bool first_dir) {
    if (!first_dir) {
        printf("\n");
    }

    if (flag_R) {
        printf("%s:\n", dirpath);
    }

    DIR *dir = opendir(dirpath);
    if (dir == NULL) {
        printf("bad directory name, abort.\n");
        return FUCKUP;
    }
    bool empty = true, first_line = true;
    for (struct dirent *entry = readdir(dir); entry != NULL;
                                entry = readdir(dir)) {
        if (flag_a || *entry->d_name != '.') {
            empty = false;
            if (flag_l) {
                print_stat(dirpath, entry->d_name, first_line);
                first_line = false;
            } else {
                printf("%s  ", entry->d_name);
            }
        }
    }

    if (flag_R) {
        if (!empty) {
            printf("\n");
        }
        rewinddir(dir);
        for (struct dirent *entry = readdir(dir); entry != NULL;
                                    entry = readdir(dir)) {
            struct stat filestat = {};
            const char *name = entry->d_name;
            unsigned len = strlen(dirpath);
            sprintf(dirpath + len, "/%s", name);
            stat(dirpath, &filestat);

            if (S_ISDIR(filestat.st_mode) && strcmp(name, ".") != 0 &&
                                strcmp(name, "..") != 0 &&
                                (*name != '.' || flag_a)) {
                if (list_dir(dirpath, flag_a, flag_l, true, false) == FUCKUP) {
                    closedir(dir);
                    return FUCKUP;
                }
            }

            dirpath[len] = '\0';
        }
    } else {
        printf("\n");
    }

    closedir(dir);
    return QUIERES;
}

void print_stat(char *dirpath, const char *name, bool first_line) {
    struct stat filestat = {};
    unsigned len = strlen(dirpath);
    sprintf(dirpath + len, "/%s", name);
    stat(dirpath, &filestat);
    dirpath[len] = '\0';

    if (!first_line) {
        printf("\n");
    } else {
        printf("total %ld\n", filestat.st_blocks);
    }
    char *time = ctime(&filestat.st_mtime);
    time[strlen(time) - 9] = '\0';
    time += 4;
    printf("%c%c%c%c%c%c%c%c%c%c %lu %s %s %lu %s %s",
                                    S_ISDIR(filestat.st_mode) ? 'd' : '-',
                                    S_IRUSR & filestat.st_mode ? 'r' : '-',
                                    S_IWUSR & filestat.st_mode ? 'w' : '-',
                                    S_IXUSR & filestat.st_mode ? 'x' : '-',
                                    S_IRGRP & filestat.st_mode ? 'r' : '-',
                                    S_IWGRP & filestat.st_mode ? 'w' : '-',
                                    S_IXGRP & filestat.st_mode ? 'x' : '-',
                                    S_IROTH & filestat.st_mode ? 'r' : '-',
                                    S_IWOTH & filestat.st_mode ? 'w' : '-',
                                    S_IXOTH & filestat.st_mode ? 'x' : '-',
                                    filestat.st_nlink,
                                    getpwuid(filestat.st_uid)->pw_name,
                                    getgrgid(filestat.st_gid)->gr_name,
                                    filestat.st_size,
                                    time, name);
}
