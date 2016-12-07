#include <stdio.h>

int main()
{
    float a, b, c;
    printf("start value:");
    scanf("%f", &a);
    printf("end value:");
    scanf("%f", &b);
    printf("increment by:");
    scanf("%f", &c);
    while (a <= b)
    {
	if ((a + c > 98.6) && (a < 98.6))
        {
            printf("%6.2f degrees F = %6.2f degrees C\n",
                98.6, (98.6 - 32.0) * 5.0 / 9.0);
        }
        printf("%6.2f degrees F = %6.2f degrees C\n",
            a, (a - 32.0) * 5.0 / 9.0);
        a = a + c;
    }
    return 0;
}
