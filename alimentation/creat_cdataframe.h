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

void print_col(COLUMN* col);