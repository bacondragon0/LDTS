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
    if (ascii == 0) { return (char)10; }
    else if (ascii == 63) { return ' '; }
    else if (1 <= ascii && ascii <= 26) { ascii = ascii + 96; }
    else if (27 <= ascii && ascii <= 52) { ascii = ascii + 38; }
    else if (53 <= ascii && ascii <= 62) { ascii = ascii - 5; }


    return (char)ascii;
}

char* get_str(char* binary, size_t index) {
    char* out = malloc(sizeof(char) * 6 + 1);
    //printf("binary string: %s\n",binary);
    for (size_t i = 0; i < 6; i++) {
        //printf("index: %i | binary: %c\n",index,binary[(index * 6) + i]);
        out[i] = binary[(index * 6) + i];
    }

    out[6] = '\0';
    //printf("out: %s\n",out);
    return out;
}

char** decode_text(char** text, size_t lines) {
    
    char** str_arr = malloc(sizeof(char*) * lines);

    size_t llen = 0;
    int cmp = 0;
    for (size_t i = 0; i < lines; i++) {
        char* str = get_str(text[0],llen);
        cmp = strcmp("000000",str);
        free(str);
        while (cmp != 0) {
            llen++;
            str = get_str(text[i],llen);
            cmp = strcmp("000000",str);
            //printf("CMP: %i\n",cmp);
            free(str);
        }
        
        //printf("llen : %i\n",llen);
        
        char* line = calloc(llen + 2, sizeof(char));
        
        for (size_t k = 0; k < llen; k++) {
            char* ch = get_str(text[i],k);
            line[k] = reader(ch);
            free(ch);
        }

        if (i < lines-1) { 
            line[llen] = '\n';
            line[llen+1] = '\0';
        }
        else { line[llen] = '\0'; }
        str_arr[i] = line;
        llen = 0;
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