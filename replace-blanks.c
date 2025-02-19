#include <stdio.h>

int main(void)
{
    int c;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            putchar(c); /* print first space */
            while ((c = getchar()) == ' ')
                ; /* skip additional spaces */
            if (c != EOF)
 				putchar(c);
        } else {
        	putchar(c);
		}
	}
	return 0;
}
