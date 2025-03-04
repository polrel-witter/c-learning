#include <stdio.h>

void squeeze(char s1[], char s2[]);  /* declaration */

int main(void)  /* changed to return int */
{
  char str1[1000], str2[1000];
  printf("Enter first string: ");
  scanf("%s", str1);
  printf("Enter second string: ");
  scanf("%s", str2);

  squeeze(str1, str2);
  printf("Result: %s\n", str1);
  return 0;
}

void squeeze(char s1[], char s2[])  /* changed return type to void */
{
  int i, j, k;

  for (i = k = 0; s1[i] != '\0'; i++) {
      /* Check if current char exists in s2 */
      for (j = 0; s2[j] != '\0' && s2[j] != s1[i]; j++)
          ;
      /* Keep char if not found in s2 */
      if (s2[j] == '\0')
          s1[k++] = s1[i];
  }
  s1[k] = '\0';  /* terminate the string */
}
