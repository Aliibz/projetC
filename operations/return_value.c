#include "return_value.h"
#include "creat_cdataframe.c"

// Retourne le nombre d'occurrences d'une valeur x dans la colonne
int count_value(COLUMN* col, int x) {
    int count = 0;
    for (int i = 0; i < col->taille_logique; i++) {
        if (col->donnees[i] == x) count++;
    }
    return count;
}

// Retourne la valeur à la position x dans la colonne
int value_at(COLUMN* col, int x) {
    if (x >= 0 && x < col->taille_logique) {
        return col->donnees[x];
    } else {
        printf("Index hors des limites\n");
        return -1;
    }
}

// Retourne le nombre de valeurs supérieures à x dans la colonne
int count_greater(COLUMN* col, int x) {
    int count = 0;
    for (int i = 0; i < col->taille_logique; i++) {
        if (col->donnees[i] > x) count++;
    }
    return count;
}

// Retourne le nombre de valeurs inférieures à x dans la colonne
int count_less(COLUMN* col, int x) {
    int count = 0;
    for (int i = 0; i < col->taille_logique; i++) {
        if (col->donnees[i] < x) count++;
    }
    return count;
}
