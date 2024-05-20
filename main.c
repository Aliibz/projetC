#include "cdataframe.h"
#include "alimentation/creat_cdataframe.h"
#include "analyse/return_value.h"
#include "affichage/display_cdataframe.h"
#include "operations/usual_op.h"

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
    printf("20. Quitter\n");
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
                int values[nombre_colonnes];
                printf("Entrez les valeurs pour la nouvelle ligne:\n");
                for (int i = 0; i < nombre_colonnes; i++) {
                    printf("Valeur pour la colonne %d: ", i);
                    scanf("%d", &values[i]);
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
                add_column(dataframe, titre);
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
                printf("Entrez la valeur a verifier: ");
                int value;
                scanf("%d", &value);
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
                scanf("%d", &col);
                int value = get_cell_value(dataframe, row, col);
                if (value != -1) {
                    printf("La valeur a la cellule (%d, %d) est %d.\n", row, col, value);
                } else {
                    printf("Cellule invalide.\n");
                }
                break;
            }
            case 13: {
                printf("Entrez l'index de la ligne: ");
                int row;
                scanf("%d", &row);
                printf("Entrez l'index de la colonne: ");
                int col;
                scanf("%d", &col);
                printf("Entrez la nouvelle valeur: ");
                int value;
                scanf("%d", &value);
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
                printf("Entrez la valeur a compter: ");
                int x;
                scanf("%d", &x);
                count_cells_equal_to_x(dataframe, x);
                break;
            }
            case 18: {
                printf("Entrez la valeur a comparer: ");
                int x;
                scanf("%d", &x);
                count_cells_greater_than_x(dataframe, x);
                break;
            }
            case 19: {
                printf("Entrez la valeur a comparer: ");
                int x;
                scanf("%d", &x);
                count_cells_less_than_x(dataframe, x);
                break;
            }
            case 20:
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