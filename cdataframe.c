#include "cdataframe.h"

// Cree un dataframe vide avec un nombre specifie de colonnes
CDataframe* create_empty_dataframe(int nombre_colonnes) {
    CDataframe* dataframe = (CDataframe*)malloc(sizeof(CDataframe)); // Alloue de la memoire pour le dataframe
    if (dataframe == NULL) {
        return NULL; // Verifie l'allocation de memoire
    }
    dataframe->nombre_colonnes = nombre_colonnes; // Initialise le nombre de colonnes
    dataframe->colonnes = (COLUMN**)calloc(nombre_colonnes, sizeof(COLUMN*)); // Alloue de la memoire pour les colonnes
    if (dataframe->colonnes == NULL) {
        free(dataframe); // Libère la memoire allouee si l'allocation des colonnes echoue
        return NULL;
    }
    for (int i = 0; i < nombre_colonnes; i++) {
        char titre_default[20];
        sprintf(titre_default, "Colonne%d", i); // Cree un titre par defaut pour chaque colonne
        dataframe->colonnes[i] = create_column(INT, titre_default); // Cree chaque colonne avec un type par defaut
        if (dataframe->colonnes[i] == NULL) {
            for (int j = 0; j < i; j++) {
                delete_column(&(dataframe->colonnes[j])); // Supprime les colonnes creees en cas d'echec
            }
            free(dataframe->colonnes);
            free(dataframe);
            return NULL;
        }
    }
    return dataframe;
}

// Remplit le dataframe avec des saisies utilisateur
void fill_dataframe_from_user_input(CDataframe* dataframe) {
    for (int i = 0; i < dataframe->nombre_colonnes; i++) {
        printf("Saisir les donnees pour la colonne %s :\n", dataframe->colonnes[i]->titre);
        for (int j = 0; j < 10; j++) {
            COL_TYPE valeur;
            switch (dataframe->colonnes[i]->type_donnees) {
                case INT:
                    printf("Saisir la valeur (entier) %d : ", j + 1);
                    if (scanf("%d", &valeur.int_value) != 1) {
                        printf("Erreur de saisie. Veuillez entrer un entier.\n");
                        return;
                    }
                    break;
                case FLOAT:
                    printf("Saisir la valeur (flottant) %d : ", j + 1);
                    if (scanf("%f", &valeur.float_value) != 1) {
                        printf("Erreur de saisie. Veuillez entrer un flottant.\n");
                        return;
                    }
                    break;
                case CHAR:
                    printf("Saisir la valeur (caractère) %d : ", j + 1);
                    if (scanf(" %c", &valeur.char_value) != 1) {
                        printf("Erreur de saisie. Veuillez entrer un caractère.\n");
                        return;
                    }
                    break;
                case DOUBLE:
                    printf("Saisir la valeur (double) %d : ", j + 1);
                    if (scanf("%lf", &valeur.double_value) != 1) {
                        printf("Erreur de saisie. Veuillez entrer un double.\n");
                        return;
                    }
                    break;
                case STRING:
                    printf("Saisir la valeur (string) %d : ", j + 1);
                    valeur.string_value = (char*)malloc(100 * sizeof(char)); // Alloue de la memoire pour la chaîne de caractères
                    if (scanf("%99s", valeur.string_value) != 1) {
                        printf("Erreur de saisie. Veuillez entrer une chaîne de caractères.\n");
                        return;
                    }
                    break;
                default:
                    printf("Type non supporte\n");
                    return;
            }
            insert_value(dataframe->colonnes[i], &valeur); // Insère la valeur dans la colonne
        }
    }
}

// Remplit le dataframe avec des valeurs predefinies
void fill_dataframe_with_predefined_values(CDataframe* dataframe) {
    for (int i = 0; i < dataframe->nombre_colonnes; i++) {
        for (int j = 1; j <= 10; j++) {
            COL_TYPE valeur;
            valeur.int_value = j;
            insert_value(dataframe->colonnes[i], &valeur); // Insère des valeurs predefinies dans chaque colonne
        }
    }
}

// Affiche tout le dataframe
void print_dataframe(CDataframe* dataframe) {
    for (int i = 0; i < dataframe->nombre_colonnes; i++) {
        printf("Colonne %s :\n", dataframe->colonnes[i]->titre);
        print_col(dataframe->colonnes[i]); // Affiche chaque colonne
        printf("\n");
    }
}

// Affiche partiellement les lignes du dataframe
void print_partial_rows(CDataframe* dataframe, int limite) {
    for (int i = 0; i < dataframe->nombre_colonnes; i++) {
        printf("Colonne %s :\n", dataframe->colonnes[i]->titre);
        for (int j = 0; j < limite && j < dataframe->colonnes[i]->taille_logique; j++) {
            switch (dataframe->colonnes[i]->type_donnees) {
                case UINT:
                    printf("[%d] %u\n", j, dataframe->colonnes[i]->donnees[j].uint_value);
                    break;
                case INT:
                    printf("[%d] %d\n", j, dataframe->colonnes[i]->donnees[j].int_value);
                    break;
                case CHAR:
                    printf("[%d] %c\n", j, dataframe->colonnes[i]->donnees[j].char_value);
                    break;
                case FLOAT:
                    printf("[%d] %f\n", j, dataframe->colonnes[i]->donnees[j].float_value);
                    break;
                case DOUBLE:
                    printf("[%d] %lf\n", j, dataframe->colonnes[i]->donnees[j].double_value);
                    break;
                case STRING:
                    printf("[%d] %s\n", j, dataframe->colonnes[i]->donnees[j].string_value);
                    break;
                case STRUCTURE:
                    printf("[%d] %p\n", j, dataframe->colonnes[i]->donnees[j].struct_value);
                    break;
                default:
                    printf("Type non supporte\n");
            }
        }
        printf("\n");
    }
}

// Affiche partiellement les colonnes du dataframe
void print_partial_columns(CDataframe* dataframe, int limite) {
    for (int i = 0; i < limite && i < dataframe->nombre_colonnes; i++) {
        printf("Colonne %s :\n", dataframe->colonnes[i]->titre);
        print_col(dataframe->colonnes[i]); // Affiche chaque colonne jusqu'a la limite specifiee
        printf("\n");
    }
}

// Ajoute une ligne au dataframe
void add_row(CDataframe* dataframe, COL_TYPE* values) {
    for (int i = 0; i < dataframe->nombre_colonnes; i++) {
        insert_value(dataframe->colonnes[i], &values[i]); // Insère les valeurs dans chaque colonne
    }
}

// Supprime une ligne du dataframe
void remove_row(CDataframe* dataframe, int index) {
    for (int i = 0; i < dataframe->nombre_colonnes; i++) {
        if (index >= 0 && index < dataframe->colonnes[i]->taille_logique) {
            for (int j = index; j < dataframe->colonnes[i]->taille_logique - 1; j++) {
                dataframe->colonnes[i]->donnees[j] = dataframe->colonnes[i]->donnees[j + 1]; // Decale les valeurs
            }
            dataframe->colonnes[i]->taille_logique--; // Reduit la taille logique
        }
    }
}

// Ajoute une colonne au dataframe
void add_column(CDataframe* dataframe, ENUM_TYPE type, const char* titre) {
    COLUMN* new_column = create_column(type, titre);
    if (new_column != NULL) {
        dataframe->colonnes = realloc(dataframe->colonnes, (dataframe->nombre_colonnes + 1) * sizeof(COLUMN*)); // Realloue la memoire pour ajouter la nouvelle colonne
        if (dataframe->colonnes != NULL) {
            dataframe->colonnes[dataframe->nombre_colonnes] = new_column; // Ajoute la nouvelle colonne
            dataframe->nombre_colonnes++;
        } else {
            delete_column(&new_column); // Supprime la colonne si l'allocation echoue
        }
    }
}

// Supprime une colonne du dataframe
void remove_column(CDataframe* dataframe, int index) {
    if (index >= 0 && index < dataframe->nombre_colonnes) {
        delete_column(&(dataframe->colonnes[index])); // Supprime la colonne specifiee
        for (int i = index; i < dataframe->nombre_colonnes - 1; i++) {
            dataframe->colonnes[i] = dataframe->colonnes[i + 1]; // Decale les colonnes
        }
        dataframe->nombre_colonnes--;
        dataframe->colonnes = realloc(dataframe->colonnes, dataframe->nombre_colonnes * sizeof(COLUMN*)); // Realloue la memoire pour le nouveau nombre de colonnes
    }
}

// Renomme une colonne du dataframe
void rename_column(CDataframe* dataframe, int index, const char* new_title) {
    if (index >= 0 && index < dataframe->nombre_colonnes) {
        free(dataframe->colonnes[index]->titre); // Libère l'ancienne chaîne de titre
        dataframe->colonnes[index]->titre = copier_chaine(new_title); // Copie la nouvelle chaîne de titre
    }
}

// Verifie si une valeur existe dans le dataframe
int value_exists(CDataframe* dataframe, COL_TYPE value) {
    for (int i = 0; i < dataframe->nombre_colonnes; i++) {
        if (count_value(dataframe->colonnes[i], value) > 0) {
            return 1; // Renvoie 1 si la valeur existe
        }
    }
    return 0; // Renvoie 0 si la valeur n'existe pas
}

// Obtient la valeur d'une cellule
COL_TYPE get_cell_value(CDataframe* dataframe, int row, int col) {
    if (row >= 0 && row < dataframe->colonnes[0]->taille_logique && col >= 0 && col < dataframe->nombre_colonnes) {
        return dataframe->colonnes[col]->donnees[row]; // Renvoie la valeur de la cellule
    }
    COL_TYPE null_value;
    null_value.uint_value = 0;
    return null_value; // Renvoie une valeur nulle si les indices sont hors limites
}

// Definit la valeur d'une cellule
void set_cell_value(CDataframe* dataframe, int row, int col, COL_TYPE value) {
    if (row >= 0 && row < dataframe->colonnes[0]->taille_logique && col >= 0 && col < dataframe->nombre_colonnes) {
        dataframe->colonnes[col]->donnees[row] = value; // Met a jour la valeur de la cellule
    }
}

// Affiche les noms des colonnes
void print_column_names(CDataframe* dataframe) {
    printf("Noms des colonnes :\n");
    for (int i = 0; i < dataframe->nombre_colonnes; i++) {
        printf("%s\n", dataframe->colonnes[i]->titre);
    }
}

// Affiche le nombre de lignes
void print_row_count(CDataframe* dataframe) {
    if (dataframe->nombre_colonnes > 0) {
        printf("Nombre de lignes: %d\n", dataframe->colonnes[0]->taille_logique);
    } else {
        printf("Le dataframe est vide.\n");
    }
}

// Affiche le nombre de colonnes
void print_col_count(CDataframe* dataframe) {
    printf("Nombre de colonnes: %d\n", dataframe->nombre_colonnes);
}

// Compte les cellules egales a une valeur
void count_cells_equal_to_x(CDataframe* dataframe, COL_TYPE x) {
    int count = 0;
    for (int i = 0; i < dataframe->nombre_colonnes; i++) {
        count += count_value(dataframe->colonnes[i], x); // Ajoute le nombre de valeurs egales a x
    }
    printf("Nombre de cellules contenant la valeur specifiee: %d\n", count);
}

// Compte les cellules superieures a une valeur
void count_cells_greater_than_x(CDataframe* dataframe, COL_TYPE x) {
    int count = 0;
    for (int i = 0; i < dataframe->nombre_colonnes; i++) {
        count += count_greater(dataframe->colonnes[i], x); // Ajoute le nombre de valeurs superieures a x
    }
    printf("Nombre de cellules contenant une valeur superieure a la valeur specifiee: %d\n", count);
}

// Compte les cellules inferieures a une valeur
void count_cells_less_than_x(CDataframe* dataframe, COL_TYPE x) {
    int count = 0;
    for (int i = 0; i < dataframe->nombre_colonnes; i++) {
        count += count_less(dataframe->colonnes[i], x); // Ajoute le nombre de valeurs inferieures a x
    }
    printf("Nombre de cellules contenant une valeur inferieure a la valeur specifiee: %d\n", count);
}
