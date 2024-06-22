#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("##########Console-output###\n");
    //================= Code ===================
    float numbers[3];
    unsigned char i = 0;
    printf("Enter three numbers: ");
    for(i = 0; i < 3; i++){
        scanf("%f", &numbers[i]);
    }
    float max = numbers[0];
    for(i = 1; i < 3; i++){
        if(numbers[i] >= max){
            max = numbers[i];
        }
        else{
            continue;
        }
    }
    printf("Largest number = %.2f\n", max);
    // =========================================
    printf("###########################\n");
    return 0;
}