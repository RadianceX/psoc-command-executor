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

void homophonic_cipher_encode(char* text);
void playfair_cipher_encode(char* message, char* _key);
void replace_cipher_encode(char* text);
void shift_cipher_encode(char* text, char * shift_text);
void vigenere_encode(char* text, char* _key);
void xor_cipher_encode(char* message);

/* [] END OF FILE */
