//
//  main.c
//  up06-4-read-dir
//
//  Created by Мамаев Павел on 21/10/2018.
//  Copyright © 2018 Мамаев Павел. All rights reserved.
//

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
int main(int argc, char **argv) {
    DIR *d;
    struct stat info;
    char new_path[PATH_MAX + 1];
    unsigned long len = strlen(argv[1]);
    if (argv[1][len - 1] == '/'){
        argv[1][len - 1] = '\0';
    }
    long long size_all = 0;
    struct dirent *dd;
    uid_t id = getuid();
    if ((d = opendir(argv[1])) != NULL) {
        while ((dd = readdir(d))) {
            if (dd->d_name[0] >= 'A' && dd->d_name[0] <= 'Z'){
                snprintf(new_path, PATH_MAX, "%s/%s", argv[1], dd->d_name);
                if (stat(new_path, &info) == 0) {
                    if (S_ISREG(info.st_mode) && info.st_uid == id) {
                        size_all += info.st_size;
                    }
                }
            }
        }
    }
    closedir(d);
    printf("%lld", size_all);
    return 0;
}
