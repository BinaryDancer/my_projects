#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
int main(int argc, char **argv) {
    enum 
    {
        MAX_NAME = 15,
        RIGHTS = 0700
    };
    if (argc == 1) {
        return 1;
    }
    const char py_init[] = "#! /usr/bin/env python3\nimport os\nprint(";
    const char mult = '*';
    const char end[] = "1)\n";
    const char del[] = "os.remove(";
    const char backtick = '"';
    const char close_bracket = ')';
    const char *tmpdir;
    if ((tmpdir = getenv("XDG_RUNTIME_DIR")) == NULL) {
        if ((tmpdir = getenv("TMPDIR")) == NULL) {
            tmpdir = "/tmp/";
        }
    }
    char path[PATH_MAX];
    pid_t id = getpid();
    char template[MAX_NAME];
    sprintf(template, "scr%d", id);
    size_t path_len = 0;
    path_len = snprintf(path, PATH_MAX, "%s%s", tmpdir, template);
    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, RIGHTS);
    if (fd < 0) {
        return 1;
    }
    if (write(fd, py_init, sizeof(py_init) -1) != sizeof(py_init) - 1) {
        return 1;
    }
    for (int i = 1; i < argc; ++i) {
        int len = strlen(argv[i]);
        if (write(fd, argv[i], sizeof(argv[i][0]) * len) != sizeof(argv[i][0]) * len) {
            return 1;
        }
        if (write(fd, &mult, sizeof(mult)) != sizeof(mult)) {
            return 1;
        }
    }
    if (write(fd, end, sizeof(end) - 1) != sizeof(end) - 1) {
        return 1;
    }
    // выводим команду удалиния файла
    if (write(fd, del, sizeof(del) - 1) != sizeof(del) - 1) {
        return 1;
    }
    if (write(fd, &backtick, sizeof(backtick)) != sizeof(backtick)) {
        return 1;
    }
    if (write(fd, path, sizeof(*path) * path_len) != sizeof(*path) * path_len) {
        return 1;
    }
    if (write(fd, &backtick, sizeof(backtick)) != sizeof(backtick)) {
        return 1;
    }
    if (write(fd, &close_bracket, sizeof(close_bracket)) != sizeof(close_bracket)) {
        return 1;
    }
    close(fd);
    execl(path, template, NULL);
    _exit(1);
}
