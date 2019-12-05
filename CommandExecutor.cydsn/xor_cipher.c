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


void xor_cipher_encode(char* message){
    if (DEBUG_ENABLED){ print("\r\nCALL xor_cipher_encode, args:", message, "\r\n"); }
    char ciphered_message[COMMAND_LEN] = {'\0'};
    
    int key [] = {'k','e','y'};
    uint16 k=0;
       
    for (int i = 0; i <strlen(message); i++) {
        if(k == 3){k = 0;}
        ciphered_message[i] = (message[i]^key[k]);
        k = k + 1;
    }
    
    print("\r\nCiphered message: ");
    for(int i = 0; i < strlen(message); i++){
        UART_PutChar(ciphered_message[i]);
    }
    print("\r\n");
}

/* [] END OF FILE */
