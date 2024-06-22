#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("##########Console-output###\n");
    //================= Code ===================
    float number = 0;
    unsigned char i = 0;
    printf("Enter a number: ");
    scanf("%f", &number);
    
    if(0 < number){
        printf("%.2f is positive.\n", number);
    }
    else if(0 > number){
        printf("%.2f is negative.\n", number);
    }
    else{
        printf("You entered zero.\n", number);
    }
    
    // =========================================
    printf("###########################\n");
    return 0;
}