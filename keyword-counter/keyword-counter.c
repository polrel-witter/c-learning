/* Word frequency counter for C keywords
 * Handles string constants, comments, and preprocessor directives
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Data structures
// C keywords
struct key {
    char *word;
    int count;
} keytab[] = {
    { "auto", 0 },
    { "break", 0 },
    { "case", 0 },
    { "char", 0 },
    { "const", 0 },
    { "continue", 0 },
    { "default", 0 },
    { "do", 0 },
    { "double", 0 },
    { "else", 0 },
    { "enum", 0 },
    { "extern", 0 },
    { "float", 0 },
    { "for", 0 },
    { "goto", 0 },
    { "if", 0 },
    { "int", 0 },
    { "long", 0 },
    { "register", 0 },
    { "return", 0 },
    { "short", 0 },
    { "signed", 0 },
    { "sizeof", 0 },
    { "static", 0 },
    { "struct", 0 },
    { "switch", 0 },
    { "typedef", 0 },
    { "union", 0 },
    { "unsigned", 0 },
    { "void", 0 },
    { "volatile", 0 },
    { "while", 0 }
};

// Constants
#define MAXWORD 100
#define BUFSIZE 100
#define NKEYS (sizeof(keytab) / sizeof(struct key))

// Function declarations
int getword(char *, int);
int binsearch(char *, struct key *, int);
int getch(void);
void ungetch(int);

// Main program
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

// Buffer management
char buf[BUFSIZE];    // buffer for ungetch
int bufp = 0;         // next free position in buf

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

// Core word processing
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

// Word search
int getword(char *word, int lim)
{
    int c;
    char *w = word;

    lim--; // Ensure we always have space for null terminator

    // Skip whitespace
    while (isspace(c = getch()))
        ;

    // Handle EOF
    if (c == EOF) {
        *w++ = c;
        *w = '\0';
        return c;
    }

    // Handle string constants
    if (c == '"' || c == '\'') {
        int quote = c;
        if (lim > 0) { *w++ = c; lim--; }
        while ((c = getch()) != quote && c != EOF && lim > 0) {
            *w++ = c;
            lim--;
        }
        if (c == quote && lim > 0) {
            *w++ = c;
        }
        *w = '\0';
        return word[0];
    }

    // Handle comments
    if (c == '/') {
        if ((c = getch()) == '*') {
            while ((c = getch()) != EOF) {
                if (c == '*') {
                    if ((c = getch()) == '/')
                        break;
                    ungetch(c);
                }
            }
            return getword(word, lim + 1); // +1 to restore original limit
        } else if (c == '/') {
            while ((c = getch()) != '\n' && c != EOF)
                ;
            return getword(word, lim + 1); // +1 to restore original limit
        }
        ungetch(c);
        c = '/';
    }

    // Handle preprocessor
    if (c == '#') {
        while ((c = getch()) != '\n' && c != EOF)
            ;
        return getword(word, lim + 1);
    }

    // Handle identifiers
    if (isalpha(c) || c == '_') {
        if (lim > 0) { *w++ = c; lim--; }
        while (lim > 0 && (c = getch(), isalnum(c) || c == '_')) {
            *w++ = c;
            lim--;
        }
        if (!isalnum(c) && c != '_')
            ungetch(c);
        *w = '\0';
        return word[0];
    }

    // Handle single character
    if (lim > 0) { *w++ = c; }
    *w = '\0';
    return c;
}
