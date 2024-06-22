#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("##########Console-output###\n");
    //================= Code ===================
    unsigned char operator = 0;
    printf("Enter operator either + or - or * or /: ");
    scanf("%c", &operator);
    float n1 = 0, n2 = 0;
    scanf("%f %f", &n1, &n2);

    switch (operator)
    {
    case  '+':
        printf("%.2f %c %.2f = %.2f\n", n1, operator, n2, n1+n2);
        break;
    case  '-':
        printf("%.2f %c %.2f = %.2f\n", n1, operator, n2, n1-n2);
        break;
    case  '*':
        printf("%.2f %c %.2f = %.2f\n", n1, operator, n2, n1*n2);
        break;
    case  '/':
        printf("%.2f %c %.2f = %.2f\n", n1, operator, n2, n1/n2);
        break;
    default:
        printf("Invalid Operator!\n");
        break;
    }
    // =========================================
    printf("###########################\n");
    return 0;
}