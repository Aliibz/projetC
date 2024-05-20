/*
Nom du projet : Gestion de DataFrame en C
Auteurs : Ali Ibnou Zahir et Arthur Hacques
Rôle : Ce fichier contient les fonctions pour gerer les colonnes d'un DataFrame.
*/

#include "colonne.h"
#include <string.h>
#include <stdio.h>

/* Copie une chaîne de caracteres */
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

/* Cree une colonne avec un type de donnees specifique et un titre */
COLONNE* creer_colonne(ENUM_TYPE type, const char* titre) {
    COLONNE* colonne = (COLONNE*)malloc(sizeof(COLONNE));
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
    colonne->type_donnees = type;
    colonne->donnees = (COL_TYPE*)calloc(colonne->taille_physique, sizeof(COL_TYPE));
    if (colonne->donnees == NULL) {
        free(colonne->titre);
        free(colonne);
        return NULL;
    }
    colonne->index = NULL;
    colonne->valid_index = 0;
    colonne->direction_tri = 0;
    return colonne;
}

/* Supprime une colonne et libere la memoire associee */
void supprimer_colonne(COLONNE** col) {
    if ((*col)->donnees != NULL) {
        free((*col)->donnees);
    }
    if ((*col)->titre != NULL) {
        free((*col)->titre);
    }
    if ((*col)->index != NULL) {
        free((*col)->index);
    }
    free(*col);
    *col = NULL;
}

/* Insere une valeur dans une colonne */
int inserer_valeur(COLONNE* col, void* valeur) {
    if (col->taille_logique == col->taille_physique) {
        COL_TYPE* nouvel_espace = realloc(col->donnees, (col->taille_physique + 256) * sizeof(COL_TYPE));
        if (nouvel_espace == NULL) {
            return 0;
        }
        col->donnees = nouvel_espace;
        col->taille_physique += 256;
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
    col->valid_index = 0;
    return 1;
}

/* Affiche le contenu d'une colonne */
void afficher_colonne(COLONNE* col) {
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

/* Compte le nombre de fois qu'une valeur apparaît dans une colonne */
int compter_valeur(COLONNE* col, COL_TYPE x) {
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

/* Compte le nombre de valeurs superieures a une valeur donnee dans une colonne */
int compter_superieur(COLONNE* col, COL_TYPE x) {
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

/* Compte le nombre de valeurs inferieures a une valeur donnee dans une colonne */
int compter_inferieur(COLONNE* col, COL_TYPE x) {
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

/* Convertit une valeur a un format de chaîne de caracteres */
void convertir_valeur(COLONNE* col, unsigned long long int i, char* str, int size) {
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

/* Affiche une colonne en utilisant l'index */
void afficher_colonne_par_index(COLONNE* col) {
    if (col->valid_index == 0) {
        printf("Index non valide.\n");
        return;
    }
    for (int i = 0; i < col->taille_logique; ++i) {
        unsigned long long int idx = col->index[i];
        char buffer[100];
        convertir_valeur(col, idx, buffer, 100);
        printf("[%llu] %s\n", idx, buffer);
    }
}

/* Trie une colonne dans un ordre specifique */
void trier(COLONNE* col, int direction_tri) {
    if (col->taille_logique <= 1) {
        return;
    }

    for (int i = 0; i < col->taille_logique - 1; i++) {
        for (int j = 0; j < col->taille_logique - i - 1; j++) {
            int should_swap = 0;
            switch (col->type_donnees) {
                case UINT:
                    should_swap = (direction_tri == 0) ?
                        (col->donnees[j].uint_value > col->donnees[j + 1].uint_value) :
                        (col->donnees[j].uint_value < col->donnees[j + 1].uint_value);
                    break;
                case INT:
                    should_swap = (direction_tri == 0) ?
                        (col->donnees[j].int_value > col->donnees[j + 1].int_value) :
                        (col->donnees[j].int_value < col->donnees[j + 1].int_value);
                    break;
                case FLOAT:
                    should_swap = (direction_tri == 0) ?
                        (col->donnees[j].float_value > col->donnees[j + 1].float_value) :
                        (col->donnees[j].float_value < col->donnees[j + 1].float_value);
                    break;
                case DOUBLE:
                    should_swap = (direction_tri == 0) ?
                        (col->donnees[j].double_value > col->donnees[j + 1].double_value) :
                        (col->donnees[j].double_value < col->donnees[j + 1].double_value);
                    break;
                case CHAR:
                    should_swap = (direction_tri == 0) ?
                        (col->donnees[j].char_value > col->donnees[j + 1].char_value) :
                        (col->donnees[j].char_value < col->donnees[j + 1].char_value);
                    break;
                case STRING:
                    should_swap = (direction_tri == 0) ?
                        (strcmp(col->donnees[j].string_value, col->donnees[j + 1].string_value) > 0) :
                        (strcmp(col->donnees[j].string_value, col->donnees[j + 1].string_value) < 0);
                    break;
                default:
                    printf("Type non supporte pour le tri\n");
                    return;
            }
            if (should_swap) {
                COL_TYPE temp = col->donnees[j];
                col->donnees[j] = col->donnees[j + 1];
                col->donnees[j + 1] = temp;
            }
        }
    }
    mettre_a_jour_index(col);
}

/* Efface l'index d'une colonne */
void effacer_index(COLONNE* col) {
    if (col->index != NULL) {
        free(col->index);
        col->index = NULL;
    }
    col->valid_index = 0;
}

/* Verifie la validite de l'index d'une colonne */
int verifier_index(COLONNE* col) {
    return col->valid_index;
}

/* Met a jour l'index d'une colonne */
void mettre_a_jour_index(COLONNE* col) {
    if (col->index != NULL) {
        free(col->index);
    }
    col->index = (unsigned long long int*)malloc(col->taille_logique * sizeof(unsigned long long int));
    for (unsigned int i = 0; i < col->taille_logique; i++) {
        col->index[i] = i;
    }
    col->valid_index = 1;
}

/* Recherche une valeur specifique dans une colonne */
int rechercher_valeur_dans_colonne(COLONNE* col, void* val) {
    if (col->valid_index != 1) {
        return -1;
    }
    int gauche = 0;
    int droite = col->taille_logique - 1;
    while (gauche <= droite) {
        int milieu = gauche + (droite - gauche) / 2;
        COL_TYPE mid_val = col->donnees[col->index[milieu]];
        if (col->type_donnees == INT) {
            int cible = *(int*)val;
            if (mid_val.int_value == cible) {
                return 1;
            } else if (mid_val.int_value < cible) {
                gauche = milieu + 1;
            } else {
                droite = milieu - 1;
            }
        }
    }
    return 0;
}
