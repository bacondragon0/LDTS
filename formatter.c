#include "main.h"

void convert_to_format(struct data* raw) {
    char **text = raw->data;
    
    for (size_t i = 0; i < raw->size; i++) {
        char* line = text[i];
        
        size_t n = 0;
        size_t oglen = strlen(line);

        for (size_t c = 0; c < oglen; c++) {
            for (size_t sp = 0; sp < special_chrs_num; sp++) { 
                if (special_chrs[sp] == line[c]) { n++; } 
            }
        }
        if (n == 0) { return; }

        char* nline = malloc(1 + oglen * sizeof(char) + sizeof(char) * n);
        
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

void convert_from_format(struct data* format) {
    char **text = format->data;

        for (size_t i = 0; i < format->size; i++) {
        char* line = text[i];
        
        size_t n = 0;
        size_t oglen = strlen(line);
        
        for (size_t c = 0; c < oglen-1; c++) {
            if (line[c] == '$') { n++; }
        }
        printf("n = %i\n",n);
        if (n == 0) { return; }
        printf("n non zero\n");
        char* nline = malloc((1024 + oglen - n) * sizeof(char));
        
        size_t l = 0;
        for (size_t j = 0; j < 1+oglen-n; j++) {
            if (line[j] == '$') {
                if (line[j+1] == '0') {
                    nline[l] = ' ';
                }
                else if (line[j+1] == '1') {
                    nline[l] = '.';
                }
                else if (line[j+1] == '2') {
                    nline[l] = ',';
                }
                else if (line[j+1] == '3') {
                    nline[l] = '?';
                }
                else if (line[j+1] == '4') {
                    nline[l] = '!';
                }
                j = j + 1;
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

