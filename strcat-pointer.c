#include <stdio.h>
#include <string.h>

int main(void)
{
  char str1[1000], str2[1000];
  printf("Enter first string: ");
  scanf("%s", str1);
  printf("Enter second string: ");
  scanf("%s", str2);

  concat(str1, str2);
  printf("Concatenated string: %s\n", str1);
  return 0;
}

// copies the string t to the end of s
void concat(char *s, char *t)
{
    // find the end of s
    while (*s != '\0')
        s++;

    // copy t to end of s
    while (*t != '\0') {
        *s = *t;
        s++;
        t++;
    }

    // add null terminator
    *s = '\0';
}
