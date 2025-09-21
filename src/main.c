#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/mystrfunctions.h"
#include "../include/myfilefunctions.h"

int main(void) {
    printf("--- Testing String Functions ---\n");

    const char* s = "Hello, World!";
    int len = mystrlen(s);
    printf("mystrlen(\"%s\") = %d\n", s, len);

    char dest[128];
    int copied = mystrcpy(dest, s);
    printf("mystrcpy -> dest: \"%s\" (copied %d chars)\n", dest, copied);

    char dest2[128];
    int n = 5;
    int copied2 = mystrncpy(dest2, s, n);
    printf("mystrncpy (n=%d) -> dest2: \"%s\" (copied %d chars)\n", n, dest2, copied2);

    char catdest[256] = "Start: ";
    int newlen = mystrcat(catdest, s);
    printf("mystrcat -> \"%s\" (new length %d)\n", catdest, newlen);

    printf("\n--- Testing File Functions ---\n");

    const char* fname = "testfile.txt";
    FILE* wf = fopen(fname, "w");
    if (!wf) {
        perror("fopen (write)");
        return 1;
    }

    fprintf(wf, "Hello world\n");
    fprintf(wf, "This is a test file.\n");
    fprintf(wf, "Another line with test.\n");
    fprintf(wf, "Last line\n");
    fclose(wf);

    FILE* rf = fopen(fname, "r");
    if (!rf) {
        perror("fopen (read)");
        return 1;
    }

    int lines = 0, words = 0, chars = 0;
    if (wordCount(rf, &lines, &words, &chars) == 0) {
        printf("wordCount -> lines=%d, words=%d, chars=%d\n", lines, words, chars);
    } else {
        printf("wordCount failed\n");
    }

    char** matches = NULL;
    int mcount = mygrep(rf, "test", &matches);
    if (mcount < 0) {
        printf("mygrep failed\n");
    } else if (mcount == 0) {
        printf("mygrep: no matches found for \"test\"\n");
    } else {
        printf("mygrep found %d matches:\n", mcount);
        for (int i = 0; i < mcount; ++i) {
            printf("  %d: %s\n", i + 1, matches[i]);
            free(matches[i]);
        }
        free(matches);
    }

    fclose(rf);
    /* cleanup example file */
    remove(fname);

    printf("\nAll tests finished.\n");
    return 0;
}
