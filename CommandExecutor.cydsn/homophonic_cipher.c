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

void homophonic_cipher_encode(char* text){
    if (DEBUG_ENABLED)  { print("\r\nCALL homophonic_cipher_encode, args: ", text); }

    uint16 i;
    int encrypted_text[COMMAND_LEN];
    
    int c_alphabet[1000];
    static uint8 gen = 0;
    if (gen == 0){
        for(i=0; i<1000; i++){ c_alphabet[i] = i; }
        shuffle(c_alphabet, 1000);
        gen = 1;
    }
    
    int ranges[26][2];
    int symbol_prob[26] = { 81, 14, 27, 39, 130, 29, 20, 52, 65, 2, 4, 34, 25, 72, 79, 20, 2, 69, 61, 105, 24, 9, 15, 2, 19, 1};
    int temp = 0;
    for (i=0; i<26; i++){
        ranges[i][0] = temp;
        ranges[i][1] = temp+symbol_prob[i]-1;
        temp += symbol_prob[i];
    }
    
    uint16 index;
    char value;
    for (i=0; i<strlen(text); i++){
        value = text[i];
        if (value >= 'A' && value <= 'Z'){
            index = value-65;
            encrypted_text[i] = c_alphabet[ randint( ranges[index][0], ranges[index][1])];
        } else if (value >= 'a' && value <= 'z'){
            index = value-97;
            encrypted_text[i] = c_alphabet[ randint( ranges[index][0], ranges[index][1])];
        } else {
            encrypted_text[i] = 9999;
        }
    }

    char buff[4];
    for (i=0; i<strlen(text); i++){
        UART_PutString(itoa(encrypted_text[i], buff, 10));
        UART_PutChar(' ');
    }
}

/* [] END OF FILE */
