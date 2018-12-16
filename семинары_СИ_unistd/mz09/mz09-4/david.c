#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <limits.h>

enum
{
    MAX_NAME_LEN = 20,
    OPEN_RIGHTS = 0700
};

int main(int argc, char *argv[])
{
    char name[MAX_NAME_LEN];
    snprintf(name, MAX_NAME_LEN, "up-tmp%d.py", getpid());
    char *dir;
    if (!(dir = getenv("XDG_RUNTIME_DIR")) && !(dir = getenv("TMPDIR")))
    {
        dir = "/tmp/";
    }
    char path[PATH_MAX];
    snprintf(path, PATH_MAX, "%s%s", dir, name);
    printf("%s\n", path);
    int fd = open(path, O_RDWR | O_CREAT | O_TRUNC, OPEN_RIGHTS);
    if (fd < 0)
    {
        return 1;
    }
    const char code1[] = "#! /usr/bin/env python\nfrom os import remove\nprint(";
    if (write(fd, &code1, sizeof(code1) - 1) != sizeof(code1) - 1)
    {
        close(fd);
        return 1;
    }
    int arglen = strlen(argv[1]);
    if (write(fd, argv[1], arglen) != arglen)
    {
        close(fd);
        return 1;
    }
    for (int i = 2; i < argc; ++i)
    {
        if (write(fd, "*", 1) != 1)
        {
            close(fd);
            return 1;
        }
        int arglen = strlen(argv[i]);
        if (write(fd, argv[i], arglen) != arglen)
        {
            close(fd);
            return 1;
        }
    }
    char code2[PATH_MAX];
    arglen = snprintf(code2, PATH_MAX, ")\nremove(\"%s\")\n", path);
    if (write(fd, &code2, arglen) != arglen)
    {
        close(fd);
        return 1;
    }
    if (close(fd) < 0)
    {
        return 1;
    }
    execl(path, name, NULL);
    return 100;
}