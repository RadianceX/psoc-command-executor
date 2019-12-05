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
#ifndef CUSTOM_COMMANDS_H
#define CUSTOM_COMMANDS_H
#include "custom_commands.h"
#endif /* custom_commands.h */
#ifndef CIPHER_H
#define CIPHER_H
#include "cipher.h"
#endif /* cipher.h */

void select_command(int is_show_help, context_table *context, char* arg0){
    if (DEBUG_ENABLED)  { 
        print("\r\nCALL select_command, arg:", arg0);
    }
    if (is_show_help==1){ 
        print(
            "\r\n select (uint)cp_num                           - select cipher",
            "\r\n cp_num:                                       - cipher type",
            "\r\n    1 - shift cipher ; cp_args: (int)shift",
            "\r\n    2 - replace cipher; cp_args: none",
            "\r\n    3 - homophonic replacement cipher; cp_args: none",
            "\r\n    4 - playfair cipher; cp_args: (str)message (str)key",
            "\r\n    5 - vigenere cipher; cp_args: (str)message (str)key",
            "\r\n    7 - xor cipher; cp_args: (str)message (str)key"
        ); 
        return;
    }
    context->cipher = *arg0;
}

void encrypt_command(int is_show_help, context_table *context, char* text, char* cp_arg){
    if (DEBUG_ENABLED)  { print("\r\nCALL encrypt_command args: ", text, ", ", cp_arg); }
    if (is_show_help==1){ 
        print(
            "\r\n encrypt (string)text (args)cp_args            - encrypt text by selected cipher"
        );
        return; 
    }
    print("\r\n");
    switch(context->cipher){
        case '1':{
            shift_cipher_encode(text, cp_arg);
            break;
        }
        case '2':{
            replace_cipher_encode(text);
            break;
        }
        case '3':{
            homophonic_cipher_encode(text);
            break;
        }
        case '4':{
            playfair_cipher_encode(text, cp_arg);
            break;
        }
        case '5':{
            vigenere_encode(text, cp_arg);
            break;
        }
        case '7':{
            xor_cipher_encode(text);
            break;
        }   
        default:{
            print("\r\nInvalid cipher");
        }
    }
    print("\r\n");
}

/* [] END OF FILE */
