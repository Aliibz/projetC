#ifndef CDATAFRAME_H
#define CDATAFRAME_H

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

void add_row(CDataframe* dataframe, COL_TYPE* values);

void remove_row(CDataframe* dataframe, int index);

void add_column(CDataframe* dataframe, ENUM_TYPE type, const char* titre);

void remove_column(CDataframe* dataframe, int index);

void rename_column(CDataframe* dataframe, int index, const char* new_title);

int value_exists(CDataframe* dataframe, COL_TYPE value);

COL_TYPE get_cell_value(CDataframe* dataframe, int row, int col);

void set_cell_value(CDataframe* dataframe, int row, int col, COL_TYPE value);

void print_column_names(CDataframe* dataframe);

void print_row_count(CDataframe* dataframe);

void print_col_count(CDataframe* dataframe);

void count_cells_equal_to_x(CDataframe* dataframe, COL_TYPE x);

void count_cells_greater_than_x(CDataframe* dataframe, COL_TYPE x);

void count_cells_less_than_x(CDataframe* dataframe, COL_TYPE x);

#endif // CDATAFRAME_H
