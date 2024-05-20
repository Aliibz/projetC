/*
Nom du projet : Gestion de DataFrame en C
Auteurs : Ali Ibnou Zahir et Arthur Hacques
Rôle : Ce fichier contient la fonction principale et l'interface utilisateur pour interagir avec le DataFrame.
*/

#include <stdio.h>
#include <stdlib.h>
#include "cdataframe.h"

/* Affiche le menu principal */
void afficher_menu() {
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
    printf("*20. Effacer l'index d'une colonne\n");
    printf("*21. Verifier l'index d'une colonne\n");
    printf("*22. Mettre a jour l'index d'une colonne\n");
    printf("*23. Rechercher une valeur dans une colonne\n");
    printf("*24. Trier une colonne\n");
    printf("*25. Afficher une colonne par index\n");
    printf("26. Quitter\n");
    printf("Entrez votre choix: ");
}

int main() {
    int choix, en_cours = 1;
    int nombre_colonnes = 3;
    CDataframe *dataframe = creer_dataframe_vide(nombre_colonnes);

    while (en_cours) {
        afficher_menu();
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("\n");
                remplir_dataframe_utilisateur(dataframe);
                break;
            case 2:
                printf("\n");
                remplir_dataframe_valeurs_predefinies(dataframe);
                break;
            case 3:
                printf("\n");
                afficher_dataframe(dataframe);
                break;
            case 4: {
                printf("\n");
                printf("Entrer la limite de lignes a afficher: ");
                int limite_lignes;
                scanf("%d", &limite_lignes);
                afficher_lignes_partielles(dataframe, limite_lignes);
                break;
            }
            case 5: {
                printf("Entrer la limite de colonnes a afficher: ");
                int limite_colonnes;
                scanf("%d", &limite_colonnes);
                afficher_colonnes_partielles(dataframe, limite_colonnes);
                break;
            }
            case 6: {
                COL_TYPE valeurs[nombre_colonnes];
                printf("Entrez les valeurs pour la nouvelle ligne:\n");
                for (int i = 0; i < nombre_colonnes; i++) {
                    printf("Valeur pour la colonne %d: ", i);
                    if (((COLONNE *)obtenir_premier_noeud(dataframe)->data)->type_donnees == INT) {
                        scanf("%d", &valeurs[i].int_value);
                    }
                }
                ajouter_ligne(dataframe, valeurs);
                break;
            }
            case 7: {
                printf("Entrez l'index de la ligne a supprimer: ");
                int index;
                scanf("%d", &index);
                supprimer_ligne(dataframe, index);
                break;
            }
            case 8: {
                char titre[50];
                printf("Entrez le titre de la nouvelle colonne: ");
                scanf("%s", titre);
                printf("Entrez le type de la nouvelle colonne (1-NULLVAL, 2-UINT, 3-INT, 4-CHAR, 5-FLOAT, 6-DOUBLE, 7-STRING, 8-STRUCTURE): ");
                int type;
                scanf("%d", &type);
                ajouter_colonne(dataframe, (ENUM_TYPE)type, titre);
                break;
            }
            case 9: {
                char nom_colonne[50];
                printf("Entrez le nom de la colonne a supprimer: ");
                scanf("%s", nom_colonne);
                supprimer_colonne_dataframe(dataframe, nom_colonne);
                break;
            }
            case 10: {
                printf("Entrez l'index de la colonne a renommer: ");
                int index;
                scanf("%d", &index);
                char nouveau_titre[50];
                printf("Entrez le nouveau titre de la colonne: ");
                scanf("%s", nouveau_titre);
                renommer_colonne(dataframe, index, nouveau_titre);
                break;
            }
            case 11: {
                COL_TYPE valeur;
                if (((COLONNE *)obtenir_premier_noeud(dataframe)->data)->type_donnees == INT) {
                    printf("Entrez la valeur a verifier (entier): ");
                    scanf("%d", &valeur.int_value);
                }
                if (valeur_existe(dataframe, valeur)) {
                    printf("La valeur existe dans le DataFrame.\n");
                } else {
                    printf("La valeur n'existe pas dans le DataFrame.\n");
                }
                break;
            }
            case 12: {
                printf("Entrez l'index de la ligne: ");
                int ligne;
                scanf("%d", &ligne);
                printf("Entrez l'index de la colonne: ");
                int col;
                scanf("%d", &col);
                COL_TYPE valeur = obtenir_valeur_cellule(dataframe, ligne, col);
                if (((COLONNE *)obtenir_premier_noeud(dataframe)->data)->type_donnees == INT) {
                    printf("La valeur a la cellule (%d, %d) est %d.\n", ligne, col, valeur.int_value);
                }
                break;
            }
            case 13: {
                printf("Entrez l'index de la ligne: ");
                int ligne;
                scanf("%d", &ligne);
                printf("Entrez l'index de la colonne: ");
                int col;
                scanf("%d", &col);
                COL_TYPE valeur;
                if (((COLONNE *)obtenir_premier_noeud(dataframe)->data)->type_donnees == INT) {
                    printf("Entrez la nouvelle valeur (entier): ");
                    scanf("%d", &valeur.int_value);
                }
                definir_valeur_cellule(dataframe, ligne, col, valeur);
                break;
            }
            case 14:
                printf("\n");
                afficher_noms_colonnes(dataframe);
                break;
            case 15:
                printf("\n");
                afficher_nombre_lignes(dataframe);
                break;
            case 16:
                printf("\n");
                afficher_nombre_colonnes(dataframe);
                break;
            case 17: {
                COL_TYPE x;
                if (((COLONNE *)obtenir_premier_noeud(dataframe)->data)->type_donnees == INT) {
                    printf("Entrez la valeur a compter (entier): ");
                    scanf("%d", &x.int_value);
                }
                compter_cellules_egales_a(dataframe, x);
                break;
            }
            case 18: {
                COL_TYPE x;
                if (((COLONNE *)obtenir_premier_noeud(dataframe)->data)->type_donnees == INT) {
                    printf("Entrez la valeur a comparer (entier): ");
                    scanf("%d", &x.int_value);
                }
                compter_cellules_superieures_a(dataframe, x);
                break;
            }
            case 19: {
                COL_TYPE x;
                if (((COLONNE *)obtenir_premier_noeud(dataframe)->data)->type_donnees == INT) {
                    printf("Entrez la valeur a comparer (entier): ");
                    scanf("%d", &x.int_value);
                }
                compter_cellules_inferieures_a(dataframe, x);
                break;
            }
            case 20: {
                printf("Entrez l'index de la colonne pour effacer l'index: ");
                int index;
                scanf("%d", &index);
                noeud *current = obtenir_premier_noeud(dataframe);
                for (int i = 0; i < index && current != NULL; i++) {
                    current = obtenir_noeud_suivant(dataframe, current);
                }
                if (current != NULL) {
                    effacer_index((COLONNE *)current->data);
                    printf("Index efface pour la colonne %d.\n", index);
                }
                break;
            }
            case 21: {
                printf("Entrez l'index de la colonne pour verifier l'index: ");
                int index;
                scanf("%d", &index);
                noeud *current = obtenir_premier_noeud(dataframe);
                for (int i = 0; i < index && current != NULL; i++) {
                    current = obtenir_noeud_suivant(dataframe, current);
                }
                if (current != NULL) {
                    int valid = verifier_index((COLONNE *)current->data);
                    printf("L'index de la colonne %d est %s.\n", index, valid ? "valide" : "non valide");
                }
                break;
            }
            case 22: {
                printf("Entrez l'index de la colonne pour mettre a jour l'index: ");
                int index;
                scanf("%d", &index);
                noeud *current = obtenir_premier_noeud(dataframe);
                for (int i = 0; i < index && current != NULL; i++) {
                    current = obtenir_noeud_suivant(dataframe, current);
                }
                if (current != NULL) {
                    mettre_a_jour_index((COLONNE *)current->data);
                    printf("Index mis a jour pour la colonne %d.\n", index);
                }
                break;
            }
            case 23: {
                printf("Entrez l'index de la colonne pour rechercher la valeur: ");
                int index;
                scanf("%d", &index);
                noeud *current = obtenir_premier_noeud(dataframe);
                for (int i = 0; i < index && current != NULL; i++) {
                    current = obtenir_noeud_suivant(dataframe, current);
                }
                if (current != NULL) {
                    COL_TYPE val;
                    COLONNE *col = (COLONNE *)current->data;
                    if (col->type_donnees == INT) {
                        printf("Entrez la valeur (entier): ");
                        scanf("%d", &val.int_value);
                    }
                    int result = rechercher_valeur_dans_colonne(col, &val);
                    printf("Resultat de la recherche: %d\n", result);
                }
                break;
            }
            case 24: {
                printf("Entrez l'index de la colonne a trier: ");
                int index;
                scanf("%d", &index);
                printf("Entrez l'ordre de tri (0 pour ASC, 1 pour DESC): ");
                int direction_tri;
                scanf("%d", &direction_tri);
                noeud *current = obtenir_premier_noeud(dataframe);
                for (int i = 0; i < index && current != NULL; i++) {
                    current = obtenir_noeud_suivant(dataframe, current);
                }
                if (current != NULL) {
                    trier((COLONNE *)current->data, direction_tri);
                    printf("Colonne %d triee.\n", index);
                }
                break;
            }
            case 25: {
                printf("Entrez l'index de la colonne a afficher par index: ");
                int index;
                scanf("%d", &index);
                noeud *current = obtenir_premier_noeud(dataframe);
                for (int i = 0; i < index && current != NULL; i++) {
                    current = obtenir_noeud_suivant(dataframe, current);
                }
                if (current != NULL) {
                    afficher_colonne_par_index((COLONNE *)current->data);
                }
                break;
            }
            case 26:
                en_cours = 0;
                break;
            default:
                printf("Choix non valide, veuillez reessayer.\n");
        }
    }

    supprimer_dataframe(&dataframe);

    return 0;
}
