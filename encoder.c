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
    //printf("text: %s\n",text);
    char* bin = calloc(((strlen(text) + 2) * 6), sizeof(char));
    char* tmp;
    size_t spn = 0;

    size_t i = 0;
    while (i < strlen(text)) {
        char c = text[i];
        //printf("Char: %c\n",c);
        
        if (c == '$') {
            char* b = "111111";
            //printf("%s\n",b);
            strcat(bin,b);

            tmp = realloc(bin,((strlen(text) + 2) * 6) + 3 * sizeof(char) + spn * sizeof(char) * 3);
            bin = tmp;

            if (text[i+1] == '0') { strcat(bin,"000"); }
            else if (text[i+1] == '1') { strcat(bin,"001"); }
            else if (text[i+1] == '2') { strcat(bin,"011"); }
            else if (text[i+1] == '3') { strcat(bin,"010"); }
            else if (text[i+1] == '4') { strcat(bin,"100"); }
            i++;
            spn++;
        }
        else if ('A' <= c && c <= 'Z') {
            char* b = to_binary((int)c - 38);
            //printf("%s\n",b);
            strcat(bin,b);
            free(b);
        }
        else if ('a' <= c && c <= 'z') {
            char* b = to_binary((int)c - 96);
            //printf("%s\n",b);
            strcat(bin,b);
            free(b);
        }
        else if ('0' <= c && c <= '9') {
            char* b = to_binary((int)c + 5);
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