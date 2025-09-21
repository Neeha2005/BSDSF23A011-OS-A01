#include "../include/myfilefunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 * wordCount:
 *  - Counts lines, words and characters in the provided FILE*.
 *  - Returns 0 on success, -1 on failure (e.g., bad args).
 *  - After the call the file pointer is rewound to the start.
 *
 * Definition used here:
 *  - lines: number of newline characters; if file does not end with newline
 *    but has characters, last line is counted as a line too.
 *  - words: sequences of non-space characters separated by isspace()
 *  - chars: total characters read
 */

int wordCount(FILE* file, int* lines, int* words, int* chars) {
    if (!file || !lines || !words || !chars) return -1;

    rewind(file);

    int c;
    int in_word = 0;
    int l = 0, w = 0, ch = 0;
    int last_char = 0;

    while ((c = fgetc(file)) != EOF) {
        ++ch;
        last_char = c;
        if (c == '\n') ++l;
        if (isspace((unsigned char)c)) {
            if (in_word) {
                ++w;
                in_word = 0;
            }
        } else {
            in_word = 1;
        }
    }

    /* if file ended while inside a word, count it */
    if (in_word) ++w;

    /* if file had characters and last char wasn't a newline, count the last line */
    if (ch > 0 && last_char != '\n') ++l;

    *lines = l;
    *words = w;
    *chars = ch;

    rewind(file);
    return 0;
}

/*
 * mygrep:
 *  - Searches for lines that contain search_str in fp.
 *  - On success returns number of matches (>=0) and sets *matches to an
 *    allocated array of char* (caller must free each string and the array).
 *  - On failure returns -1.
 *
 * Limitations:
 *  - Uses a fixed read buffer (4096). Very long lines may be truncated.
 *  - Matches are exact substring matches (uses strstr).
 */

int mygrep(FILE* fp, const char* search_str, char*** matches) {
    if (!fp || !search_str || !matches) return -1;

    rewind(fp);

    const size_t BUF_SZ = 4096;
    char buffer[BUF_SZ];

    size_t capacity = 8;
    size_t count = 0;
    char** arr = malloc(capacity * sizeof(char*));
    if (!arr) return -1;

    while (fgets(buffer, (int)BUF_SZ, fp) != NULL) {
        if (strstr(buffer, search_str) != NULL) {
            /* strip trailing newline if present */
            size_t len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') buffer[len - 1] = '\0';
            /* allocate and copy */
            char* copy = malloc(strlen(buffer) + 1);
            if (!copy) {
                /* cleanup on failure */
                for (size_t i = 0; i < count; ++i) free(arr[i]);
                free(arr);
                rewind(fp);
                return -1;
            }
            strcpy(copy, buffer);

            if (count >= capacity) {
                capacity *= 2;
                char** tmp = realloc(arr, capacity * sizeof(char*));
                if (!tmp) {
                    free(copy);
                    for (size_t i = 0; i < count; ++i) free(arr[i]);
                    free(arr);
                    rewind(fp);
                    return -1;
                }
                arr = tmp;
            }
            arr[count++] = copy;
        }
    }

    if (count == 0) {
        free(arr);
        *matches = NULL;
        rewind(fp);
        return 0;
    }

    *matches = arr;
    rewind(fp);
    return (int)count;
}

