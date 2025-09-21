#include "../include/mystrfunctions.h"
#include <stddef.h>

/*
 * Simple implementations of basic string routines.
 * Return values:
 *  - mystrlen: returns length (>=0), or -1 on NULL input
 *  - mystrcpy: returns number of characters copied (excluding '\0'), or -1 on NULL input
 *  - mystrncpy: returns number of characters copied (<= n), or -1 on NULL input or n<0
 *  - mystrcat: returns new length of dest (>=0), or -1 on error
 *
 * Note: These functions do not check destination buffer sizes. In real code,
 * make sure dest has enough space to hold the result (including trailing '\0').
 */

int mystrlen(const char* s) {
    if (s == NULL) return -1;
    int len = 0;
    while (s[len] != '\0') ++len;
    return len;
}

int mystrcpy(char* dest, const char* src) {
    if (dest == NULL || src == NULL) return -1;
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        ++i;
    }
    dest[i] = '\0';
    return i;
}

int mystrncpy(char* dest, const char* src, int n) {
    if (dest == NULL || src == NULL || n < 0) return -1;
    int i = 0;
    for (; i < n && src[i] != '\0'; ++i) {
        dest[i] = src[i];
    }
    /* Ensure null-terminated to be safe (caller must still ensure enough space) */
    dest[i] = '\0';
    return i;
}

int mystrcat(char* dest, const char* src) {
    if (dest == NULL || src == NULL) return -1;
    int dlen = mystrlen(dest);
    if (dlen < 0) return -1;
    int i = 0;
    while (src[i] != '\0') {
        dest[dlen + i] = src[i];
        ++i;
    }
    dest[dlen + i] = '\0';
    return dlen + i;
}
