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

struct data* read_file(char *filepath) {

    size_t lines = count_lines(filepath);

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

    struct data* out = malloc(sizeof(struct data));
    out->conv = false;
    out->type = TXT;
    out->size = lines;
    out->data = text_arr;

    return out;
}

void write_file(char *filepath, struct data* content) {
    FILE* file = fopen(filepath, "w");
    if (!file) { return; }

    for (size_t i = 0; i < content->size; i++) {
        fprintf(file,content->data[i]);
    }
    fclose(file);
}

void free_data(struct data* content) {
    for (size_t i = 0; i < content->size; i++) {
        if (content->data[i]) { free(content->data[i]); }
    }
    free(content->data);
    free(content);
}

void print_data(struct data* content) {

    static const char *type_string[] = {"Text", "Image", "Audio", "Video"};
    printf("\n----START----\n");
    printf("Converted: %i\n",content->conv);
    printf("Type: %s\n",type_string[content->type]);
    printf("Lines: %i\n",content->size); 
    printf("Data:\n");
    for (size_t i = 0; i < content->size; i++) {
        if (content->data[i]) { printf("%s",content->data[i]); }
    }
    printf("\n----END----\n");
}

int main() {

    char* input = "input/test.txt";
    char* output = "output/test.txt";

    struct data* f1 = read_file(input);
    
    struct data* encoded = encode(f1);
    //printf("Encoded main\n");
    print_data(f1);
    print_data(encoded);
    struct data* decoded = decode(encoded);
    print_data(decoded);
    //write_file(output,encoded);
    free_data(f1);
    free_data(encoded);
    free_data(decoded);

    return 0;
}