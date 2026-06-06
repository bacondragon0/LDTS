#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

enum types {
    TXT, IMG, AUD, VID
};

const static char special_chrs[] = {' ', ',', '.', '?', '!'};
const static size_t special_chrs_num = sizeof(special_chrs) / sizeof(char);

struct data {
    bool conv;
    enum types type;
    size_t size;
    char** data;
};

struct data* encode(struct data* raw);
struct data* decode(struct data* content);
void convert_to_format(struct data* raw);