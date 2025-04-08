/* Word frequency counter for C keywords
 * Handles string constants, comments, and preprocessor directives
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* Data structures */
struct key {
    char *word;
    int count;
} keytab[] = {
    { "break", 0 },
    { "case", 0 },
    { "char", 0 },
    { "continue", 0 },
    { "do", 0 },
    { "else", 0 },
    { "for", 0 },
    { "if", 0 },
    { "int", 0 },
    { "main", 0 },
    { "return", 0 },
    { "static", 0 },
    { "switch", 0 },
    { "void", 0 },
    { "while", 0 }
};

/* Constants */
#define MAXWORD 100
#define BUFSIZE 100
#define NKEYS sizeof(struct key)

/* Function declarations */
int getword(char *, int);
int binsearch(char *, struct key *, int);
int getch(void);
void ungetch(int);

/* Main program */
int main()
{
    int n;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]))
            if ((n = binsearch(word, keytab, NKEYS)) >= 0)
                keytab[n].count++;
    for (n = 0; n < NKEYS; n++)
        if (keytab[n].count > 0)
            printf("%4d %s\n",
                    keytab[n].count, keytab[n].word);
    return 0;
}

/* Buffer management */
char buf[BUFSIZE];    /* buffer for ungetch */
int bufp = 0;         /* next free position in buf */

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

/* Core word processing */
int binsearch(char *word, struct key *tab, int n)
{
    int low = 0;
    int high = n - 1;
    int mid;
    int cond;

    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, tab[mid].word)) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}

int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;

    if (c == EOF) {
        *w++ = c;
        *w = '\0';
        return c;
    }

    if (c == '"' || c == '\'') {
        int quote = c;
        *w++ = c;
        while ((c = getch()) != quote && c != EOF && --lim > 0)
            *w++ = c;
        if (c == quote)
            *w++ = c;
        *w = '\0';
        return word[0];
    }

    if (c == '/') {
        if ((c = getch()) == '*') {
            while ((c = getch()) != EOF) {
                if (c == '*') {
                    if ((c = getch()) == '/')
                        break;
                    ungetch(c);
                }
            }
            return getword(word, lim);
        } else if (c == '/') {
            while ((c = getch()) != '\n' && c != EOF)
                ;
            return getword(word, lim);
        }
        ungetch(c);
        c = '/';
    }

    if (c == '#') {
        while ((c = getch()) != '\n' && c != EOF)
            ;
        return getword(word, lim);
    }

    if (isalpha(c) || c == '_') {
        *w++ = c;
        while (--lim > 0) {
            c = getch();
            if (!isalnum(c) && c != '_') {
                ungetch(c);
                break;
            }
            *w++ = c;
        }
        *w = '\0';
        return word[0];
    }

    *w++ = c;
    *w = '\0';
    return c;
}
