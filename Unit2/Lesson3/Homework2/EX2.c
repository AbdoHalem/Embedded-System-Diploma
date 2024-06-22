#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("##########Console-output###\n");
    //================= Code ===================
    unsigned char const vowels[] = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
    unsigned char a = 0, check = 0;
    printf("Enter an alphabet: ");
    scanf("%c", &a);
    unsigned char i = 0;
    for(i = 0; i < sizeof(vowels); i++){
        if(vowels[i] == a){
            check = 1;;
        }
        else{
            continue;
        }
    }
    if(check == 1){
        printf("%c is a vowel\n", a);
    }
    else{
        printf("%c is a consonant\n", a);
    }
    // =========================================
    printf("###########################\n");
    return 0;
}