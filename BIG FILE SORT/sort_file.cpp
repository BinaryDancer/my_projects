#include <cstdio>
#include <iostream>
bool cmp(const char *a, const char *b) {
    const char *c1 = a, *c2 = b;
    while ((*c1 != '\n') && (*c2 != '\n')) {
        if (*c1 < *c2)
            return true;
        else if (*c1 > *c2)
            return false;
        c1++;
        c2++;
    }
    return *c1 == '\n';
}
int main() {
    FILE *files[4];
    
    files[0] = fopen("input.txt", "r");
    files[2] = fopen("help0.txt", "w+");
    files[3] = fopen("help1.txt", "w+");
    int k = 0;
    int now = 0;
    int kk[] = {0, 0, 0, 0};
    char ss[3][10013];
    char *s[] = {ss[0], ss[1], ss[2]};
    int kol = 0;
    while (fgets(s[k], 10004, files[0]) != NULL) {
        ++kol;
        if (k++ == 2) {
            if (cmp(s[0], s[1])){
                fputs(s[0], files[now+2]);
                fputs(s[1], files[now+2]);
                kk[now+2] += 2;
            } else {
                fputs(s[1], files[now+2]);
                fputs(s[0], files[now+2]);
                kk[now+2] += 2;
            }
            char *temp = s[0];
            s[0] = s[2];
            s[2] = temp;
            k = 1;
            now ^= 1;
        }
    }
    if (k == 2)
        if (cmp(s[0], s[1])){
            fputs(s[0], files[now + 2]);
            fputs(s[1], files[now + 2]);
            kk[now+2] += 2;
        } else {
            fputs(s[1], files[now + 2]);
            fputs(s[0], files[now + 2]);
            kk[now+2] += 2;
        }
        else
            if (k == 1) {
                fputs(s[0], files[now + 2]);
                kk[now+2]++;
            }
    fclose(files[0]);
    // first sort
    
    k = 2;
    int shag = 0;
    files[0] = fopen("help2.txt", "w+");
    files[1] = fopen("help3.txt", "w+");
    
    while (k < kol) {
        rewind(files[0]);
        rewind(files[1]);
        rewind(files[2]);
        rewind(files[3]);
        shag ^= 1;
        kk[(shag ^ 1) * 2 + 1] = kk[(shag ^ 1) * 2] = 0;
        ss[1][0] = ss[2][0] = '\0';
        now = 0;
        bool flag_f1 = false, flag_f2 = false;
        int k1 = 0, k2 = 0;
        int bb = 0;
        while (true) {
            if (kk[shag * 2] == 0 && kk[shag * 2 + 1] == 0)
                if (bb++ == 1)
                    break;
            if (k1 < k) {
                if (ss[1][0] == '\0' && !flag_f1) {
                    if (kk[shag * 2] > 0) {
                        fgets(ss[1], 10004, files[shag * 2]);
                        k1++;
                        kk[shag * 2]--;
                    } else {
                        flag_f1 = true;
                        ss[1][0] = '\0';
                    }
                }
            }
            if (k2 < k) {
                if (ss[2][0] == '\0' && !flag_f2) {
                    if (kk[shag * 2 + 1] > 0) {
                        fgets(ss[2], 10004, files[shag * 2 + 1]);
                        k2++;
                        kk[shag * 2 + 1]--;
                    } else {
                        flag_f2 = true;
                        ss[2][0] = '\0';
                    }
                }
            }
            if ((ss[1][0]) || (ss[2][0])) {
                if (ss[1][0] == '\0') {
                    fputs(ss[2], files[(shag ^ 1) * 2 + now]);
                    kk[(shag ^ 1) * 2 + now]++;
                    ss[2][0] = '\0';
                }
                else {
                    if (ss[2][0] == '\0') {
                        fputs(ss[1], files[(shag ^ 1) * 2 + now]);
                        kk[(shag ^ 1) * 2 + now]++;
                        ss[1][0] = '\0';
                    }
                    else {
                        if (cmp(ss[1], ss[2])) {
                            fputs(ss[1], files[(shag ^ 1) * 2 + now]);
                            kk[(shag ^ 1) * 2 + now]++;
                            ss[1][0] = '\0';
                        }
                        else {
                            fputs(ss[2], files[(shag ^ 1) * 2 + now]);
                            kk[(shag ^ 1) * 2 + now]++;
                            ss[2][0] = '\0';
                        }
                    }
                }
            }
            else {
                k1 = k2 = 0;
                now ^= 1;
            }
        }
        k <<= 1;
    }
    // last step
    shag ^= 1;
    rewind(files[shag * 2]);
    rewind(files[shag * 2 + 1]);
    fclose(files[(shag ^ 1) * 2]);
    fclose(files[(shag ^ 1) * 2 + 1]);
    files[(shag ^ 1) * 2] = fopen("output.txt", "w+");
    ss[1][0] = ss[2][0] = '\0';
    now = 0;
    bool flag_f1 = false, flag_f2 = false;
    int k1 = 0, k2 = 0;
    int bb = 0;
    while (true) {
        if (kk[shag * 2] == 0 && kk[shag * 2 + 1] == 0)
            if (bb++ == 1)
                break;
        if (k1 < k) {
            if (ss[1][0] == '\0' && !flag_f1) {
                if (kk[shag * 2] > 0) {
                    fgets(ss[1], 10004, files[shag * 2]);
                    k1++;
                    kk[shag * 2]--;
                } else {
                    flag_f1 = true;
                    ss[1][0] = '\0';
                }
            }
        }
        if (k2 < k) {
            if (ss[2][0] == '\0' && !flag_f2) {
                if (kk[shag * 2 + 1] > 0) {
                    fgets(ss[2], 10004, files[shag * 2 + 1]);
                    k2++;
                    kk[shag * 2 + 1]--;
                } else {
                    flag_f2 = true;
                    ss[2][0] = '\0';
                }
            }
        }
        if ((ss[1][0]) || (ss[2][0])) {
            if (ss[1][0] == '\0') {
                fputs(ss[2], files[(shag ^ 1) * 2 + now]);
                kk[(shag ^ 1) * 2 + now]++;
                ss[2][0] = '\0';
            }
            else {
                if (ss[2][0] == '\0') {
                    fputs(ss[1], files[(shag ^ 1) * 2 + now]);
                    kk[(shag ^ 1) * 2 + now]++;
                    ss[1][0] = '\0';
                }
                else {
                    if (cmp(ss[1], ss[2])) {
                        fputs(ss[1], files[(shag ^ 1) * 2 + now]);
                        kk[(shag ^ 1) * 2 + now]++;
                        ss[1][0] = '\0';
                    }
                    else {
                        fputs(ss[2], files[(shag ^ 1) * 2 + now]);
                        kk[(shag ^ 1) * 2 + now]++;
                        ss[2][0] = '\0';
                    }
                }
            }
        }
        else {
            k1 = k2 = 0;
            now ^= 1;
        }
    }
    if ((ss[1][0]) || (ss[2][0])) {
        if (ss[1][0] == '\0') {
            fputs(ss[2], files[(shag ^ 1) * 2]);
            ss[2][0] = '\0';
        }
        else {
            if (ss[2][0] == '\0') {
                fputs(ss[1], files[(shag ^ 1) * 2]);
                ss[1][0] = '\0';
            }
            else {
                if (cmp(ss[1], ss[2])) {
                    fputs(ss[1], files[(shag ^ 1) * 2]);
                    ss[1][0] = '\0';
                }
                else {
                    fputs(ss[2], files[(shag ^ 1) * 2]);
                    ss[2][0] = '\0';
                }
            }
        }
    }
    fclose(files[(shag ^ 1) * 2]);
    fclose(files[shag * 2 + 1]);
    fclose(files[shag * 2]);
    return 0;
}
