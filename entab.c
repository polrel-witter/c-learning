#include <stdio.h>

#define tab 4

int main()
{
    int c, i, j, spaces;
    char str[1000];

    i = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            str[i] = '\0';
            printf("%s\n", str);
            i = 0;
        } else if (c == '\t') {
            spaces = tab - (i % tab); // modulo to tell us the next tab position
            for (j = 0; j < spaces; ++j) {
                str[i] = ' ';
                ++i;
            }
        } else {
            str[i] = c;
            ++i;
        }
    }
}
