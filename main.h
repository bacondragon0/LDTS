#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

enum types {
    TXT, IMG, AUD, VID
};

struct data {
    bool conv;
    enum types type;
    size_t size;
    char** data;
};

struct data* encode(struct data* raw);
struct data* decode(struct data* content);