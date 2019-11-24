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

void select_command(int is_show_help, struct Context *context, char* arg0){
    if (DEBUG_ENABLED)  { print("CALL select_command, arg:", arg0, NULL);      }
    if (is_show_help==1){ 
        print(
            "\r\n select (uint)cp_num                           - select cipher",
            "\r\n cp_num:                                       - cipher type",
            "\r\n    1 - shift cipher ; cp_args: (int)shift",
            "\r\n    2 - replace cipher; cp_args: none",
            "\r\n    3 - homophonic replacement cipher; cp_args: none",
            NULL
        ); 
    return; 
    }
    
    context->cipher = *arg0;
}

/* [] END OF FILE */
