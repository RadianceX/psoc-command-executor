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


#ifndef PROJECT_H
#define PROJECT_H
#include "project.h"
#endif /* project.h */
#include "framework.h"
#include "custom_commands.c"

CY_ISR_PROTO(UARTIsrHandler);

// service block
void execute(context *context);            // передає аргументи у вибрану функцію
void help();
void main_loop(context *context);

// commands block
void encrypt_command(int is_show_help, char* text, char* cp_arg);
void shift_cipher_encode(char*, char*);
void replace_cipher_encode(char* text);
void homophonic_cipher_encode(char* text);

// variables
char is_command_ready = False;
char command[COMMAND_LEN];
char cipher = '1';


// Strongly recommended to follow this pattern
void function_name_command(int is_show_help, char* arg0, char* arg1, ...){
    if (DEBUG_ENABLED)  { PRINT("\r\nCALL function_name_command, args: ", arg0, ", ", arg1); }
    if (is_show_help==1){ PRINT("\r\ndetailed info about function"); return; }

    /* Function code */
}

int main(void){
    CyGlobalIntEnable;
    UART_Start();
    isr_UART_StartEx(UARTIsrHandler);

    help();
    UART_PutString("\r\n>");
    context context = {'1', {0}};
    for(;;)
    {
        if (is_command_ready == True)
        {
            execute(&context);
            is_command_ready = False;
        }
    }
    main_loop(&context);
}

void execute(context* context){
    UART_PutString("\r\n");
    
    char tmp[COMMAND_LEN];
    strcpy(tmp, context->command);
    char *cmd = strtok(tmp, " ");
    char *arg0 = strtok(NULL, " ");
    char *arg1 = strtok(NULL, " ");
    // char *arg2 = strtok(NULL, " ");

    if (strcmp(cmd, "help") == 0){
        help();
    }
    else if (strcmp(cmd, "select") == 0){
        select_command(0, context, arg0);
    }
    else if (strcmp(cmd, "encrypt") == 0){
        encrypt_command(0, arg0, arg1);
    }
    else{
        PRINT("Invalid command");
    }
    
    UART_PutString("\r\n>");
}

void help(void){
    if (DEBUG_ENABLED){ 
        print("CALL help_command, args: "); 
    }
    
    PRINT("\r\n Available commands:");
    select_command(1, NULL, NULL);
    encrypt_command(1, NULL, NULL);
}

void encrypt_command(int is_show_help, char* text, char* cp_arg){
    if (DEBUG_ENABLED)  { PRINT("\r\nCALL encrypt_command args: ", text, ", ", cp_arg); }
    if (is_show_help==1){ 
        print(
            "\r\n encrypt (string)text (args)cp_args            - encrypt text by selected cipher",
            NULL
        );
    return; 
    }
    
    switch(cipher){
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
        default:{
            PRINT("invalid cipher");
        }
    }
}

void shift_cipher_encode(char* text, char * shift_text){
    if (DEBUG_ENABLED){ PRINT("\r\nCALL shift_cipher_encode, args:", text,", ", shift_text); }
    
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
    
    PRINT(text);
}

void replace_cipher_encode(char* text){
    if (DEBUG_ENABLED){ PRINT("\r\nCALL replace_cipher_encode, args:", text); }
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
    PRINT(text);
}

void homophonic_cipher_encode(char* text){
    if (DEBUG_ENABLED)  { PRINT("\r\nCALL homophonic_cipher_encode, args: ", text); }

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
            encrypted_text[i] = c_alphabet[ random_int( ranges[index][0], ranges[index][1])];
        } else if (value >= 'a' && value <= 'z'){
            index = value-97;
            encrypted_text[i] = c_alphabet[ random_int( ranges[index][0], ranges[index][1])];
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


CY_ISR(UARTIsrHandler){
    volatile static uint16 data_count = 0;
    
    command[data_count] = UART_GetChar();
    UART_PutChar(command[data_count]);
    if (command[data_count] == '\r') 
    {
        is_command_ready = True;
        fill_buffer_tail(data_count);
        data_count = 0;
    }
    else if (command[data_count] == '\b'){
        if (data_count != 0){
                data_count -= 1;
        }
    }
    else 
    {
        data_count++;
        if (data_count == COMMAND_LEN)
        {
            is_command_ready = True;
            data_count = 0;
        }
    }
    
    isr_UART_ClearPending();
    UART_ClearRxBuffer();
}

void shuffle(int *array, size_t n) {
    // https://stackoverflow.com/a/6127606

    if (n > 1) 
    {
        size_t i;
        for (i = 0; i < n - 1; i++) 
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = array[j];
          array[j] = array[i];
          array[i] = t;
        }
    }
}

int random_int(int min, int max){
    return min + rand() % (max+1 - min);
}

void __fill_command_tail(uint8 start_position){
    if (DEBUG_ENABLED){ PRINT("\r\nCALL __fill_command_tail, args:", start_position); }
    uint8 i;
    for (i=start_position; i<COMMAND_LEN; i++)
    {
        command[i] = '\0';
    }
}


/* [] END OF FILE */
