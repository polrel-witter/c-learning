#include <stdio.h>

int lower(int c);

int main(void)
{
    int i;
    char str[1000];
    printf("Enter string: ");

    if (fgets(str, sizeof(str), stdin) == NULL) {
        printf("Error reading input\n");
        return 1;
    }

    for (i = 0; str[i] != '\0'; i++) {
      str[i] = lower(str[i]);
    }

    printf("Result: %s\n", str);
    return 0;
}

int lower(int c)
{
    return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
}
