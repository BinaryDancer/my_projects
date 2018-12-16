void normalize_path(char *buf){
    char *now = buf;
    while (*now != '\0') {
        if (*now == '/') {
            *buf++ = *now++;
            while (*now == '/'){
            now++;
            }
        } else {
            *buf = *now;
            now++;
            buf++;
        }
        
    }
    *buf = *now;
}