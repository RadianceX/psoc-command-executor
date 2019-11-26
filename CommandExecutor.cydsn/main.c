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

CY_ISR_PROTO(UARTIsrHandler);

// service block
void execute(context_table *context);            // передає аргументи у вибрану функцію
void help();
void main_loop(context_table *context);

// variables
char is_command_ready = False;
context_table context = {'1', {0}};


// Strongly recommended to follow this pattern
void function_name_command(int is_show_help, char* arg0, char* arg1, ...){
    if (DEBUG_ENABLED)  { print("\r\nCALL function_name_command, args: ", arg0, ", ", arg1); }
    if (is_show_help==1){ print("\r\ndetailed info about function"); return; }

    /* Function code */
}

int main(void){
    CyGlobalIntEnable;
    UART_Start();
    isr_UART_StartEx(UARTIsrHandler);

    help();
    UART_PutString("\r\n>");

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

void execute(context_table* context){
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
        encrypt_command(0, context, arg0, arg1);
    }
    else{
        print("Invalid command");
    }
    
    UART_PutString("\r\n>");
}

void help(void){
    if (DEBUG_ENABLED){ 
        print("CALL help_command, args: "); 
    }
    
    print("\r\n Available commands:");
    select_command(1, NULL, NULL);
    encrypt_command(1, NULL, NULL, NULL);
}

CY_ISR(UARTIsrHandler){
    volatile static uint16 data_count = 0;
    
    context.command[data_count] = UART_GetChar();
    UART_PutChar(context.command[data_count]);
    if (context.command[data_count] == '\r'){
        is_command_ready = True;
        fill_buffer_tail(context.command, COMMAND_LEN, data_count);
        data_count = 0;
    }
    else if (context.command[data_count] == '\b'){
        if (data_count != 0){
                data_count -= 1;
        }
    }
    else{
        data_count++;
        if (data_count == COMMAND_LEN){
            is_command_ready = True;
            data_count = 0;
        }
    }
    
    isr_UART_ClearPending();
    UART_ClearRxBuffer();
}

/* [] END OF FILE */
