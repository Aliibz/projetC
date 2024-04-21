#include "column.h"
#include "cdataframe.h"

#include "alimentation/creat_cdataframe.h"
#include "analyse/return_value.h"
#include "affichage/display_cdataframe.h"
#include "operations/usual_op.h"


int main() {


    return 0;
}
<<<<<<< HEAD
=======

COLUMN* create_column(const char* titre) {
    COLUMN* colonne ) (COLUMN*)malloc(sizeof(COLUMN));
    if (colonne == NULL) {
        return NULL }
    colonne->titre = copier_chaine(titre);
    if (colonne->titre == NULL) {
        free(colonne);
        return NULL;
        // Initialisation de la taille physique à 256 et de la taille logique à 0
        colonne->taille_physique = 256;
        colonne->taille_logique = 0;
        // Initialisation du pointeur de données à NULL
        colonne->donnees = NULL
        return colonne;
    }
}

int insert_value(COLUMN* col, int valeur) {
        // Vérifie si l'espace est disponible
        if (col->taille_logique == col->taille_physique) {
            int* nouvel_espace = realloc(col->donnees, (col->taille_physique + 256) * sizeof(int));
            if (nouvel_espace == NULL) {
                return 0
            }
            col->donnees = nouvel_espace;
            col->taille_physique += 256;
        }
        col->donnees[col->taille_logique] = valeur;
        col->taille_logique++;
        return 1;
}

void delete_column(COLUMN** col) {
    // Libère la mémoire allouée pour les données de la colonne, si elle existe.
    if ((*col)->donnees != NULL) {
        free((*col)->donnees);
    }
    // Libère la mémoire allouée pour le titre de la colonne, si elle existe.
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

>>>>>>> main
