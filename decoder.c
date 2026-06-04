#include "main.h"


int to_int(char* binary) {
    if (strcmp(binary,"000000") == 0) { return 0; }
    if (strcmp(binary,"111111") == 0) { return 64; }
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
    if (ascii == 0) { return (char)10; }
    if (ascii == 64) { return ' '; }
    if (1 <= ascii <= 26) { ascii = ascii + 96; printf("\n ascii = %i\n",ascii); }



    return (char)ascii;
}

char* get_str(char* binary, size_t index) {
    char* out = malloc(sizeof(char) * 6 + 1);
    //printf("binary string: %s\n",binary);
    for (size_t i = 0; i < 6; i++) {
        out[i] = binary[(index * 6) + i];
    }

    out[6] = '\0';
    //printf("%s\n",out);
    return out;
}

char** decode_text(char** text, size_t lines) {
    
    char** str_arr = malloc(sizeof(char*) * lines);

    size_t llen = 0;
    char* str = get_str(text[llen],llen);
    for (size_t i = 0; i < lines; i++) {
        while (strcmp("000000",str) != 0) {
            llen++;
            str = get_str(text[i],llen);
        }
        //printf("llen : %i\n",llen);
        
        char* line = calloc(llen + 2, sizeof(char));
        
        for (size_t k = 0; k < llen; k++) {
            char* ch = get_str(text[i],k);
            line[k] = reader(ch);
        }

        if (i < lines-1) { 
            line[llen] = '\n';
            line[llen+1] = '\0';
        }
        else { line[llen] = '\0'; }
        str_arr[i] = line;
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