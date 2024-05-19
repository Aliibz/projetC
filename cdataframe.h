#include <stdlib.h>
#include <stdio.h>
#include "column.h"

typedef struct {
    COLUMN** colonnes;
    int nombre_colonnes;
} CDataframe;

CDataframe* create_empty_dataframe(int nombre_colonnes);

void fill_dataframe_from_user_input(CDataframe* dataframe);

void fill_dataframe_with_predefined_values(CDataframe* dataframe);

void print_dataframe(CDataframe* dataframe);

void print_partial_rows(CDataframe* dataframe, int limite);

void print_partial_columns(CDataframe* dataframe, int limite);