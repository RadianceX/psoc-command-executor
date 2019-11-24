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

void __print(const char* begin, ... ){
    va_list args;
    const char* message;
    va_start(args, begin);
    
    UART_PutString(begin);

    message = va_arg(args, const char*);
    while(message) {
        UART_PutString(message);
        message = va_arg(args, const char*);
    }
    va_end(args);
}

void fill_buffer_tail(char* buffer, size_t buffer_len, uint16 start_position){
    // Fills in buffer values from start position to the end by '\0' character
    uint16 i;
    for (i=start_position; i<buffer_len; i++){
        buffer[i] = '\0';
    }
}

int randint(int min, int max){
    // Return random value in range from min to max
    return min + rand() % (max+1 - min);
}

void shuffle(int *buffer, size_t lenght){
    // Shuffles the buffer
    // https://stackoverflow.com/a/6127606

    if (lenght > 1) {
        size_t i;
        for (i = 0; i < lenght - 1; i++) {
          size_t j = i + rand() / (RAND_MAX / (lenght - i) + 1);
          int t = buffer[j];
          buffer[j] = buffer[i];
          buffer[i] = t;
        }
    }
}

/* [] END OF FILE */
