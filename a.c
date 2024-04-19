#include <stdlib.h>

typedef struct {
    char* titre;
    int taille_physique;
    int taille_logique;
    int* donnees;
} COLUMN;

// Fonction pour copier une chaîne de caractères
char* copier_chaine(const char* chaine) {
    int longueur = 0;
    while (chaine[longueur] != '\0') longueur++;
    char* copie = (char*)malloc(sizeof(char) * (longueur + 1));
    if (copie == NULL) {
        return NULL; // Échec de l'allocation
    }

    for (int i = 0; i <= longueur; i++) {
        copie[i] = chaine[i];
    }

    return copie;
}

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
