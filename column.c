#include "column.h"
#include <string.h>
#include <stdio.h>

// Copie une chaîne de caractères
char* copier_chaine(const char* chaine) {
    int longueur = 0;
    while (chaine[longueur] != '\0') longueur++; // Calcule la longueur de la chaîne
    char* copie = (char*)malloc(sizeof(char) * (longueur + 1)); // Alloue de la memoire pour la copie
    if (copie == NULL) {
        return NULL; // Verifie l'allocation de memoire
    }
    for (int i = 0; i <= longueur; i++) {
        copie[i] = chaine[i]; // Copie la chaîne
    }
    return copie;
}

// Cree une colonne avec un type et un titre specifies
COLUMN* create_column(ENUM_TYPE type, const char* titre) {
    COLUMN* colonne = (COLUMN*)malloc(sizeof(COLUMN)); // Alloue de la memoire pour la colonne
    if (colonne == NULL) {
        return NULL;
    }
    colonne->titre = copier_chaine(titre); // Copie le titre
    if (colonne->titre == NULL) {
        free(colonne); // Libère la memoire si l'allocation echoue
        return NULL;
    }
    colonne->taille_physique = 256; // Initialise la taille physique
    colonne->taille_logique = 0; // Initialise la taille logique
    colonne->type_donnees = type; // Initialise le type de donnees
    colonne->donnees = (COL_TYPE*)calloc(colonne->taille_physique, sizeof(COL_TYPE)); // Alloue de la memoire pour les donnees
    if (colonne->donnees == NULL) {
        free(colonne->titre);
        free(colonne);
        return NULL;
    }
    colonne->index = NULL; // Initialise l'index a NULL
    colonne->valid_index = 0; // Initialise la validite de l'index a 0
    colonne->sort_dir = 0; // Initialise la direction de tri a 0
    return colonne;
}

// Supprime une colonne
void delete_column(COLUMN** col) {
    if ((*col)->donnees != NULL) {
        free((*col)->donnees); // Libère la memoire des donnees
    }
    if ((*col)->titre != NULL) {
        free((*col)->titre); // Libère la memoire du titre
    }
    if ((*col)->index != NULL) {
        free((*col)->index); // Libère la memoire de l'index
    }
    free(*col); // Libère la memoire de la colonne
    *col = NULL; // Met le pointeur de la colonne a NULL
}

// Insère une valeur dans une colonne
int insert_value(COLUMN* col, void* valeur) {
    if (col->taille_logique == col->taille_physique) {
        COL_TYPE* nouvel_espace = realloc(col->donnees, (col->taille_physique + 256) * sizeof(COL_TYPE)); // Realloue de la memoire si necessaire
        if (nouvel_espace == NULL) {
            return 0; // Verifie l'allocation de memoire
        }
        col->donnees = nouvel_espace;
        col->taille_physique += 256; // Augmente la taille physique
    }
    switch (col->type_donnees) {
        case UINT:
            col->donnees[col->taille_logique].uint_value = *(unsigned int*)valeur;
            break;
        case INT:
            col->donnees[col->taille_logique].int_value = *(int*)valeur;
            break;
        case CHAR:
            col->donnees[col->taille_logique].char_value = *(char*)valeur;
            break;
        case FLOAT:
            col->donnees[col->taille_logique].float_value = *(float*)valeur;
            break;
        case DOUBLE:
            col->donnees[col->taille_logique].double_value = *(double*)valeur;
            break;
        case STRING:
            col->donnees[col->taille_logique].string_value = copier_chaine(*(char**)valeur);
            break;
        default:
            return 0;
    }
    col->taille_logique++;
    col->valid_index = 0; // Invalide l'index
    return 1;
}

// Affiche une colonne
void print_col(COLUMN* col) {
    for (int i = 0; i < col->taille_logique; ++i) {
        switch (col->type_donnees) {
            case UINT:
                printf("[%d] %u\n", i, col->donnees[i].uint_value);
                break;
            case INT:
                printf("[%d] %d\n", i, col->donnees[i].int_value);
                break;
            case CHAR:
                printf("[%d] %c\n", i, col->donnees[i].char_value);
                break;
            case FLOAT:
                printf("[%d] %f\n", i, col->donnees[i].float_value);
                break;
            case DOUBLE:
                printf("[%d] %lf\n", i, col->donnees[i].double_value);
                break;
            case STRING:
                printf("[%d] %s\n", i, col->donnees[i].string_value);
                break;
            case STRUCTURE:
                printf("[%d] %p\n", i, col->donnees[i].struct_value);
                break;
            default:
                printf("Type non supporte\n");
        }
    }
}

// Compte le nombre de fois qu'une valeur apparaît dans une colonne
int count_value(COLUMN* col, COL_TYPE x) {
    int count = 0;
    for (int i = 0; i < col->taille_logique; i++) {
        switch (col->type_donnees) {
            case UINT:
                if (col->donnees[i].uint_value == x.uint_value) count++;
                break;
            case INT:
                if (col->donnees[i].int_value == x.int_value) count++;
                break;
            case CHAR:
                if (col->donnees[i].char_value == x.char_value) count++;
                break;
            case FLOAT:
                if (col->donnees[i].float_value == x.float_value) count++;
                break;
            case DOUBLE:
                if (col->donnees[i].double_value == x.double_value) count++;
                break;
            case STRING:
                if (strcmp(col->donnees[i].string_value, x.string_value) == 0) count++;
                break;
            case STRUCTURE:
                if (col->donnees[i].struct_value == x.struct_value) count++;
                break;
            default:
                printf("Type non supporte\n");
        }
    }
    return count;
}

// Renvoie la valeur a un index donne
COL_TYPE value_at(COLUMN* col, int x) {
    if (x >= 0 && x < col->taille_logique) {
        return col->donnees[x];
    } else {
        printf("Index hors des limites\n");
        COL_TYPE null_value;
        null_value.uint_value = 0;
        return null_value;
    }
}

// Compte le nombre de valeurs superieures a une valeur donnee
int count_greater(COLUMN* col, COL_TYPE x) {
    int count = 0;
    for (int i = 0; i < col->taille_logique; i++) {
        switch (col->type_donnees) {
            case UINT:
                if (col->donnees[i].uint_value > x.uint_value) count++;
                break;
            case INT:
                if (col->donnees[i].int_value > x.int_value) count++;
                break;
            case CHAR:
                if (col->donnees[i].char_value > x.char_value) count++;
                break;
            case FLOAT:
                if (col->donnees[i].float_value > x.float_value) count++;
                break;
            case DOUBLE:
                if (col->donnees[i].double_value > x.double_value) count++;
                break;
            default:
                printf("Type non supporte\n");
        }
    }
    return count;
}

// Compte le nombre de valeurs inferieures a une valeur donnee
int count_less(COLUMN* col, COL_TYPE x) {
    int count = 0;
    for (int i = 0; i < col->taille_logique; i++) {
        switch (col->type_donnees) {
            case UINT:
                if (col->donnees[i].uint_value < x.uint_value) count++;
                break;
            case INT:
                if (col->donnees[i].int_value < x.int_value) count++;
                break;
            case CHAR:
                if (col->donnees[i].char_value < x.char_value) count++;
                break;
            case FLOAT:
                if (col->donnees[i].float_value < x.float_value) count++;
                break;
            case DOUBLE:
                if (col->donnees[i].double_value < x.double_value) count++;
                break;
            default:
                printf("Type non supporte\n");
        }
    }
    return count;
}

// Convertit une valeur en chaîne de caractères
void convert_value(COLUMN* col, unsigned long long int i, char* str, int size) {
    switch (col->type_donnees) {
        case UINT:
            snprintf(str, size, "%u", col->donnees[i].uint_value);
            break;
        case INT:
            snprintf(str, size, "%d", col->donnees[i].int_value);
            break;
        case CHAR:
            snprintf(str, size, "%c", col->donnees[i].char_value);
            break;
        case FLOAT:
            snprintf(str, size, "%f", col->donnees[i].float_value);
            break;
        case DOUBLE:
            snprintf(str, size, "%lf", col->donnees[i].double_value);
            break;
        case STRING:
            snprintf(str, size, "%s", col->donnees[i].string_value);
            break;
        case STRUCTURE:
            snprintf(str, size, "%p", col->donnees[i].struct_value);
            break;
        default:
            snprintf(str, size, "Type non supporte");
    }
}

// Affiche une colonne en utilisant l'index
void print_col_by_index(COLUMN* col) {
    if (col->valid_index == 0) {
        printf("Index non valide.\n");
        return;
    }
    for (int i = 0; i < col->taille_logique; ++i) {
        unsigned long long int idx = col->index[i];
        char buffer[100];
        convert_value(col, idx, buffer, 100);
        printf("[%llu] %s\n", idx, buffer);
    }
}

// Trie une colonne
void sort(COLUMN* col, int sort_dir) {
    // Implementez le tri rapide ou le tri par insertion en fonction de la valeur de valid_index
    // Mettez a jour valid_index et sort_dir en consequence
}

// Efface l'index d'une colonne
void erase_index(COLUMN* col) {
    if (col->index != NULL) {
        free(col->index);
        col->index = NULL;
    }
    col->valid_index = 0;
}

// Verifie la validite de l'index d'une colonne
int check_index(COLUMN* col) {
    return col->valid_index;
}

// Met a jour l'index d'une colonne
void update_index(COLUMN* col) {
    if (col->index != NULL) {
        free(col->index);
    }
    col->index = (unsigned long long int*)malloc(col->taille_logique * sizeof(unsigned long long int));
    for (unsigned int i = 0; i < col->taille_logique; i++) {
        col->index[i] = i;
    }
    col->valid_index = 1;
}

// Recherche une valeur dans une colonne trie
int search_value_in_column(COLUMN* col, void* val) {
    if (col->valid_index != 1) {
        return -1;
    }
    int left = 0;
    int right = col->taille_logique - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        COL_TYPE mid_val = col->donnees[col->index[mid]];
        if (col->type_donnees == INT) {
            int target = *(int*)val;
            if (mid_val.int_value == target) {
                return 1;
            } else if (mid_val.int_value < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    return 0;
}
