/* A simple #define declaration processor
 * TODO
 * - Handle arguments
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100
#define HASHSIZE 101
#define BUFSIZE 100

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

static struct nlist *hashtab[HASHSIZE];

// Function declarations
int getword(char *word, int lim);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
unsigned hash(char *s);
int getch(void);
void ungetch(int c);

int main()
{
    char word[MAXWORD];
    struct nlist *np;
    int c;

    while ((c = getword(word, MAXWORD) != EOF)) {
        if (strcmp(word, "#define") == 0) {
			char name[MAXWORD], defn[MAXWORD];
			getword(name, MAXWORD);  // get name
			getword(defn, MAXWORD);  // get definition
			install(name, defn);
        } else if (isalpha(word[0])) {
            if ((np = lookup(word)) != NULL)
                printf("%s", np->defn);
            else
                printf("%s", word);
        } else {
            printf("%s", word);
        }
    }
    return 0;
}

// Buffer handling
char buf[BUFSIZE];
int bufp = 0;

// Get character
int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

// Step back a character
void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

// Hash function
unsigned hash(char *s) {
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

// Lookup: find name in hashtab
struct nlist *lookup(char *s) {
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}

// Install: put (name, defn) in hashtab
struct nlist *install(char *name, char *defn) {
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {
        // New name so hash it and insert at head of linked list
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);         // generates node index
        np->next = hashtab[hashval];  // point new node's next pointer to old chain
        hashtab[hashval] = np;        // insert new node at head of chain
    } else
        // Remove old definition
        free((void *) np->defn);
    // Write new definition
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
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

	// Handle identifiers and preprocessor directives
	if (isalpha(c) || c == '_' || c == '#') {
		if (lim > 0) { *w++ = c; lim--; }
		while (lim > 0 && (c = getch(), (isalnum(c) || c == '_'))) {
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
