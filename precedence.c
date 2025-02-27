#include <stdio.h>
#include <string.h>

#define MAXLENGTH 1000

int main(void)
{
    int c, i, lim;
    char s[MAXLENGTH] = "hello";

    lim = strlen(s);
    for (i = 0, c = getchar();
         i < lim-1, (c != '\n'), c != EOF;
         ++i, c = getchar())
    {
        s[i] = c;
    }
    s[i] = '\0';
}
