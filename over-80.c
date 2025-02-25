#include <stdio.h>

int main()
{
    int c, len;
    char over80[1000];

    len = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            if (len > 80) {
                over80[len] = '\0'; // append null
                printf("%s\n", over80);
            }
            /* don't need to reset over80 because printf only prints up to the
             * null terminator */
            len = 0;
        } else {
            // continue adding chars to array
            over80[len] = c;
            ++len;
        }
    }
}
