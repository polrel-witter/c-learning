#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 1024    /* initial buffer size */

/* read_line now returns allocated string and sets length through pointer */
char *read_line(size_t *len);
char *copy(const char *from);

/* print the longest input line */
int main()
{
    size_t len;            /* current line length */
    size_t max = 0;        /* maximum length seen so far */
    char *line = NULL;     /* current input line */
    char *longest = NULL;  /* longest line saved here */

    while ((line = read_line(&len)) != NULL) {
        if (len > max) {
            max = len;
            char *new_longest = copy(line);
            if (new_longest == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                free(line);
                free(longest);
                return 1;
            }
            free(longest);  /* free previous longest if any */
            longest = new_longest;
        }
        free(line);  /* free current line */
    }

    if (max > 0) {   /* there was a line */
        printf("%s", longest);
        free(longest);
    }
    return 0;
}

/* read_line: read a line, return allocated string, set length through pointer */
char *read_line(size_t *outlen)
{
    size_t size = INITIAL_SIZE;
    size_t i = 0;
    int c;
    char *s = malloc(size);

    if (s == NULL)
        return NULL;

    while ((c = getchar()) != EOF && c != '\n') {
        if (i >= size - 1) {  /* need more space (leave room for \n and \0) */
            size *= 2;
            char *new_s = realloc(s, size);
            if (new_s == NULL) {
                free(s);
                return NULL;
            }
            s = new_s;
        }
        s[i++] = c;
    }

    if (c == EOF && i == 0) {  /* no more input */
        free(s);
        return NULL;
    }

    if (c == '\n')
        s[i++] = c;

    s[i] = '\0';
    *outlen = i;
    return s;
}

/* copy: allocate new string and copy from into it */
char *copy(const char *from)
{
    char *to = malloc(strlen(from) + 1);
    if (to != NULL)
        strcpy(to, from);
    return to;
}

