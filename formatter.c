#include "main.h"

void convert_to_format(struct data* raw) {
    char **text = raw->data;
    
    for (size_t i = 0; i < raw->size; i++) {
        char* line = text[i];

        size_t n = 0;
        size_t oglen = strlen(line);
        for (size_t c = 0; c < oglen; c++) {
            if (line[c] == ' ' || line[c] == '.' || line[c] == ',' || line[c] == '?') { n++; }
        }
        if (n == 0) { return; }

        char* nline = malloc(2 + oglen * sizeof(char) + sizeof(char) * n);
        
        size_t l = 0;
        for (size_t j = 0; j < oglen; j++) {
            if (line[j] == ' ') {
                nline[l] = '$';
                nline[l+1] = '0';
                l++;
            }
            else if (line[j] == '.') {
                nline[l] = '$';
                nline[l+1] = '1';
                l++;
            }
            else if (line[j] == ',') {
                nline[l] = '$';
                nline[l+1] = '2';
                l++;
            }
            else if (line[j] == '?') {
                nline[l] = '$';
                nline[l+1] = '3';
                l++;
            }
            else if (line[j] == '!') {
                nline[l] = '$';
                nline[l+1] = '4';
                l++;
            }
            else {
                nline[l] = line[j];
            }
            l++;
        }
        nline[l] = '\0';

        //printf("nline: %s\n",nline);
        strcpy(text[i], nline);
        free(nline);
    }
}

char** convert_from_format(struct data format) {
    return NULL;
}

