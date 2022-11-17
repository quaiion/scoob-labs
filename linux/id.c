#include <unistd.h>
#include <syscall.h>
#include <string.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <stdbool.h>

bool gr_user_found(char **memb_arr, char *user_name);

int main() {
    unsigned uid = getuid();
    struct passwd *pw = getpwuid(uid);
    unsigned gid = syscall(SYS_getgid);
    struct group *grp = getgrgid(gid);
    printf("uid=%u(%s) gid=%u(%s) groups(with current user)=",
           uid, pw->pw_name, gid, grp->gr_name);

    struct group *grp_curr = getgrent();
    bool is_first = true;

    while (grp_curr) {
        if (gr_user_found(grp_curr->gr_mem, pw->pw_name)) {
            if (!is_first) {
                printf(",");
            }
            is_first = false;
            printf("%u(%s)", grp_curr->gr_gid, grp_curr->gr_name);
        }
        grp_curr = getgrent();
    }
    printf("\n");

    return 0;
}

bool gr_user_found(char **memb_arr, char *user_name) {
    for (int i = 0; memb_arr[i] != NULL; ++i) {
        if (strcmp(user_name, memb_arr[i]) == 0) {
            return true;
        }
    }
    return false;
}
