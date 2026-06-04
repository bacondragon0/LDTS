#include "main.h"

char* to_binary(int c) {
    char* out = malloc(7 * sizeof(char));
    int exp = 5;

    while(exp >= 0) {
        if (c >= pow(2,exp)) {
            c = c - pow(2,exp);
            out[5 - exp] = '1'; 
        }
        else {
            out[5 - exp] = '0';
        }
        exp--;
    }
    out[6] = '\0';
    return out;
}

char* parser(char* text) {
    //printf("strlen : %i\n",strlen(text));
    char* bin = calloc(((strlen(text) + 2) * 6), sizeof(char));
    
    size_t i = 0;
    while (i < strlen(text)) {
        char c = text[i];
        if (c == ' ') {
            char* b = "111111";
            //printf("%s\n",b);
            strcat(bin,b);
        }
        else if ('a' <= c <= 'z') {
            char* b = to_binary((int)c - 96);
            //printf("%s\n",b);
            strcat(bin,b);
            free(b);
        }
        i++;
    }
    //printf("bin str: %s\n",bin);
    strcat(bin,"000000");
    //printf("bin str post: %s\n",bin);
    return bin;
}

char** encode_text(char** text, size_t lines) {

    char** bin_arr = malloc(sizeof(char*) * lines);

    for (size_t i = 0; i < lines; i++) {
        bin_arr[i] = parser(text[i]);
        //printf("%s\n",bin_arr[i]);
    }

    return bin_arr;
}

struct data* encode(struct data* raw) {
    if (raw->size == 0) { printf("No data to encode.\n"); return NULL; }
    if (raw->conv == true) {
        printf("Data already encoded.\n");
        return NULL;
    }

    char** res_bin = encode_text(raw->data,raw->size);

    struct data* res = malloc(sizeof(struct data));

    res->conv = true;
    res->type = raw->type;
    res->size = raw->size;
    res->data = res_bin;

    return res;
}