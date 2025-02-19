#include <stdio.h>

/* symbolic constants */
#define LOWER 0
#define UPPER 300
#define STEP 20

/* print fahrenheit to celsius table */
main()
{
    float fahr, celsius;

    printf("%3c %6c\n", 'F', 'C');

    fahr = UPPER;
    while (fahr >= LOWER) {
        celsius = (5.0/9.0) * (fahr-32);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr = fahr - STEP;
    }
}
