#include "creat_cdataframe.h"

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

// Fonction pour créer une colonne
COLUMN* create_column(const char* titre) {
    COLUMN* colonne = (COLUMN*)malloc(sizeof(COLUMN));
    if (colonne == NULL) {
        return NULL; }
    colonne->titre = copier_chaine(titre);
    if (colonne->titre == NULL) {
        free(colonne);
        return NULL;
        // Initialisation de la taille physique à 256 et de la taille logique à 0
        colonne->taille_physique = 256;
        colonne->taille_logique = 0;
        // Initialisation du pointeur de données à NULL
        colonne->donnees = NULL;
        return colonne;
    }
}

// Fonction pour insérer une valeur
int insert_value(COLUMN* col, int valeur) {
    // Vérifie si l'espace est disponible
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

// Fonction pour supprimer une colonne
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

// Fonction pour afficher une colonne
void print_col(COLUMN* col) {
    for (int i = 0; i < col->taille_logique; ++i) {
        printf("[%d] %d\n", i, col->donnees[i]);
    }
}

// Fonction pour créer un CDataframe vide
CDataframe* create_empty_dataframe(int nombre_colonnes) {
    CDataframe* dataframe = (CDataframe*)malloc(sizeof(CDataframe));
    if (dataframe == NULL) {
        return NULL;
    }
    dataframe->nombre_colonnes = nombre_colonnes;
    dataframe->colonnes = (COLUMN**)malloc(nombre_colonnes * sizeof(COLUMN*));
    if (dataframe->colonnes == NULL) {
        free(dataframe);
        return NULL;
    }
    // Initialisation de chaque colonne avec un titre par défaut
    for (int i = 0; i < nombre_colonnes; i++) {
        char titre_default[20]; // Titre par défaut de longueur maximale de 20 caractères
        sprintf(titre_default, "Colonne%d", i);
        dataframe->colonnes[i] = create_column(titre_default);
        if (dataframe->colonnes[i] == NULL) {
            // En cas d'échec, libérer les colonnes précédemment allouées
            for (int j = 0; j < i; j++) {
                delete_column(&(dataframe->colonnes[j]));
            }
            free(dataframe->colonnes);
            free(dataframe);
            return NULL;
        }
    }
    return dataframe;
}

// Fonction pour remplir un CDataframe à partir de saisies utilisateur
void fill_dataframe_from_user_input(CDataframe* dataframe) {
    for (int i = 0; i < dataframe->nombre_colonnes; i++) {
        printf("Saisir les données pour la colonne %s :\n", dataframe->colonnes[i]->titre);
        for (int j = 0; j < dataframe->colonnes[i]->taille_physique; j++) {
            int valeur;
            printf("Saisir la valeur %d : ", j + 1);
            scanf("%d", &valeur);
            insert_value(dataframe->colonnes[i], valeur);
        }
    }
}
