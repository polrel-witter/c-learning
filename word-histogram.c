#include <stdio.h>

int main(void)
{
    int c, count = 0;
    char bar[100] = "";
    int len = 0;

    while ((c = getchar()) != EOF) {
        if (c == ' ' | c == '\t' | c == '\n') {
            if (len > 0) {
                ++count;
                bar[len] = '\0';
                printf("%d: %s\n", count, bar);
            }
            // reset variables
            len = 0;
	        bar[0] = '\0';  // reset string by null terminating at start
        } else {
            bar[len++] = '-';
        }
    }
}
