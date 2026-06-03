#include "main.h"

void reverse(char *bin, int left, int right) {
    while (left < right) {
        char temp = bin[left];
        bin[left] = bin[right];
        bin[right] = temp;
        left++;
        right--;
    }
}

char* to_binary(int c) {
    char* out = calloc(6, sizeof(char));
    int res;
    int i = 0;

    while (c > 0) {
        int bit = c % 2;
        out[i++] = '0' + bit;
        c /= 2;
    }
    out[i] = '\0';

    reverse(out, 0, i-1);
  	return out;
}

char* parser(char* text) {

    char* bin = calloc(strlen(text) * 6, sizeof(char));
    
    size_t i = 0;
    while (i < strlen(text)) {
        char c = text[i];

        if ('a' <= c <= 'z' || 'A' <= c <= 'Z') {
            char* b = to_binary((int)c % 26);
            strcat(bin,b);
            free(b);
        }
        else if (c == ' ') {
            char* b = "111111";
            strcat(bin,b);
            free(b);
        }
        i++;
    }
    strcat(bin,"000000");
    
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