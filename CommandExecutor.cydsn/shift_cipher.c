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

void shift_cipher_encode(char* text, char * shift_text){
    if (DEBUG_ENABLED){ print("CALL shift_cipher_encode, args:", text,", ", shift_text); }
    
    print("Input message:    ", text);
    
    int len = strlen(text);

    char value;
    int shift = atoi(shift_text);
    
    uint8 i;
    for (i=0; i<len; i++){
        value = text[i];
        if ( value >= 'A' && value <= 'Z' ){
            value += shift;
            if (value < 'A'){
                value += 26;
            }
            else if (value > 'Z'){
                value -= 26;    
            }
            text[i] = value;
        }
        else if ( value >= 'a' && value <= 'z' ){
            value += shift;
            if (value < 'a'){
                value += 26;
            }
            else if (value > 'z'){
                value -= 26;    
            }
            text[i] = value;
        }
        else if ( value >= '0' && value <= '9' ){
            value += shift;
            if (value < '0'){
                value += 10;
            }
            else if (value > '9'){
                value -= 10;    
            }
            text[i] = value;
        }
        else {
            text[i] = value; // not modify symbol
        }
    }
    
    print("Ciphered message: ", text);
}

/* [] END OF FILE */
