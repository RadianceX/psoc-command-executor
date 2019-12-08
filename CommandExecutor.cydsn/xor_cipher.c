/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef FRAMEWORK_H
#define FRAMEWORK_H
#include "framework.h"
#endif /* framework.h */
#ifndef CIPHER_H
#define CIPHER_H
#include "cipher.h"
#endif /* cipher.h */


void printbincharpad(char c){
    for (int i = 7; i >= 0; --i){
        UART_PutChar( (c & (1 << i)) ? '1' : '0' );
    }
}

void xor_cipher_encode(char* message){
    if (DEBUG_ENABLED){ print("CALL xor_cipher_encode, args:", message, "\r\n"); }
    uint16 i;
    char ciphered_message[COMMAND_LEN] = {'\0'};
    print("Input message: ", message);
    print("In binary: ");
    for (i=0; i<strlen(message); i++){
        printbincharpad(message[i]);
        UART_PutChar(' ');
    }
    print("");
    char key [] = {'k','e','y'};
    print("Key: key");
    print("In binary: ");
    for (i=0; i<strlen(message); i++){
        printbincharpad(key[i%3]);
        UART_PutChar(' ');
    }
    print("");
    uint16 k=0;
       
    for (int i = 0; i <strlen(message); i++) {
        if(k == 3){k = 0;}
        ciphered_message[i] = (message[i]^key[k]);
        k = k + 1;
    }
    print("Ciphered message: ");
    for(int i = 0; i < strlen(message); i++){
        UART_PutChar(ciphered_message[i]);
    }
    print("In binary: ");
    for (i=0; i<strlen(message); i++){
        printbincharpad(ciphered_message[i]);
        UART_PutChar(' ');
    }
}

/* [] END OF FILE */
