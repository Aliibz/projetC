#include "cdataframe.h"


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
