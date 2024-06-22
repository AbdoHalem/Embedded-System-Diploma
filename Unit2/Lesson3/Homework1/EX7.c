#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("##########Console-output###\n");
    //================= Code ===================
    float a = 0, b = 0;
    printf("Enter value of a: ");
    scanf("%f", &a);
    printf("Enter value of b: ");
    scanf("%f", &b);
    a = a + b;
    b = a - b;  // b = (a + b) - b = a
    a = a - b;  // a = (a + b) - a = b

    printf("After swapping, value of a = %.2f\n", a);
    printf("After swapping, value of b = %.2f\n", b);
    // =========================================
    printf("###########################\n");
    return 0;
}
