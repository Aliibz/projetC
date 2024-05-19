#ifndef CDATAFRAME_H
#define CDATAFRAME_H

#include "column.h"

CDataframe* create_empty_dataframe(int nombre_colonnes);
void fill_dataframe_from_user_input(CDataframe* dataframe);
void fill_dataframe_with_predefined_values(CDataframe* dataframe);
void print_dataframe(CDataframe* dataframe);
void print_partial_rows(CDataframe* dataframe, int limite);
void print_partial_columns(CDataframe* dataframe, int limite);

#endif // CDATAFRAME_H