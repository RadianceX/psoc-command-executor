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

void vigenere_encode(char* text, char* _key){
    int numstr[COMMAND_LEN],numkey[COMMAND_LEN],numcipher[COMMAND_LEN];
    char str[COMMAND_LEN], key[COMMAND_LEN] = {'\0'};
    uint16 i,j;
    //converting entered string to Capital letters
    for(i=0,j=0;i<strlen(text);i++){
        if(str[i]!=' '){
            str[j]=toupper(text[i]);   
            j++;
        }
    }
    str[j]='\0';
    print("Input message:    ", str);
    //Storing string in terms of ascii
    for(i=0;i<strlen(text);i++){
        numstr[i]=str[i]-'A';
    }
    print("Key:              ", _key);
    //converting entered key to Capital letters
    for(i=0,j=0;i<strlen(_key);i++){
        if(key[i]!=' '){
            key[j]=toupper(_key[i]);   
            j++;
        }
    }
    key[j]='\0';
    //Assigning key to the string
    for(i=0;i<strlen(text);){
        for(j=0;(j<strlen(_key))&&(i<strlen(text));j++){
            numkey[i]=key[j]-'A';
            i++;
        }
    }
    for(i=0;i<strlen(text);i++){
        numcipher[i]=numstr[i]+numkey[i];
        if(numcipher[i]>25){
            numcipher[i]=numcipher[i]-26;
        }
    }
 
    print("Ciphered message: ");   
    for(i=0;i<strlen(str);i++)
    {
        UART_PutChar(numcipher[i]+'A'); 
    }
}

/* [] END OF FILE */
