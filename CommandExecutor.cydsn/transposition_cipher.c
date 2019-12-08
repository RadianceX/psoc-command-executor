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


void transposition_encode(char* text){
    if (DEBUG_ENABLED){ print("CALL transposition_encode, args:", text, "\r\n"); }    
    print("Input message:    ", text);
    char transposition[] = {2,4,0,1,3};
    char InpBuf[COMMAND_LEN] = {'\0'};
    char OutBuf[COMMAND_LEN] = {'\0'};
    
    char ch;
    uint16 len = 6;  // sizeof(transposition)
    uint16 i, j, k;
    
    // copy input message to buffer
    for (i=0; i<strlen(text); i++){
        InpBuf[i] = text[i];
    }
    j=i=0;
    print("Ciphered message: ");
    do {
        for( ; '\0'!=(ch = InpBuf[i]) && ch != '\n';++i){
            OutBuf[j++] = ch;
            if(j == len){
                j=0;
                ++i;
                break;
            }
        }
        while(j!=0){
            OutBuf[j++] = '.';//pading if(i % len != 0)
            if(j == len){
                j = 0;
            }
        }
        for(k=0;i && k<len;++k){
            UART_PutChar(OutBuf[transposition[k]]);
        }
    } while (ch != '\n' && ch != '\0');
}

/* [] END OF FILE */
