#include <stdio.h>
#define SHOULD_NOT_COUNT_IF if

int main(void) {
    // if while for - keywords in comment
    int count = 0;
    char *str = "while if for"; /* keywords in string */

    /* Multi-line comment with keywords
     * if while for return void
     */

    while (count < 10) {
        if (count % 2 == 0) {
            count++;
            continue;
        } else if (count > 5) {
            break;
        }

        for (int i = 0; i < 3; i++) {
            switch (i) {
                case 0:
                    int return_code = 0;  // identifier with keyword as part
                    break;
                default:
                    continue;
            }
        }

        count++;
    }

    char quote = '\"';
    static int x = 0;

    do {
        x++;
    } while (x < 5);

    return 0;
}
