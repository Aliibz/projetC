#include <stdio.h>
#include <stdlib.h>
#include "cdataframe.h"

void print_menu() {
    printf("\nMenu:\n");
    printf("1. Remplir DataFrame avec saisie utilisateur\n");
    printf("2. Remplir DataFrame avec valeurs predefinies\n");
    printf("3. Afficher DataFrame complet\n");
    printf("4. Afficher parties des lignes du DataFrame\n");
    printf("5. Afficher parties des colonnes du DataFrame\n");
    printf("6. Ajouter une ligne au DataFrame\n");
    printf("7. Supprimer une ligne du DataFrame\n");
    printf("8. Ajouter une colonne au DataFrame\n");
    printf("9. Supprimer une colonne du DataFrame\n");
    printf("10. Renommer une colonne du DataFrame\n");
    printf("11. Verifier si une valeur existe dans le DataFrame\n");
    printf("12. Obtenir la valeur d'une cellule\n");
    printf("13. Definir la valeur d'une cellule\n");
    printf("14. Afficher les noms des colonnes\n");
    printf("15. Afficher le nombre de lignes\n");
    printf("16. Afficher le nombre de colonnes\n");
    printf("17. Compter les cellules egales a une valeur\n");
    printf("18. Compter les cellules superieures a une valeur\n");
    printf("19. Compter les cellules inferieures a une valeur\n");
    printf("20. Effacer l'index d'une colonne\n");
    printf("21. Verifier l'index d'une colonne\n");
    printf("22. Mettre a jour l'index d'une colonne\n");
    printf("23. Rechercher une valeur dans une colonne\n");
    printf("24. Trier une colonne\n");
    printf("25. Afficher une colonne par index\n");
    printf("26. Quitter\n");
    printf("Entrez votre choix: ");
}

int main() {
    int choix, running = 1;
    int nombre_colonnes = 3;
    CDataframe *dataframe = create_empty_dataframe(nombre_colonnes);

    while (running) {
        print_menu();
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                fill_dataframe_from_user_input(dataframe);
                break;
            case 2:
                fill_dataframe_with_predefined_values(dataframe);
                break;
            case 3:
                print_dataframe(dataframe);
                break;
            case 4: {
                printf("Entrer la limite de lignes a afficher: ");
                int limite_lignes;
                scanf("%d", &limite_lignes);
                print_partial_rows(dataframe, limite_lignes);
                break;
            }
            case 5: {
                printf("Entrer la limite de colonnes a afficher: ");
                int limite_colonnes;
                scanf("%d", &limite_colonnes);
                print_partial_columns(dataframe, limite_colonnes);
                break;
            }
            case 6: {
                COL_TYPE values[nombre_colonnes];
                printf("Entrez les valeurs pour la nouvelle ligne:\n");
                for (int i = 0; i < nombre_colonnes; i++) {
                    printf("Valeur pour la colonne %d: ", i);
                    if (dataframe->colonnes[i]->type_donnees == INT) {
                        scanf("%d", &values[i].int_value);
                    }
                }
                add_row(dataframe, values);
                break;
            }
            case 7: {
                printf("Entrez l'index de la ligne a supprimer: ");
                int index;
                scanf("%d", &index);
                remove_row(dataframe, index);
                break;
            }
            case 8: {
                char titre[50];
                printf("Entrez le titre de la nouvelle colonne: ");
                scanf("%s", titre);
                printf("Entrez le type de la nouvelle colonne (1-NULLVAL, 2-UINT, 3-INT, 4-CHAR, 5-FLOAT, 6-DOUBLE, 7-STRING, 8-STRUCTURE): ");
                int type;
                scanf("%d", &type);
                add_column(dataframe, (ENUM_TYPE)type, titre);
                break;
            }
            case 9: {
                printf("Entrez l'index de la colonne a supprimer: ");
                int index;
                scanf("%d", &index);
                remove_column(dataframe, index);
                break;
            }
            case 10: {
                printf("Entrez l'index de la colonne a renommer: ");
                int index;
                scanf("%d", &index);
                char new_title[50];
                printf("Entrez le nouveau titre de la colonne: ");
                scanf("%s", new_title);
                rename_column(dataframe, index, new_title);
                break;
            }
            case 11: {
                COL_TYPE value;
                if (dataframe->colonnes[0]->type_donnees == INT) {
                    printf("Entrez la valeur a verifier (entier): ");
                    scanf("%d", &value.int_value);
                }
                if (value_exists(dataframe, value)) {
                    printf("La valeur existe dans le DataFrame.\n");
                } else {
                    printf("La valeur n'existe pas dans le DataFrame.\n");
                }
                break;
            }
            case 12: {
                printf("Entrez l'index de la ligne: ");
                int row;
                scanf("%d", &row);
                printf("Entrez l'index de la colonne: ");
                int col;
                COL_TYPE value = get_cell_value(dataframe, row, col);
                if (dataframe->colonnes[col]->type_donnees == INT) {
                    printf("La valeur a la cellule (%d, %d) est %d.\n", row, col, value.int_value);
                }
                break;
            }
            case 13: {
                printf("Entrez l'index de la ligne: ");
                int row;
                scanf("%d", &row);
                printf("Entrez l'index de la colonne: ");
                int col;
                COL_TYPE value;
                if (dataframe->colonnes[col]->type_donnees == INT) {
                    printf("Entrez la nouvelle valeur (entier): ");
                    scanf("%d", &value.int_value);
                }
                set_cell_value(dataframe, row, col, value);
                break;
            }
            case 14:
                print_column_names(dataframe);
                break;
            case 15:
                print_row_count(dataframe);
                break;
            case 16:
                print_col_count(dataframe);
                break;
            case 17: {
                COL_TYPE x;
                if (dataframe->colonnes[0]->type_donnees == INT) {
                    printf("Entrez la valeur a compter (entier): ");
                    scanf("%d", &x.int_value);
                }
                count_cells_equal_to_x(dataframe, x);
                break;
            }
            case 18: {
                COL_TYPE x;
                if (dataframe->colonnes[0]->type_donnees == INT) {
                    printf("Entrez la valeur a comparer (entier): ");
                    scanf("%d", &x.int_value);
                }
                count_cells_greater_than_x(dataframe, x);
                break;
            }
            case 19: {
                COL_TYPE x;
                if (dataframe->colonnes[0]->type_donnees == INT) {
                    printf("Entrez la valeur a comparer (entier): ");
                    scanf("%d", &x.int_value);
                }
                count_cells_less_than_x(dataframe, x);
                break;
            }
            case 20: {
                printf("Entrez l'index de la colonne pour effacer l'index: ");
                int index;
                scanf("%d", &index);
                erase_index(dataframe->colonnes[index]);
                printf("Index efface pour la colonne %d.\n", index);
                break;
            }
            case 21: {
                printf("Entrez l'index de la colonne pour verifier l'index: ");
                int index;
                scanf("%d", &index);
                int valid = check_index(dataframe->colonnes[index]);
                printf("L'index de la colonne %d est %s.\n", index, valid ? "valide" : "non valide");
                break;
            }
            case 22: {
                printf("Entrez l'index de la colonne pour mettre a jour l'index: ");
                int index;
                scanf("%d", &index);
                update_index(dataframe->colonnes[index]);
                printf("Index mis a jour pour la colonne %d.\n", index);
                break;
            }
            case 23: {
                printf("Entrez l'index de la colonne pour rechercher la valeur: ");
                int index;
                scanf("%d", &index);
                COL_TYPE val;
                if (dataframe->colonnes[index]->type_donnees == INT) {
                    printf("Entrez la valeur (entier): ");
                    scanf("%d", &val.int_value);
                }
                int result = search_value_in_column(dataframe->colonnes[index], &val);
                printf("Resultat de la recherche: %d\n", result);
                break;
            }
            case 24: {
                printf("Entrez l'index de la colonne a trier: ");
                int index;
                scanf("%d", &index);
                printf("Entrez l'ordre de tri (0 pour ASC, 1 pour DESC): ");
                int sort_dir;
                scanf("%d", &sort_dir);
                sort(dataframe->colonnes[index], sort_dir);
                printf("Colonne %d triee.\n", index);
                break;
            }
            case 25: {
                printf("Entrez l'index de la colonne aa afficher par index: ");
                int index;
                scanf("%d", &index);
                print_col_by_index(dataframe->colonnes[index]);
                break;
            }
            case 26:
                running = 0;
                break;
            default:
                printf("Choix non valide, veuillez reessayer.\n");
        }
    }

    for (int i = 0; i < dataframe->nombre_colonnes; i++) {
        delete_column(&(dataframe->colonnes[i]));
    }
    free(dataframe->colonnes);
    free(dataframe);

    return 0;
}
