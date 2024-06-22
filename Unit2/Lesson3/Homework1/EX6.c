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
    float temp = a;
    a = b;
    b = temp;
    printf("After swapping, value of a = %.2f\n", a);
    printf("After swapping, value of b = %.2f\n", b);
    // =========================================
    printf("###########################\n");
    return 0;
}
