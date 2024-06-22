#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("##########Console-output###\n");
    //================= Code ===================
    int a = 0;
    printf("Enter an integer you want to check: ");
    scanf("%d", &a);
    if(a % 2 == 0){
        printf("%d is even\n", a);
    }
    else{
        printf("%d is odd\n", a);
    }
    // =========================================
    printf("###########################\n");
    return 0;
}