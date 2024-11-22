#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "mem.h"

int strlen(char s[]) {
    int i = 0;
    while (s[i] != '\0') ++i;
    return i;
}

void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void append(char s[], char n) {
    int len = strlen(s);
    s[len] = n;
    s[len+1] = '\0';
}

void int_to_string(int n, char str[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    reverse(str);
}

void append_str(char s[], char n[]) {
    int len = strlen(s);
    int i = 0;
    while (n[i] != '\0') {
        s[len + i] = n[i];
        i++;
    }
    s[len + i] = '\0';
}

int strcmp(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}

int strncmp(char s1[], char s2[], int n) {
    int i;
    for (i = 0; i < n && s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return (i == n) ? 0 : s1[i] - s2[i];
}

char *strchr(const char *str, int c) {
    while (*str != '\0') {
        if (*str == (char)c) {
            return (char *)str;
        }
        str++;
    }

    if (c == '\0') {
        return (char *)str;
    }

    return NULL;
}

// strdup: Duplicate a string and return a pointer to the new string.
char *strdup(char *s) {
    size_t len = strlen(s);

    char *copy = (char *)malloc(len + 1);

    if (copy == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < len; i++) {
        copy[i] = s[i];
    }

    copy[len] = '\0';

    return copy;
}
