#include "column.h"

char* copier_chaine(const char* chaine) {
    int longueur = 0;
    while (chaine[longueur] != '\0') longueur++;
    char* copie = (char*)malloc(sizeof(char) * (longueur + 1));
    if (copie == NULL) {
        return NULL;
    }
    for (int i = 0; i <= longueur; i++) {
        copie[i] = chaine[i];
    }
    return copie;
}

COLUMN* create_column(const char* titre) {
    COLUMN* colonne = (COLUMN*)malloc(sizeof(COLUMN));
    if (colonne == NULL) {
        return NULL;
    }
    colonne->titre = copier_chaine(titre);
    if (colonne->titre == NULL) {
        free(colonne);
        return NULL;
    }
    colonne->taille_physique = 256;
    colonne->taille_logique = 0;
    colonne->donnees = (int*)malloc(colonne->taille_physique * sizeof(int));
    if (colonne->donnees == NULL) {
        free(colonne->titre);
        free(colonne);
        return NULL;
    }
    return colonne;
}

int insert_value(COLUMN* col, int valeur) {
    if (col->taille_logique == col->taille_physique) {
        int* nouvel_espace = realloc(col->donnees, (col->taille_physique + 256) * sizeof(int));
        if (nouvel_espace == NULL) {
            return 0;
        }
        col->donnees = nouvel_espace;
        col->taille_physique += 256;
    }
    col->donnees[col->taille_logique] = valeur;
    col->taille_logique++;
    return 1;
}

void delete_column(COLUMN** col) {
    if ((*col)->donnees != NULL) {
        free((*col)->donnees);
    }
    if ((*col)->titre != NULL) {
        free((*col)->titre);
    }
    free(*col);
    *col = NULL;
}

void print_col(COLUMN* col) {
    for (int i = 0; i < col->taille_logique; ++i) {
        printf("[%d] %d\n", i, col->donnees[i]);
    }
}

int count_value(COLUMN* col, int x) {
    int count = 0;
    for (int i = 0; i < col->taille_logique; i++) {
        if (col->donnees[i] == x) count++;
    }
    return count;
}

int value_at(COLUMN* col, int x) {
    if (x >= 0 && x < col->taille_logique) {
        return col->donnees[x];
    } else {
        printf("Index hors des limites\n");
        return -1;
    }
}

int count_greater(COLUMN* col, int x) {
    int count = 0;
    for (int i = 0; i < col->taille_logique; i++) {
        if (col->donnees[i] > x) count++;
    }
    return count;
}

int count_less(COLUMN* col, int x) {
    int count = 0;
    for (int i = 0; i < col->taille_logique; i++) {
        if (col->donnees[i] < x) count++;
    }
    return count;
}