//
//  main.c
//  up06-6-directory
//
//  Created by Мамаев Павел on 22/10/2018.
//  Copyright © 2018 Мамаев Павел. All rights reserved.
//

#include <dirent.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>
int compare(const void * x1, const void * x2) {
    return (strcasecmp(*(char**)x1, *(char**)x2));
}
int traverse(const char *dir, const char *name_dir, int len_dir, char *path)
{
    DIR *d = opendir(dir);
    if (d == NULL) {
        return 0;
    }
    if (name_dir != NULL) {
        printf("cd %s\n", name_dir);
    }
    struct dirent *dd;
    int count = 0;
    int all = 1;
    char **v = calloc(all, sizeof(*v));
    if (v == NULL){
        return 1;
    }
    while ((dd = readdir(d))) {
        if (strcmp(dd->d_name, ".") && strcmp(dd->d_name, "..")) {
            int slen = snprintf(&path[len_dir], PATH_MAX - len_dir, "/%s", dd->d_name);
            if (slen + len_dir + 1 <= PATH_MAX) {
                struct stat info;
                if (lstat(path, &info) == 0){
                    if (S_ISDIR(info.st_mode)) {
                        if (count == all) {
                            char **tmp = realloc(v, (all *= 2) * sizeof(*v));
                            if (tmp == NULL) {
                                return 1;
                            }
                            v = tmp;
                        }
                        v[count++] = strdup(dd->d_name);
                    }
                }
            }
        }
    }
    closedir(d);
    if (count > 0) {
        qsort(v, count, sizeof(*v), compare);
    }
    for (size_t i = 0; i < count; ++i) {
        int slen = snprintf(&path[len_dir], PATH_MAX - len_dir, "/%s", v[i]);
        if (traverse(path, v[i], slen + len_dir, path)){
            return 1;
        }
        free(v[i]);
    }
    if (name_dir != NULL) {
        printf("cd ..\n");
    }
    free(v);
    return 0;
}

int main(int argc, char *argv[]) {
    int len = (int) strlen(argv[1]);
    char path[PATH_MAX];
    sprintf(path, "%s", argv[1]);
    return traverse(argv[1], NULL, len, path);
}
