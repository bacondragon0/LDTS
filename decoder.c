#include "main.h"


int to_int(char* binary) {
    if (strcmp(binary,"000000") == 0) { return 0; }
    if (strcmp(binary,"111111") == 0) { return 63; }
    int res = 0;
    for (int i = 5; i >= 0; i--) {
        if (binary[i] == '1') {
            res = res + pow(2,5 - i);
        }
    }
    //printf("res %i\n",res);
    return res;
}

char reader(char* binary) {

    int ascii = to_int(binary);
    //printf("before conv: %i\n",ascii);
    if (1 <= ascii && ascii <= 26) { ascii = ascii + 96; }
    else if (27 <= ascii && ascii <= 52) { ascii = ascii + 38; }
    else if (53 <= ascii && ascii <= 62) { ascii = ascii - 5; }


    return (char)ascii;
}

char** decode_text(char** text, size_t lines) {
    char** str_arr = malloc(sizeof(char*) * lines);
    for (size_t line = 0; line < lines; line++) {
        str_arr[line] = malloc(sizeof(char) * (2 * strlen(text[line])) / 6);
    }

    for (size_t line = 0; line < lines; line++) {
        char* bin = text[line];
        size_t i = 0;
        size_t k = 0;
        bool end_line = false;
        bool sp_char = false;

        while (!end_line) {
            char* tmp_line = malloc(sizeof(char) * 6 + 1);
            
            if (!sp_char) {

                for (size_t j = 0; j < 6; j++) {
                    tmp_line[j] = bin[j+i];
                }
                tmp_line[6] = '\0';
                
                if (strcmp(tmp_line,"000000") == 0) { end_line = true; }
                else if (strcmp(tmp_line,"111111") == 0) {
                    str_arr[line][k] = '$';
                    sp_char = true;
                    k++;
                }
                else {
                    str_arr[line][k] = reader(tmp_line);
                    k++;
                }

                i = i + 6;
            }
            else {
                for (size_t j = 0; j < 3; j++) {
                    tmp_line[j] = bin[j+i];
                }
                tmp_line[3] = '\0';
                
                if (strcmp(tmp_line,"001") == 0) {
                    str_arr[line][k] = '0';
                }
                else if (strcmp(tmp_line,"010") == 0) {
                    str_arr[line][k] = '1';
                }
                else if (strcmp(tmp_line,"011") == 0) {
                    str_arr[line][k] = '2';
                }
                else if (strcmp(tmp_line,"100") == 0) {
                    str_arr[line][k] = '3';
                }
                else if (strcmp(tmp_line,"101") == 0) {
                    str_arr[line][k] = '4';
                }


                sp_char = false;
                i = i + 3;
                k++;
            }

            free(tmp_line);
        }
        
        if (line < lines-1) { str_arr[line][k] = '\n'; str_arr[line][k+1] = '\0'; }
        else { str_arr[line][k] = '\0'; }
    }

    return str_arr;
}

struct data* decode(struct data* content) {
    if (content->size == 0) { printf("No data to decode.\n"); return NULL; }
    if (content->conv == 0) { return content; }

    struct data* out = malloc(sizeof(struct data));
    out->conv = 0;
    out->type = content->type;
    out->size = content->size;
    out->data = decode_text(content->data,content->size);


    return out;
}