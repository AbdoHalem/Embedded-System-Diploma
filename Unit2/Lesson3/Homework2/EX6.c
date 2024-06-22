#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("##########Console-output###\n");
    //================= Code ===================
    unsigned int n = 0, i = 0;
    printf("Enter an integer: ");
    scanf("%d", &n);
    
    int sum = 0;
    for(i = 1; i <= n; i++){
        sum += i;
    }
    printf("Sum = %d\n", sum);
    // =========================================
    printf("###########################\n");
    return 0;
}