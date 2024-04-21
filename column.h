#include <stdlib.h>
#include <stdio.h>

typedef struct {
    char* titre;
    int taille_physique;
    int taille_logique;
    int* donnees;
} COLUMN;

typedef struct {
    COLUMN** colonnes;
    int nombre_colonnes;
} CDataframe;

char* copier_chaine(const char* chaine);

COLUMN* create_column(const char* titre);

void delete_column(COLUMN** col);

int insert_value(COLUMN* col, int valeur);

void print_col(COLUMN* col);

int count_value(COLUMN* col, int x);

int value_at(COLUMN* col, int x);

int count_greater(COLUMN* col, int x);

int count_less(COLUMN* col, int x);