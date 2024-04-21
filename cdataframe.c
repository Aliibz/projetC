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


// Fonction pour remplir un CDataframe en dur
void fill_dataframe_with_predefined_values(CDataframe* dataframe) {
    // Choisisez ici les valeurs prédéfinies pour chaque colonne du CDataframe,exemple : valeurs de 1 à 10 dans chaque colonne
    for (int i = 0; i < dataframe->nombre_colonnes; i++) {
        for (int j = 1; j <= 10; j++) {
            insert_value(dataframe->colonnes[i], j);
        }
    }
}


//Afficher tout le CDataframe
void print_dataframe(CDataframe* dataframe) {
    for (int i = 0; i < dataframe->nombre_colonnes; i++) {
        printf("Colonne %s :\n", dataframe->colonnes[i]->titre);
        print_col(dataframe->colonnes[i]);
        printf("\n");
    }
}


//Afficher une partie des lignes du CDataframe selon une limite fournie par l’utilisateur
void print_partial_rows(CDataframe* dataframe, int limite) {
    for (int i = 0; i < dataframe->nombre_colonnes; i++) {
        printf("Colonne %s :\n", dataframe->colonnes[i]->titre);
        for (int j = 0; j < limite && j < dataframe->colonnes[i]->taille_logique; j++) {
            printf("[%d] %d\n", j, dataframe->colonnes[i]->donnees[j]);
        }
        printf("\n");
    }
}


//Afficher une partie des colonnes du CDataframe selon une limite fournie par l’utilisateur
void print_partial_columns(CDataframe* dataframe, int limite) {
    for (int i = 0; i < limite && i < dataframe->nombre_colonnes; i++) {
        printf("Colonne %s :\n", dataframe->colonnes[i]->titre);
        print_col(dataframe->colonnes[i]);
        printf("\n");
    }
}

/*
void add_row(CDataframe* dataframe, int* values) {
    for (int i = 0; i < dataframe->nombre_colonnes; i++) {
        insert_value(dataframe->colonnes[i], values[i]);
    }
}


void remove_row(CDataframe* dataframe, int index) {
    for (int i = 0; i < dataframe->nombre_colonnes; i++) {
        if (index >= 0 && index < dataframe->colonnes[i]->taille_logique) {
            // Déplacer les valeurs vers le haut pour remplacer la ligne supprimée
            for (int j = index; j < dataframe->colonnes[i]->taille_logique - 1; j++) {
                dataframe->colonnes[i]->donnees[j] = dataframe->colonnes[i]->donnees[j + 1];
            }
            // Réduire la taille logique de la colonne
            dataframe->colonnes[i]->taille_logique--;
        }
    }
}


void add_column(CDataframe* dataframe, const char* titre) {
    // Créer une nouvelle colonne avec le titre spécifié
    COLUMN* new_column = create_column(titre);
    if (new_column != NULL) {
        // Allouer de la mémoire pour stocker un pointeur de colonne supplémentaire
        dataframe->colonnes = realloc(dataframe->colonnes, (dataframe->nombre_colonnes + 1) * sizeof(COLUMN*));
        if (dataframe->colonnes != NULL) {
            // Ajouter la nouvelle colonne à la fin du CDataframe
            dataframe->colonnes[dataframe->nombre_colonnes] = new_column;
            dataframe->nombre_colonnes++;
        } else {
            // En cas d'échec de réallocation, libérer la mémoire allouée pour la nouvelle colonne
            delete_column(&new_column);
        }
    }
}


void remove_column(CDataframe* dataframe, int index) {
    if (index >= 0 && index < dataframe->nombre_colonnes) {
        // Libérer la mémoire allouée pour la colonne à l'index spécifié
        delete_column(&(dataframe->colonnes[index]));
        // Déplacer les pointeurs des colonnes suivantes pour remplir le vide
        for (int i = index; i < dataframe->nombre_colonnes - 1; i++) {
            dataframe->colonnes[i] = dataframe->colonnes[i + 1];
        }
        // Réduire le nombre total de colonnes
        dataframe->nombre_colonnes--;
        // Réallouer la mémoire pour le tableau de pointeurs de colonnes
        dataframe->colonnes = realloc(dataframe->colonnes, dataframe->nombre_colonnes * sizeof(COLUMN*));
    }
}


void rename_column(CDataframe* dataframe, int index, const char* new_title) {
    if (index >= 0 && index < dataframe->nombre_colonnes) {
        // Libérer l'ancien titre de la colonne
        free(dataframe->colonnes[index]->titre);
        // Copier le nouveau titre
        dataframe->colonnes[index]->titre = copier_chaine(new_title);
    }
}


int value_exists(CDataframe* dataframe, int value) {
    for (int i = 0; i < dataframe->nombre_colonnes; i++) {
        if (count_value(dataframe->colonnes[i], value) > 0) {
            return 1; // La valeur existe dans au moins une colonne
        }
    }
    return 0; // La valeur n'existe pas dans le CDataframe
}


int get_cell_value(CDataframe* dataframe, int row, int col) {
    if (row >= 0 && row < dataframe->colonnes[0]->taille_logique && col >= 0 && col < dataframe->nombre_colonnes) {
        return dataframe->colonnes[col]->donnees[row];
    }
    return -1; // Retourne une valeur par défaut si les indices sont invalides
}

void set_cell_value(CDataframe* dataframe, int row, int col, int value) {
    if (row >= 0 && row < dataframe->colonnes[0]->taille_logique && col >= 0 && col < dataframe->nombre_colonnes) {
        dataframe->colonnes[col]->donnees[row] = value;
    }
}


void print_column_names(CDataframe* dataframe) {
    printf("Noms des colonnes :\n");
    for (int i = 0; i < dataframe->nombre_colonnes; i++) {
        printf("%s\n", dataframe->colonnes[i]->titre);
    }
}