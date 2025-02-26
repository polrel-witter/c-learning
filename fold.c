#include <stdio.h>
#include <string.h>

#define MAX_LINE 1000
#define MAX_WORD 100
#define FOLD_WIDTH 80

int main(void)
{
    int c;
    int line_pos = 0;    // Current position in line
    int word_pos = 0;    // Current position in word buffer
    char line[MAX_LINE];
    char word[MAX_WORD];

    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            word[word_pos] = '\0';

            // If word fits current line
            if (line_pos == 0 || line_pos + 1 + word_pos <= FOLD_WIDTH) {
                if (line_pos > 0) {
                    line[line_pos] = ' ';
                    line_pos++;
                }
                strcat(line + line_pos, word);
                line_pos += word_pos;
            } else {
                // Print current line and start new one with word
                if (line_pos > 0) {
                    line[line_pos] = '\0';
                    printf("%s\n", line);
                }
                strcpy(line, word);
                line_pos = word_pos;
            }

            word_pos = 0;

            // Handle newline
            if (c == '\n' && line_pos > 0) {
                line[line_pos] = '\0';
                printf("%s\n", line);
                line_pos = 0;
            }
        } else if (word_pos < MAX_WORD - 1) {
            word[word_pos++] = c;
        }
    }

    // Print any remaining text
    if (word_pos > 0) {
        word[word_pos] = '\0';
        if (line_pos + word_pos <= FOLD_WIDTH) {
            if (line_pos > 0) {
                line[line_pos] = ' ';
                line_pos++;
            }
            strcat(line + line_pos, word);
            line_pos += word_pos;
        }
    }
    if (line_pos > 0) {
        line[line_pos] = '\0';
        printf("%s\n", line);
    }

    return 0;
}
