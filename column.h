#ifndef COLUMN_H
#define COLUMN_H

#include <stdlib.h>
#include <stdio.h>

typedef enum {
    NULLVAL = 1,
    UINT,
    INT,
    CHAR,
    FLOAT,
    DOUBLE,
    STRING,
    STRUCTURE
} ENUM_TYPE;

typedef union {
    unsigned int uint_value;
    signed int int_value;
    char char_value;
    float float_value;
    double double_value;
    char* string_value;
    void* struct_value;
} COL_TYPE;

typedef struct {
    char* titre;
    unsigned int taille_logique;
    unsigned int taille_physique;
    ENUM_TYPE type_donnees;
    COL_TYPE* donnees;
    unsigned long long int* index;
    int valid_index;
    int sort_dir;
} COLUMN;

char* copier_chaine(const char* chaine);

COLUMN* create_column(ENUM_TYPE type, const char* titre);

void delete_column(COLUMN** col);

int insert_value(COLUMN* col, void* valeur);

void print_col(COLUMN* col);

int count_value(COLUMN* col, COL_TYPE x);

COL_TYPE value_at(COLUMN* col, int x);

int count_greater(COLUMN* col, COL_TYPE x);

int count_less(COLUMN* col, COL_TYPE x);

void convert_value(COLUMN* col, unsigned long long int i, char* str, int size);

void print_col_by_index(COLUMN* col);

void sort(COLUMN* col, int sort_dir);

void erase_index(COLUMN* col);

int check_index(COLUMN* col);

void update_index(COLUMN* col);

int search_value_in_column(COLUMN* col, void* val);

#endif // COLUMN_H
