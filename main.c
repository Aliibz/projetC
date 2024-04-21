#include "column.h"
#include "cdataframe.h"

#include "alimentation/creat_cdataframe.h"
#include "analyse/return_value.h"
#include "affichage/display_cdataframe.h"
#include "operations/usual_op.h"
#include <stdio.h>
#include <stdlib.h>


int main() {

    int choix, running = 1;
    CDataframe *dataframe = create_empty_dataframe(3);  // Crée un dataframe avec 3 colonnes

    while (running) {
        printf("Menu :\n");
        printf("1. Remplir DataFrame avec saisie utilisateur\n");
        printf("2. Remplir DataFrame avec valeurs prédéfinies\n");
        printf("3. Afficher DataFrame complet\n");
        printf("4. Afficher parties des lignes du DataFrame\n");
        printf("5. Afficher parties des colonnes du DataFrame\n");
        printf("6. Quitter\n");
        printf("Entrer votre choix : ");
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
            case 4:
                printf("Entrer la limite de lignes à afficher : ");
            int limite_lignes;
            scanf("%d", &limite_lignes);
            print_partial_rows(dataframe, limite_lignes);
            break;
            case 5:
                printf("Entrer la limite de colonnes à afficher : ");
            int limite_colonnes;
            scanf("%d", &limite_colonnes);
            print_partial_columns(dataframe, limite_colonnes);
            break;
            case 6:
                running = 0;
            break;
            default:
                printf("Choix non valide, veuillez réessayer.\n");
        }
    }
    return 0;
}
