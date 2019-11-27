#ifndef FRAMEWORK_H
#define FRAMEWORK_H
#include "framework.h"
#endif /* framework.h */
#ifndef CIPHER_H
#define CIPHER_H
#include "cipher.h"
#endif /* cipher.h */

void playfair(char ch1, char ch2, char key[5][5]){
    if (DEBUG_ENABLED)  { print("\r\nCALL function_name_command, args: ", ch1, ", ", ch2); }
    int i, j, w, x, y, z;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (ch1 == key[i][j]) {
                w = i;
                x = j;
            } else if (ch2 == key[i][j]) {
                y = i;
                z = j;
            }
        }
    }

    if (w == y){
        x = (x + 1) % 5;
        z = (z + 1) % 5;
        UART_PutChar(key[w][x]);
        UART_PutChar(key[y][z]);
    }
    else if (x == z){
        w = (w + 1) % 5;
        y = (y + 1) % 5;
        UART_PutChar(key[w][x]);
        UART_PutChar(key[y][z]);
    }
    else{
        UART_PutChar(key[w][z]);
        UART_PutChar(key[y][x]);
    }
}

void playfair_cipher_encode(char* message, char* _key){
    if (DEBUG_ENABLED)  { print("\r\nCALL function_name_command, args: ", message, ", ", _key); }
    uint8 i, j, k = 0, m = 0, n;
    char key[5][5], keyminus[25], keystr[10], str[25] = {'\0'};
    char alpa[26] = {
        'A',
        'B',
        'C',
        'D',
        'E',
        'F',
        'G',
        'H',
        'I',
        'J',
        'K',
        'L',
        'M',
        'N',
        'O',
        'P',
        'Q',
        'R',
        'S',
        'T',
        'U',
        'V',
        'W',
        'X',
        'Y',
        'Z'
    };
    uint8 t;
    
    // set key
    for (t=0;t<10;t++){
        if (t < strlen(_key)){
            keystr[t] = _key[t];
        }
        else{
            keystr[t] = '\0';
        }
    }
    // clear key from duplicate characters
    for(i=0;i<strlen(keystr);i++){
  		for(j=i+1;keystr[j] != '\0';j++){
  			if(keystr[j] == keystr[i]){
  				for(k=j;keystr[k] != '\0';k++){
					keystr[k] = keystr[k + 1];
				}
 			}
		}
	}
    // set message
    for (t=0;t<25;t++){
        if (t < strlen(message)){
            str[t] = message[t];
        }
        else{
            str[t] = '\0';
        }
    }
    
    n = strlen(keystr);
    //convert the characters to uppertext
    for (i = 0; i < n; i++) {
        if (keystr[i] == 'j') keystr[i] = 'i';
        else if (keystr[i] == 'J') keystr[i] = 'I';
        keystr[i] = toupper(keystr[i]);
    }
    //convert all the characters of message to uppercase
    for (i = 0; i < strlen(str); i++) {
        if (str[i] == 'j') str[i] = 'i';
        else if (str[i] == 'J') str[i] = 'I';
        str[i] = toupper(str[i]);
    }
    // store all characters except key
    j = 0;
    for (i = 0; i < 26; i++) {
        for (k = 0; k < n; k++) {
            if (keystr[k] == alpa[i]) break;
            else if (alpa[i] == 'J') break;
        }
        if (k == n) {
            keyminus[j] = alpa[i];
            j++;
        }
    }
    
    //construct key keymatrix
    k = 0;
    m = 0;
    print("Encrypt table: \r\n");
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (k < n) {
                key[i][j] = keystr[k];
                k++;
            } else {
                key[i][j] = keyminus[m];
                m++;
            }
            UART_PutChar(key[i][j]);
            UART_PutChar(' ');
        }
        print("\r\n");
    }
    // construct diagram and convert to cipher text
    print("\r\nEntered text: ", str, "\r\nCiphered text: ");
    for (i = 0; i < strlen(str); i++) {
        if (str[i] == 'J') str[i] = 'I';
        if (str[i + 1] == '\0') playfair(str[i], 'X', key);
        else {
            if (str[i + 1] == 'J') str[i + 1] = 'I';
            if (str[i] == str[i + 1]) playfair(str[i], 'X', key);
            else {
                playfair(str[i], str[i + 1], key);
                i++;
            }
        }
    }
}
