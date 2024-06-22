#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("##########Console-output###\n");
    //================= Code ===================
    signed int n = 0;
    printf("Enter an integer: ");
    scanf("%d", &n);
    if(n >= 0){
        unsigned int factorial = 1, i = 0;
        for(i = 1; i <= n; i++){
            factorial *= i;
        }
        printf("Factorial = %d\n", factorial);
    }
    else{
        printf("Error!!! Factorial of negative number does not exist.\n");
    }
    // =========================================
    printf("###########################\n");
    return 0;
}