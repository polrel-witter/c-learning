#include <stdio.h>

/* symbolic constants */
#define LOWER 0
#define UPPER 300
#define STEP 20

/* function prototype */
float convert(float fahr);

/* print fahrenheit to celsius table */
int main(void)
{
    float fahr, celsius;

    printf("%3c %6c\n", 'F', 'C');

    fahr = UPPER;
    while (fahr >= LOWER) {
        celsius = convert(fahr);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr = fahr - STEP;
    }
}

float convert(float fahr)
{
    return (5.0/9.0) * (fahr-32);
}
