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
#define False 0  
#define True (!False)
#define COMMAND_LEN 32

#include "project.h"

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>


CY_ISR_PROTO(UARTIsrHandler);

// service block
void __fill_command_tail(uint8 begin);  // заповнює кінець строки '\0'
void print(const char * arg1, ...);     // виводить текст через UART, останній аргумент обов'язково NULL!
void execute(char *command);            // передає аргументи у вибрану функцію
void help(int is_show_help, char*);
int random_int(int min, int max);

// commands block
void select_command(int is_show_help, char* arg0 );
void encrypt_command(int is_show_help, char* text, char* cp_arg);
void shift_cipher_encode(char*, char*);
void replace_cipher_encode(char* text);
void homophonic_cipher_encode(char* text);

// variables
uint8 DEBUG_ENABLED = 0;
char is_command_ready = False;
char command[COMMAND_LEN];
char cipher = '1';


// Strongly recommended to follow this pattern
void function_name_command(int is_show_help, char* arg0, char* arg1, ...){
    if (DEBUG_ENABLED)  { print("\r\nCALL function_name_command, args: ", arg0, ", ", arg1, NULL); }
    if (is_show_help==1){ print("\r\ndetailed info about function", NULL); return; }

    /* Function code */
}

int main(void){
    CyGlobalIntEnable;
    UART_Start();
    isr_UART_StartEx(UARTIsrHandler);

    help(1, NULL);
    UART_PutString("\r\n>");
    
    for(;;)
    {
        if (is_command_ready == True)
        {
            execute(command);
            is_command_ready = False;
        }
    }
}

void execute(char command[]){
    UART_PutString("\r\n");
    
    char tmp[COMMAND_LEN];
    strcpy(tmp, command);
    char *cmd = strtok(tmp, " ");
    char *arg0 = strtok(NULL, " ");
    char *arg1 = strtok(NULL, " ");
    // char *arg2 = strtok(NULL, " ");

    if (strcmp(cmd, "help") == 0)
    {
        help(0, arg0);
    }
    else if (strcmp(cmd, "select") == 0)
    {
        select_command(0, arg0);
    }  
    else if (strcmp(cmd, "encrypt") == 0)
    {
        encrypt_command(0, arg0, arg1);
    }
    else
    {
        print("Invalid command", NULL);
    }
    
    UART_PutString("\r\n>");
}

void help(int is_show_help, char* function){
    if (DEBUG_ENABLED){ print("CALL help_command, args: ", function, NULL); }
    
    print("\r\n Available commands:", NULL);
    select_command(1,NULL);
    encrypt_command(1, NULL, NULL);
}

void select_command(int is_show_help, char* arg0){
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

    cipher = *arg0;
}

void encrypt_command(int is_show_help, char* text, char* cp_arg){
    if (DEBUG_ENABLED)  { print("\r\nCALL encrypt_command args: ", text, ", ", cp_arg, NULL); }
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
            print("invalid cipher", NULL);
        }
    }
}

void shift_cipher_encode(char* text, char * shift_text){
    if (DEBUG_ENABLED){ print("\r\nCALL shift_cipher_encode, args:", text,", ", shift_text, NULL); }
    
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
    
    print(text, NULL);
}

void replace_cipher_encode(char* text){
    if (DEBUG_ENABLED){ print("\r\nCALL replace_cipher_encode, args:", text, NULL); }
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
    print(text, NULL);
}

void homophonic_cipher_encode(char* text){
    if (DEBUG_ENABLED)  { print("\r\nCALL homophonic_cipher_encode, args: ", text, NULL); }

    char* c_alphabet[1000] = { "763", "283", "146", "117", "258", "44", "221", "824", "558", "22", 
        "861", "909", "900", "842", "238", "664", "219", "688", "683", "916", "586", "294", "613", "163", "959", "517", "519", "992", "166", "463", "165", "923", "274", "945", "91", "110", "12", "428", "255", "68", 
        "779", "598", "507", "755", "822", "452", "405", "942", "453", "306", "521", "589", "993", "740", "93", "685", "33", "615", "397", "4", "395", "477", "864", "581", "592", "392", "961", "890", "708", "545", 
        "70", "265", "669", "495", "985", "856", "516", "145", "357", "938", "838", "394", "307", "290", "773", "988", "410", "172", "345", "126", "797", "566", "574", "717", "703", "270", "384", "202", "528", "515", 
        "882", "94", "469", "869", "150", "551", "746", "337", "154", "681", "573", "687", "998", "977", "849", "829", "888", "396", "654", "538", "131", "148", "176", "940", "183", "322", "414", "196", "30", "557", 
        "862", "868", "111", "5", "367", "164", "95", "823", "736", "84", "448", "329", "472", "57", "805", "115", "738", "833", "261", "933", "867", "491", "122", "986", "532", "121", "52", "751", "975", "640", 
        "225", "198", "655", "62", "617", "484", "438", "444", "523", "769", "733", "256", "810", "978", "289", "591", "877", "979", "705", "218", "542", "954", "605", "157", "192", "430", "616", "107", "407", "398", 
        "943", "471", "837", "644", "737", "994", "200", "996", "340", "158", "612", "748", "449", "167", "19", "399", "756", "601", "870", "619", "67", "376", "686", "264", "653", "921", "684", "382", "548", "620", 
        "241", "732", "137", "727", "497", "642", "609", "671", "828", "127", "635", "891", "224", "580", "243", "296", "478", "878", "750", "373", "273", "194", "390", "957", "801", "169", "312", "153", "721", "186", 
        "36", "41", "97", "530", "49", "599", "266", "75", "355", "116", "361", "723", "187", "858", "787", "83", "905", "576", "257", "7", "213", "860", "984", "74", "53", "103", "151", "892", "47", "113", 
        "754", "71", "768", "31", "149", "604", "896", "282", "155", "924", "46", "722", "980", "419", "628", "670", "73", "124", "38", "539", "501", "214", "774", "510", "245", "639", "715", "974", "387", "925", 
        "919", "459", "458", "412", "259", "667", "106", "60", "678", "637", "659", "424", "927", "767", "359", "279", "606", "554", "473", "416", "92", "569", "607", "293", "481", "499", "457", "34", "502", "848", 
        "559", "952", "58", "78", "881", "181", "596", "701", "983", "793", "368", "791", "311", "336", "488", "480", "614", "98", "391", "971", "799", "281", "96", "622", "220", "901", "907", "277", "456", "18", 
        "885", "505", "713", "696", "782", "40", "209", "468", "248", "588", "321", "934", "570", "440", "79", "718", "309", "808", "242", "335", "268", "475", "500", "317", "119", "16", "178", "37", "886", "536", 
        "175", "237", "936", "745", "470", "292", "72", "786", "101", "593", "602", "400", "82", "420", "331", "485", "625", "413", "379", "989", "442", "873", "766", "955", "171", "462", "899", "482", "326", "935", 
        "634", "418", "582", "161", "798", "380", "66", "794", "812", "134", "403", "564", "534", "487", "182", "866", "362", "50", "260", "141", "234", "832", "630", "346", "123", "690", "461", "159", "86", "446", 
        "0", "949", "185", "883", "205", "133", "514", "334", "371", "511", "301", "374", "25", "800", "835", "350", "401", "333", "85", "673", "15", "578", "563", "851", "142", "349", "252", "647", "649", "843", 
        "743", "506", "26", "759", "765", "320", "951", "932", "707", "125", "854", "503", "228", "29", "836", "546", "315", "308", "679", "898", "190", "706", "287", "518", "697", "365", "692", "342", "180", "611", 
        "189", "223", "344", "590", "206", "377", "691", "871", "632", "204", "20", "571", "665", "731", "138", "173", "816", "17", "348", "784", "211", "906", "11", "135", "271", "880", "666", "714", "857", "109", 
        "656", "422", "284", "162", "278", "341", "236", "674", "55", "404", "964", "783", "230", "152", "479", "928", "298", "623", "802", "381", "694", "339", "699", "811", "742", "454", "541", "253", "549", "325", 
        "35", "87", "139", "447", "902", "675", "493", "948", "494", "460", "160", "375", "547", "369", "803", "465", "486", "347", "997", "352", "976", "207", "987", "579", "464", "353", "941", "652", "43", "944", 
        "725", "771", "354", "432", "436", "785", "724", "522", "661", "351", "216", "496", "59", "1", "476", "427", "597", "760", "567", "922", "556", "668", "32", "953", "695", "48", "272", "100", "54", "509", 
        "904", "770", "199", "966", "305", "863", "421", "967", "360", "338", "847", "817", "806", "761", "610", "796", "587", "99", "734", "968", "327", "585", "633", "643", "758", "89", "753", "42", "303", "887", 
        "80", "972", "962", "411", "330", "929", "772", "965", "807", "834", "973", "700", "393", "780", "918", "302", "595", "323", "853", "425", "790", "433", "233", "426", "217", "946", "319", "445", "555", "910", 
        "366", "789", "27", "859", "618", "657", "389", "191", "280", "600", "193", "662", "8", "629", "930", "560", "201", "525", "638", "879", "698", "749", "2", "208", "232", "875", "21", "288", "291", "845", 
        "409", "212", "69", "112", "897", "88", "831", "64", "704", "572", "937", "711", "76", "819", "912", "249", "179", "328", "775", "14", "550", "251", "483", "318", "850", "383", "575", "90", "441", "450", 
        "594", "415", "672", "39", "776", "356", "939", "636", "719", "130", "908", "132", "689", "764", "474", "818", "231", "712", "894", "562", "184", "65", "645", "108", "267", "434", "520", "372", "24", "386", 
        "641", "304", "147", "429", "23", "489", "51", "663", "830", "140", "809", "262", "931", "825", "709", "627", "104", "855", "531", "250", "982", "9", "275", "568", "876", "874", "956", "417", "813", "203", 
        "626", "543", "735", "561", "247", "744", "716", "926", "512", "408", "728", "466", "246", "324", "884", "343", "577", "490", "846", "170", "999", "535", "895", "826", "105", "680", "136", "63", "815", "729", 
        "156", "240", "658", "917", "210", "865", "269", "10", "235", "960", "195", "144", "215", "969", "492", "174", "682", "914", "646", "188", "435", "781", "913", "439", "423", "102", "263", "963", "762", "693", 
        "314", "844", "544", "239", "388", "332", "364", "827", "676", "143", "81", "537", "814", "28", "114", "660", "950", "792", "820", "197", "841", "120", "451", "608", "893", "431", "947", "316", "61", "443", 
        "778", "297", "524", "752", "739", "13", "378", "300", "295", "720", "726", "529", "370", "244", "702", "995", "584", "118", "358", "565", "437", "45", "286", "513", "741", "991", "498", "6", "990", "222", 
        "710", "3", "920", "981", "958", "406", "804", "128", "872", "508", "310", "177", "285", "533", "839", "540", "385", "651", "970", "168", "227", "313", "129", "903", "504", "254", "229", "821", "889", "402", 
        "911", "757", "467", "624", "226", "788", "747", "455", "553", "77", "527", "603", "852", "299", "363", "795", "777", "650", "552", "648", "631", "276", "915", "677", "730", "56", "526", "621", "840", "583" 
    };
    
    uint8 i;
    char value;
    char* encrypted_text[COMMAND_LEN];

    for (i=0; i<strlen(text); i++){
        value = text[i];

        /* == following code is automatically generated == */
        switch(value){
            case 'a': {
                encrypted_text[i] = c_alphabet[random_int(0, 80)];
                break;
            }
            case 'A': {
                encrypted_text[i] = c_alphabet[random_int(0, 80)];
                break;
            }
            case 'b': {
                encrypted_text[i] = c_alphabet[random_int(81, 94)];
                break;
            }
            case 'B': {
                encrypted_text[i] = c_alphabet[random_int(81, 94)];
                break;
            }
            case 'c': {
                encrypted_text[i] = c_alphabet[random_int(95, 121)];
                break;
            }
            case 'C': {
                encrypted_text[i] = c_alphabet[random_int(95, 121)];
                break;
            }
            case 'd': {
                encrypted_text[i] = c_alphabet[random_int(122, 160)];
                break;
            }
            case 'D': {
                encrypted_text[i] = c_alphabet[random_int(122, 160)];
                break;
            }
            case 'e': {
                encrypted_text[i] = c_alphabet[random_int(161, 290)];
                break;
            }
            case 'E': {
                encrypted_text[i] = c_alphabet[random_int(161, 290)];
                break;
            }
            case 'f': {
                encrypted_text[i] = c_alphabet[random_int(291, 319)];
                break;
            }
            case 'F': {
                encrypted_text[i] = c_alphabet[random_int(291, 319)];
                break;
            }
            case 'g': {
                encrypted_text[i] = c_alphabet[random_int(320, 339)];
                break;
            }
            case 'G': {
                encrypted_text[i] = c_alphabet[random_int(320, 339)];
                break;
            }
            case 'h': {
                encrypted_text[i] = c_alphabet[random_int(340, 391)];
                break;
            }
            case 'H': {
                encrypted_text[i] = c_alphabet[random_int(340, 391)];
                break;
            }
            case 'i': {
                encrypted_text[i] = c_alphabet[random_int(392, 456)];
                break;
            }
            case 'I': {
                encrypted_text[i] = c_alphabet[random_int(392, 456)];
                break;
            }
            case 'j': {
                encrypted_text[i] = c_alphabet[random_int(457, 458)];
                break;
            }
            case 'J': {
                encrypted_text[i] = c_alphabet[random_int(457, 458)];
                break;
            }
            case 'k': {
                encrypted_text[i] = c_alphabet[random_int(459, 462)];
                break;
            }
            case 'K': {
                encrypted_text[i] = c_alphabet[random_int(459, 462)];
                break;
            }
            case 'l': {
                encrypted_text[i] = c_alphabet[random_int(463, 496)];
                break;
            }
            case 'L': {
                encrypted_text[i] = c_alphabet[random_int(463, 496)];
                break;
            }
            case 'm': {
                encrypted_text[i] = c_alphabet[random_int(497, 521)];
                break;
            }
            case 'M': {
                encrypted_text[i] = c_alphabet[random_int(497, 521)];
                break;
            }
            case 'n': {
                encrypted_text[i] = c_alphabet[random_int(522, 593)];
                break;
            }
            case 'N': {
                encrypted_text[i] = c_alphabet[random_int(522, 593)];
                break;
            }
            case 'o': {
                encrypted_text[i] = c_alphabet[random_int(594, 672)];
                break;
            }
            case 'O': {
                encrypted_text[i] = c_alphabet[random_int(594, 672)];
                break;
            }
            case 'p': {
                encrypted_text[i] = c_alphabet[random_int(673, 692)];
                break;
            }
            case 'P': {
                encrypted_text[i] = c_alphabet[random_int(673, 692)];
                break;
            }
            case 'q': {
                encrypted_text[i] = c_alphabet[random_int(693, 694)];
                break;
            }
            case 'Q': {
                encrypted_text[i] = c_alphabet[random_int(693, 694)];
                break;
            }
            case 'r': {
                encrypted_text[i] = c_alphabet[random_int(695, 763)];
                break;
            }
            case 'R': {
                encrypted_text[i] = c_alphabet[random_int(695, 763)];
                break;
            }
            case 's': {
                encrypted_text[i] = c_alphabet[random_int(764, 824)];
                break;
            }
            case 'S': {
                encrypted_text[i] = c_alphabet[random_int(764, 824)];
                break;
            }
            case 't': {
                encrypted_text[i] = c_alphabet[random_int(825, 929)];
                break;
            }
            case 'T': {
                encrypted_text[i] = c_alphabet[random_int(825, 929)];
                break;
            }
            case 'u': {
                encrypted_text[i] = c_alphabet[random_int(930, 953)];
                break;
            }
            case 'U': {
                encrypted_text[i] = c_alphabet[random_int(930, 953)];
                break;
            }
            case 'v': {
                encrypted_text[i] = c_alphabet[random_int(954, 962)];
                break;
            }
            case 'V': {
                encrypted_text[i] = c_alphabet[random_int(954, 962)];
                break;
            }
            case 'w': {
                encrypted_text[i] = c_alphabet[random_int(963, 977)];
                break;
            }
            case 'W': {
                encrypted_text[i] = c_alphabet[random_int(963, 977)];
                break;
            }
            case 'x': {
                encrypted_text[i] = c_alphabet[random_int(978, 979)];
                break;
            }
            case 'X': {
                encrypted_text[i] = c_alphabet[random_int(978, 979)];
                break;
            }
            case 'y': {
                encrypted_text[i] = c_alphabet[random_int(980, 998)];
                break;
            }
            case 'Y': {
                encrypted_text[i] = c_alphabet[random_int(980, 998)];
                break;
            }
            case 'z': {
                encrypted_text[i] = c_alphabet[random_int(999, 999)];
                break;
            }
            case 'Z': {
                encrypted_text[i] = c_alphabet[random_int(999, 999)];
                break;
            }
            default: {
                encrypted_text[i] = "???";
            }
        }
    }

    for (i=0; i<strlen(text); i++){
        UART_PutString(encrypted_text[i]);
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
        __fill_command_tail(data_count);
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

int random_int(int min, int max)
{
   return min + rand() % (max+1 - min);
}

void __fill_command_tail(uint8 start_position){
    if (DEBUG_ENABLED){ print("\r\nCALL __fill_command_tail, args:", start_position, NULL); }
    uint8 i;
    for (i=start_position; i<COMMAND_LEN; i++)
    {
        command[i] = '\0';
    }
}

void print( const char * arg1, ... ){
    va_list args;
    const char * message;
    va_start( args, arg1 );
    
    UART_PutString(arg1);

    message = va_arg( args, const char * );
    while( message ) {
        UART_PutString(message);
        message = va_arg( args, const char *);
    }
    
    va_end( args );
}

/* [] END OF FILE */
