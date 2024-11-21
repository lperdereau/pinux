#include <stdint.h>

int string_length(char s[]) {
    int i = 0;
    while (s[i] != '\0') ++i;
    return i;
}

void append(char s[], char n) {
    int len = string_length(s);
    s[len] = n;
    s[len+1] = '\0';
}

void append_str(char s[], char n[]) {
    int len = string_length(s);
    int i = 0;
    while (n[i] != '\0') {
        s[len + i] = n[i];
        i++;
    }
    s[len + i] = '\0';
}
