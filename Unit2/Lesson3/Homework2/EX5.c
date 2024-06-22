#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("##########Console-output###\n");
    //================= Code ===================
    unsigned char a = 0;
    printf("Enter a character: ");
    scanf("%c", &a);
    
    if(((a >= 97) && (a <= 122)) || ((a >= 65) && (a <= 90))){        
        printf("%c is an alphabet\n", a);
    }
    else{
        printf("is not an alphabet\n", a);
    }
    
    // =========================================
    printf("###########################\n");
    return 0;
}