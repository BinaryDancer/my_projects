#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int year, day;
    sscanf(argv[1], "%d", &year);
    sscanf(argv[2], "%d", &day);
    struct tm *timeinfo = calloc(1, sizeof(*timeinfo));
    timeinfo->tm_min = 10;
    timeinfo->tm_mday = day;
    timeinfo->tm_year = year - 1900;
    mktime(timeinfo);
    printf("%d %d %d %d\n", year, timeinfo->tm_mon + 1, timeinfo->tm_mday + 1, timeinfo->tm_wday + 1);
    return 0;
}