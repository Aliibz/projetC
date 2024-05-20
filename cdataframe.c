#include "cdataframe.h"

CDataframe* create_empty_dataframe(int nombre_colonnes) {
    CDataframe* dataframe = (CDataframe*)malloc(sizeof(CDataframe));
    if (dataframe == NULL) {
        return NULL;
    }
    dataframe->nombre_colonnes = nombre_colonnes;
    dataframe->colonnes = (COLUMN**)calloc(nombre_colonnes, sizeof(COLUMN*));
    if (dataframe->colonnes == NULL) {
        free(dataframe);
        return NULL;
    }
    for (int i = 0; i < nombre_colonnes; i++) {
        char titre_default[20];
        sprintf(titre_default, "Colonne%d", i);
        dataframe->colonnes[i] = create_column(titre_default);
        if (dataframe->colonnes[i] == NULL) {
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

void fill_dataframe_from_user_input(CDataframe* dataframe) {
    for (int i = 0; i < dataframe->nombre_colonnes; i++) {
        printf("Saisir les donnees pour la colonne %s :\n", dataframe->colonnes[i]->titre);
        for (int j = 0; j < 10; j++) { // Limite de 10 valeurs par colonne pour la saisie utilisateur
            int valeur;
            printf("Saisir la valeur %d : ", j + 1);
            if (scanf("%d", &valeur) != 1) {
                printf("Erreur de saisie. Veuillez entrer un entier.\n");
                return;
            }
            insert_value(dataframe->colonnes[i], valeur);
        }
    }
}

void fill_dataframe_with_predefined_values(CDataframe* dataframe) {
    for (int i = 0; i < dataframe->nombre_colonnes; i++) {
        for (int j = 1; j <= 10; j++) {
            insert_value(dataframe->colonnes[i], j);
        }
    }
}

void print_dataframe(CDataframe* dataframe) {
    for (int i = 0; i < dataframe->nombre_colonnes; i++) {
        printf("Colonne %s :\n", dataframe->colonnes[i]->titre);
        print_col(dataframe->colonnes[i]);
        printf("\n");
    }
}

void print_partial_rows(CDataframe* dataframe, int limite) {
    for (int i = 0; i < dataframe->nombre_colonnes; i++) {
        printf("Colonne %s :\n", dataframe->colonnes[i]->titre);
        for (int j = 0; j < limite && j < dataframe->colonnes[i]->taille_logique; j++) {
            printf("[%d] %d\n", j, dataframe->colonnes[i]->donnees[j]);
        }
        printf("\n");
    }
}

void print_partial_columns(CDataframe* dataframe, int limite) {
    for (int i = 0; i < limite && i < dataframe->nombre_colonnes; i++) {
        printf("Colonne %s :\n", dataframe->colonnes[i]->titre);
        print_col(dataframe->colonnes[i]);
        printf("\n");
    }
}

void add_row(CDataframe* dataframe, int* values) {
    for (int i = 0; i < dataframe->nombre_colonnes; i++) {
        insert_value(dataframe->colonnes[i], values[i]);
    }
}

void remove_row(CDataframe* dataframe, int index) {
    for (int i = 0; i < dataframe->nombre_colonnes; i++) {
        if (index >= 0 && index < dataframe->colonnes[i]->taille_logique) {
            for (int j = index; j < dataframe->colonnes[i]->taille_logique - 1; j++) {
                dataframe->colonnes[i]->donnees[j] = dataframe->colonnes[i]->donnees[j + 1];
            }
            dataframe->colonnes[i]->taille_logique--;
        }
    }
}

void add_column(CDataframe* dataframe, const char* titre) {
    COLUMN* new_column = create_column(titre);
    if (new_column != NULL) {
        dataframe->colonnes = realloc(dataframe->colonnes, (dataframe->nombre_colonnes + 1) * sizeof(COLUMN*));
        if (dataframe->colonnes != NULL) {
            dataframe->colonnes[dataframe->nombre_colonnes] = new_column;
            dataframe->nombre_colonnes++;
        } else {
            delete_column(&new_column);
        }
    }
}

void remove_column(CDataframe* dataframe, int index) {
    if (index >= 0 && index < dataframe->nombre_colonnes) {
        delete_column(&(dataframe->colonnes[index]));
        for (int i = index; i < dataframe->nombre_colonnes - 1; i++) {
            dataframe->colonnes[i] = dataframe->colonnes[i + 1];
        }
        dataframe->nombre_colonnes--;
        dataframe->colonnes = realloc(dataframe->colonnes, dataframe->nombre_colonnes * sizeof(COLUMN*));
    }
}

void rename_column(CDataframe* dataframe, int index, const char* new_title) {
    if (index >= 0 && index < dataframe->nombre_colonnes) {
        free(dataframe->colonnes[index]->titre);
        dataframe->colonnes[index]->titre = copier_chaine(new_title);
    }
}

int value_exists(CDataframe* dataframe, int value) {
    for (int i = 0; i < dataframe->nombre_colonnes; i++) {
        if (count_value(dataframe->colonnes[i], value) > 0) {
            return 1;
        }
    }
    return 0;
}

int get_cell_value(CDataframe* dataframe, int row, int col) {
    if (row >= 0 && row < dataframe->colonnes[0]->taille_logique && col >= 0 && col < dataframe->nombre_colonnes) {
        return dataframe->colonnes[col]->donnees[row];
    }
    return -1;
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

void print_row_count(CDataframe* dataframe) {
    if (dataframe->nombre_colonnes > 0) {
        printf("Nombre de lignes: %d\n", dataframe->colonnes[0]->taille_logique);
    } else {
        printf("Le dataframe est vide.\n");
    }
}

void print_col_count(CDataframe* dataframe) {
    printf("Nombre de colonnes: %d\n", dataframe->nombre_colonnes);
}

void count_cells_equal_to_x(CDataframe* dataframe, int x) {
    int count = 0;
    for (int i = 0; i < dataframe->nombre_colonnes; i++) {
        for (int j = 0; j < dataframe->colonnes[i]->taille_logique; j++) {
            if (dataframe->colonnes[i]->donnees[j] == x) {
                count++;
            }
        }
    }
    printf("Nombre de cellules contenant la valeur %d: %d\n", x, count);
}

void count_cells_greater_than_x(CDataframe* dataframe, int x) {
    int count = 0;
    for (int i = 0; i < dataframe->nombre_colonnes; i++) {
        for (int j = 0; j < dataframe->colonnes[i]->taille_logique; j++) {
            if (dataframe->colonnes[i]->donnees[j] > x) {
                count++;
            }
        }
    }
    printf("Nombre de cellules contenant une valeur superieure a %d: %d\n", x, count);
}

void count_cells_less_than_x(CDataframe* dataframe, int x) {
    int count = 0;
    for (int i = 0; i < dataframe->nombre_colonnes; i++) {
        for (int j = 0; j < dataframe->colonnes[i]->taille_logique; j++) {
            if (dataframe->colonnes[i]->donnees[j] < x) {
                count++;
            }
        }
    }
    printf("Nombre de cellules contenant une valeur inferieure a %d: %d\n", x, count);
}
