#include "uart.h"

unsigned char string_buffer[100] = "learn-in-depth:Abdo";
unsigned char string_buffer2[100] = "learn-in-depth:Abdo";

int main(){
    Uart_Send_String(string_buffer);
    return 0;
}