#include "main.h"

size_t count_lines(char *filepath) {
    FILE* file = fopen(filepath, "r");
    char* line = malloc(sizeof(char) * 256);
    size_t i = 0;
    while (fgets(line, sizeof(line), file)) {
        i++;
    }

    fclose(file);
    free(line);
    return i;
}

char** read_file(char *filepath, size_t lines) {
    FILE* file = fopen(filepath, "r");
    if (!file) { return NULL; }

    char* line = malloc(sizeof(char) * 256);

    char** text_arr = malloc(sizeof(char*) * lines);
    for (size_t l = 0; l < lines; l++) {
        text_arr[l] = malloc(sizeof(char) * 256);
    }
    size_t i = 0;

    while (fgets(line, sizeof(line), file)) {
        strcpy(text_arr[i],line);
        i++;
    }
    
    fclose(file);
    free(line);
    return text_arr;
}

void write_file(char *filepath, char** text, size_t lines) {
    FILE* file = fopen(filepath, "w");
    if (!file) { return; }

    for (size_t i = 0; i < lines; i++) {
        fprintf(file,text[i]);
    }
    fclose(file);
}

void free_text(char** text, size_t lines) {
    for (size_t i = 0; i < lines; i++) {
        free(text[i]);
    }
    free(text);
}

void print_text(char** text, size_t lines) {
    for (size_t i = 0; i < lines; i++) {
        printf("%s\n",text[i]);
    }
}

int main() {

    char* input = "input/test.txt";
    char* output = "output/test.txt";
    size_t lines = count_lines(input);
    
    char** text = read_file(input,lines);
    char** encoded = encode_text(text,lines);
    //print_text(text,lines);
    printf("Encoded main\n");
    print_text(encoded,lines);
    write_file(output,encoded,lines);
    free_text(text,lines);
    free_text(encoded,lines);

    return 0;
}