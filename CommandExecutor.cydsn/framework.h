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
#define False 0  
#define True (!False)
#define COMMAND_LEN 32

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

uint8 DEBUG_ENABLED = 0;
struct Context{
    char cipher;
    char command[COMMAND_LEN];
};

void print( const char * arg1, ... );
char* fill_command_tail(char* buffer, uint16 start_position);
void shuffle(int *buffer, size_t lenght);

/* [] END OF FILE */
