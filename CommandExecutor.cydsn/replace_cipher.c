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
#include "framework.h"

void replace_cipher_encode(char* text){
    if (DEBUG_ENABLED){ print("\r\nCALL replace_cipher_encode, args:", text); }
    char c_alphabet[] = {
        'r', 's', 'A', '7', 'g', 'p', 'U', 'S', 'c',
        'D', 'y', 'n', 'T', '4', 'u', 'w', 'X', 'd', 'e', 
        'm', 'L', '0', '3', 'q', 'R', 'x', 'I', 'i', 'W', 
        '8', 'j', '6', 'b', 'v', 'F', '9', 'J', 'K', 
        'f', 'Y', 'Q', '5', 'O', 'o', 'M', 'B', 'a', 
        'G', '1', 'h', 'V', 'N', '0', 'z', 'P', 'l', '2', 
        'H', 'k', 'E', 'Z', 'C', 't'};
    char value;
    uint8 i;
    for (i=0;i<strlen(text);i++){
        value = text[i];
        if (value >= 'A' && value <= 'Z'){
            value -= 65;
            text[i] = c_alphabet[(int)value];
        }
        else if (value >= 'a' && value <= 'z'){
            value = (value - 97) + 26;
            text[i] = c_alphabet[(int)value];
        }
        else if (value >= '0' && value <= '9'){
            value = (value - 48) + 52;
            text[i] = c_alphabet[(int)value];
        }
    }
    print(text);
}

/* [] END OF FILE */
