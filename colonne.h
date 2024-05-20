/*
Nom du projet : Gestion de DataFrame en C
Auteurs : Ali Ibnou Zahir et Arthur Hacques
Rôle : Ce fichier contient les déclarations des fonctions pour gérer les colonnes d'un DataFrame.
*/

#ifndef COLONNE_H
#define COLONNE_H

#include <stdlib.h>
#include <stdio.h>

typedef enum {
    NULLVAL = 1,
    UINT,
    INT,
    CHAR,
    FLOAT,
    DOUBLE,
    STRING,
    STRUCTURE
} ENUM_TYPE;

typedef union {
    unsigned int uint_value;
    signed int int_value;
    char char_value;
    float float_value;
    double double_value;
    char* string_value;
    void* struct_value;
} COL_TYPE;

typedef struct {
    char* titre;
    unsigned int taille_logique;
    unsigned int taille_physique;
    ENUM_TYPE type_donnees;
    COL_TYPE* donnees;
    unsigned long long int* index;
    int valid_index;
    int direction_tri;
} COLONNE;

char* copier_chaine(const char* chaine);

COLONNE* creer_colonne(ENUM_TYPE type, const char* titre);

void supprimer_colonne(COLONNE** col);

int inserer_valeur(COLONNE* col, void* valeur);

void afficher_colonne(COLONNE* col);

int compter_valeur(COLONNE* col, COL_TYPE x);

COL_TYPE valeur_a(COLONNE* col, int x);

int compter_superieur(COLONNE* col, COL_TYPE x);

int compter_inferieur(COLONNE* col, COL_TYPE x);

void convertir_valeur(COLONNE* col, unsigned long long int i, char* str, int size);

void afficher_colonne_par_index(COLONNE* col);

void trier(COLONNE* col, int direction_tri);

void effacer_index(COLONNE* col);

int verifier_index(COLONNE* col);

void mettre_a_jour_index(COLONNE* col);

int rechercher_valeur_dans_colonne(COLONNE* col, void* val);

#endif // COLONNE_H
