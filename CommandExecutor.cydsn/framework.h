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
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#ifndef PROJECT_H
#define PROJECT_H
#include "project.h"
#endif /* project.h */

#define False 0  
#define True (!False)

#define COMMAND_LEN 32

#define print(...) fprint(__VA_ARGS__, 0)

typedef struct {
    char cipher;
    char command[COMMAND_LEN];
} context_table;

void fprint( const char* begin, ... );
void fill_buffer_tail(char* buffer, size_t buffer_len, uint16 start_position);
void shuffle(int *buffer, size_t lenght);
int randint(int min, int max);

#define DEBUG_ENABLED False

/* [] END OF FILE */
