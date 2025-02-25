#include <stdio.h>

/* replaces tabs with proper number of blank spaces */

// start with fixed sized tab
// init string accumulator; where string will be added
// hunt for '\t', adding char to string
// once '\t' is found, replace with corresponding number of spaces
// produce new string as output
// later, modify to accept variable tab size

#define tab 4

int main()
{
    int c, i, j;
    char str[1000];

    i = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            str[i] = '\0';
            printf("%s\n", str);
            i = 0;
        } else if (c == '\t') {
            for (j = 0; j < tab; ++j) {
                str[i] = ' ';
                ++i;
            }
        } else {
            str[i] = c;
            ++i;
        }
    }
}
