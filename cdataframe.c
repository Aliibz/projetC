/*
Nom du projet : Gestion de DataFrame en C
Auteurs : Ali Ibnou Zahir et Arthur Hacques
Rôle : Ce fichier contient les fonctions pour gerer un DataFrame en utilisant des listes doublement chaînees.
*/

#include "cdataframe.h"
#include <string.h>
#include <stdio.h>

/* Cree un DataFrame vide avec un nombre specifie de colonnes */
CDataframe* creer_dataframe_vide(int nombre_colonnes) {
    CDataframe* dataframe = liste_creer_liste();
    if (dataframe == NULL) {
        return NULL;
    }
    for (int i = 0; i < nombre_colonnes; i++) {
        char titre_default[20];
        sprintf(titre_default, "Colonne%d", i);
        COLONNE *col = creer_colonne(INT, titre_default);
        if (col == NULL) {
            supprimer_dataframe(&dataframe);
            return NULL;
        }
        noeud *node = liste_creer_noeud(col);
        liste_inserer_queue(dataframe, node);
    }
    return dataframe;
}

/* Supprime le DataFrame et libere la memoire associee */
void supprimer_dataframe(CDataframe **cdf) {
    if (*cdf != NULL) {
        noeud *current = (*cdf)->tete;
        while (current != NULL) {
            noeud *next = current->suivant;
            supprimer_colonne((COLONNE **)&current->data);
            free(current);
            current = next;
        }
        liste_supprimer_liste(*cdf);
        *cdf = NULL;
    }
}

/* Supprime une colonne specifique du DataFrame par son nom */
void supprimer_colonne_dataframe(CDataframe *cdf, char *nom_colonne) {
    noeud *current = cdf->tete;
    noeud *prev = NULL;

    while (current != NULL) {
        COLONNE *col = (COLONNE *)current->data;

        if (strcmp(col->titre, nom_colonne) == 0) {
            noeud *to_delete = current;
            current = current->suivant;

            if (prev == NULL) {
                // Supprimer le premier noeud
                cdf->tete = current;
                if (current != NULL) {
                    current->precedent = NULL;
                }
            } else {
                prev->suivant = current;
                if (current != NULL) {
                    current->precedent = prev;
                }
            }

            if (to_delete == cdf->queue) {
                // Si le noeud a supprimer est le dernier
                cdf->queue = prev;
            }

            supprimer_colonne((COLONNE **)&to_delete->data);
            free(to_delete);
        } else {
            prev = current;
            current = current->suivant;
        }
    }
}

/* Remplit le DataFrame avec des valeurs saisies par l'utilisateur */
void remplir_dataframe_utilisateur(CDataframe* dataframe) {
    char choix[4];
    printf("Voulez-vous remplir une colonne specifique ? (oui/non) : ");
    scanf("%3s", choix);

    if (strcmp(choix, "oui") == 0) {
        char nom_colonne[50];
        printf("Entrez le nom de la colonne a remplir : ");
        scanf("%49s", nom_colonne);

        noeud *current = dataframe->tete;
        while (current != NULL) {
            COLONNE *col = (COLONNE *)current->data;
            if (strcmp(col->titre, nom_colonne) == 0) {
                for (int i = 0; i < 10; i++) {
                    COL_TYPE valeur;
                    printf("Saisir les donnees pour la colonne %s :\n", col->titre);
                    switch (col->type_donnees) {
                        case INT:
                            printf("Saisir la valeur (entier) %d : ", i + 1);
                            scanf("%d", &valeur.int_value);
                            break;
                        case FLOAT:
                            printf("Saisir la valeur (flottant) %d : ", i + 1);
                            scanf("%f", &valeur.float_value);
                            break;
                        case CHAR:
                            printf("Saisir la valeur (caractere) %d : ", i + 1);
                            scanf(" %c", &valeur.char_value);
                            break;
                        case DOUBLE:
                            printf("Saisir la valeur (double) %d : ", i + 1);
                            scanf("%lf", &valeur.double_value);
                            break;
                        case STRING:
                            valeur.string_value = (char*)malloc(100 * sizeof(char));
                            scanf("%99s", valeur.string_value);
                            break;
                        default:
                            printf("Type non supporte\n");
                            return;
                    }
                    inserer_valeur(col, &valeur);
                }
                return; // Sortir de la fonction une fois la colonne remplie
            }
            current = current->suivant;
        }
        printf("Colonne non trouvee.\n");
    } else {
        noeud *current = dataframe->tete;
        while (current != NULL) {
            COLONNE *col = (COLONNE *)current->data;
            for (int i = 0; i < 10; i++) {
                COL_TYPE valeur;
                printf("Saisir les donnees pour la colonne %s :\n", col->titre);
                switch (col->type_donnees) {
                    case INT:
                        printf("Saisir la valeur (entier) %d : ", i + 1);
                        scanf("%d", &valeur.int_value);
                        break;
                    case FLOAT:
                        printf("Saisir la valeur (flottant) %d : ", i + 1);
                        scanf("%f", &valeur.float_value);
                        break;
                    case CHAR:
                        printf("Saisir la valeur (caractere) %d : ", i + 1);
                        scanf(" %c", &valeur.char_value);
                        break;
                    case DOUBLE:
                        printf("Saisir la valeur (double) %d : ", i + 1);
                        scanf("%lf", &valeur.double_value);
                        break;
                    case STRING:
                        valeur.string_value = (char*)malloc(100 * sizeof(char));
                        scanf("%99s", valeur.string_value);
                        break;
                    default:
                        printf("Type non supporte\n");
                        return;
                }
                inserer_valeur(col, &valeur);
            }
            current = current->suivant;
        }
    }
}

/* Remplit le DataFrame avec des valeurs predefinies */
void remplir_dataframe_valeurs_predefinies(CDataframe* dataframe) {
    if (dataframe == NULL) {
        return;
    }
    noeud *current = obtenir_premier_noeud(dataframe);
    while (current != NULL) {
        COLONNE *col = (COLONNE *)current->data;
        if (col == NULL) {
            current = obtenir_noeud_suivant(dataframe, current);
            continue;
        }
        for (int j = 1; j <= 10; j++) {
            COL_TYPE valeur;
            valeur.int_value = j;
            inserer_valeur(col, &valeur);
        }
        current = obtenir_noeud_suivant(dataframe, current);
    }
}

/* Affiche le contenu complet du DataFrame */
void afficher_dataframe(CDataframe* dataframe) {
    if (dataframe == NULL) {
        printf("Le DataFrame est vide.\n");
        return;
    }
    noeud *current = dataframe->tete;
    while (current != NULL) {
        COLONNE *col = (COLONNE *)current->data;
        printf("%-15s", col->titre);
        current = current->suivant;
    }
    printf("\n");
    int max_lignes = 0;
    current = dataframe->tete;
    while (current != NULL) {
        COLONNE *col = (COLONNE *)current->data;
        if (col->taille_logique > max_lignes) {
            max_lignes = col->taille_logique;
        }
        current = current->suivant;
    }
    for (int i = 0; i < max_lignes; i++) {
        current = dataframe->tete;
        while (current != NULL) {
            COLONNE *col = (COLONNE *)current->data;
            if (i < col->taille_logique) {
                switch (col->type_donnees) {
                    case UINT:
                        printf("%-15u", col->donnees[i].uint_value);
                        break;
                    case INT:
                        printf("%-15d", col->donnees[i].int_value);
                        break;
                    case CHAR:
                        printf("%-15c", col->donnees[i].char_value);
                        break;
                    case FLOAT:
                        printf("%-15f", col->donnees[i].float_value);
                        break;
                    case DOUBLE:
                        printf("%-15lf", col->donnees[i].double_value);
                        break;
                    case STRING:
                        printf("%-15s", col->donnees[i].string_value);
                        break;
                    default:
                        printf("%-15s", "N/A");
                }
            } else {
                printf("%-15s", "NULL");
            }
            current = current->suivant;
        }
        printf("\n");
    }
}

/* Affiche une partie des lignes du DataFrame */
void afficher_lignes_partielles(CDataframe* dataframe, int limite) {
    noeud *current = dataframe->tete;
    while (current != NULL) {
        COLONNE *col = (COLONNE *)current->data;
        printf("%s:\n", col->titre);
        for (int j = 0; j < limite && j < col->taille_logique; j++) {
            switch (col->type_donnees) {
                case UINT:
                    printf("[%d] %u\n", j, col->donnees[j].uint_value);
                    break;
                case INT:
                    printf("[%d] %d\n", j, col->donnees[j].int_value);
                    break;
                case CHAR:
                    printf("[%d] %c\n", j, col->donnees[j].char_value);
                    break;
                case FLOAT:
                    printf("[%d] %f\n", j, col->donnees[j].float_value);
                    break;
                case DOUBLE:
                    printf("[%d] %lf\n", j, col->donnees[j].double_value);
                    break;
                case STRING:
                    printf("[%d] %s\n", j, col->donnees[j].string_value);
                    break;
                case STRUCTURE:
                    printf("[%d] %p\n", j, col->donnees[j].struct_value);
                    break;
                default:
                    printf("Type non supporte\n");
            }
        }
        printf("\n");
        current = current->suivant;
    }
}

/* Affiche une partie des colonnes du DataFrame */
void afficher_colonnes_partielles(CDataframe* dataframe, int limite) {
    noeud *current = dataframe->tete;
    int count = 0;
    while (current != NULL && count < limite) {
        COLONNE *col = (COLONNE *)current->data;
        printf("%s :\n", col->titre);
        afficher_colonne(col);
        printf("\n");
        current = current->suivant;
        count++;
    }
}

/* Ajoute une nouvelle ligne au DataFrame */
void ajouter_ligne(CDataframe* dataframe, COL_TYPE* valeurs) {
    noeud *current = dataframe->tete;
    int count = 0;
    while (current != NULL) {
        inserer_valeur((COLONNE *)current->data, &valeurs[count]);
        current = current->suivant;
        count++;
    }
}

/* Supprime une ligne du DataFrame a un index specifie */
void supprimer_ligne(CDataframe* dataframe, int index) {
    noeud *current = dataframe->tete;
    while (current != NULL) {
        COLONNE *col = (COLONNE *)current->data;
        if (index >= 0 && index < col->taille_logique) {
            for (int j = index; j < col->taille_logique - 1; j++) {
                col->donnees[j] = col->donnees[j + 1];
            }
            col->taille_logique--;
        }
        current = current->suivant;
    }
}

/* Ajoute une nouvelle colonne au DataFrame */
void ajouter_colonne(CDataframe* dataframe, ENUM_TYPE type, const char* titre) {
    COLONNE* new_column = creer_colonne(type, titre);
    if (new_column != NULL) {
        noeud *node = liste_creer_noeud(new_column);
        liste_inserer_queue(dataframe, node);
    }
}

/* Renomme une colonne specifique dans le DataFrame */
void renommer_colonne(CDataframe* dataframe, int index, const char* nouveau_titre) {
    noeud *current = dataframe->tete;
    int count = 0;
    while (current != NULL) {
        if (count == index) {
            COLONNE *col = (COLONNE *)current->data;
            free(col->titre);
            col->titre = copier_chaine(nouveau_titre);
            break;
        }
        current = current->suivant;
        count++;
    }
}

/* Verifie si une valeur existe dans le DataFrame */
int valeur_existe(CDataframe* dataframe, COL_TYPE valeur) {
    noeud *current = dataframe->tete;
    while (current != NULL) {
        COLONNE *col = (COLONNE *)current->data;
        if (compter_valeur(col, valeur) > 0) {
            return 1;
        }
        current = current->suivant;
    }
    return 0;
}

/* Obtient la valeur d'une cellule specifique */
COL_TYPE obtenir_valeur_cellule(CDataframe* dataframe, int ligne, int col) {
    noeud *current = dataframe->tete;
    int count = 0;
    while (current != NULL) {
        if (count == col) {
            COLONNE *column = (COLONNE *)current->data;
            return column->donnees[ligne];
        }
        current = current->suivant;
        count++;
    }
    COL_TYPE null_value;
    null_value.uint_value = 0;
    return null_value;
}

/* Definit la valeur d'une cellule specifique */
void definir_valeur_cellule(CDataframe* dataframe, int ligne, int col, COL_TYPE valeur) {
    noeud *current = dataframe->tete;
    int count = 0;
    while (current != NULL) {
        if (count == col) {
            COLONNE *column = (COLONNE *)current->data;
            column->donnees[ligne] = valeur;
        }
        current = current->suivant;
        count++;
    }
}

/* Affiche les noms des colonnes du DataFrame */
void afficher_noms_colonnes(CDataframe* dataframe) {
    noeud *current = dataframe->tete;
    while (current != NULL) {
        COLONNE *col = (COLONNE *)current->data;
        printf("%s\n", col->titre);
        current = current->suivant;
    }
}

/* Affiche le nombre de lignes dans le DataFrame */
void afficher_nombre_lignes(CDataframe* dataframe) {
    if (dataframe->tete != NULL) {
        COLONNE *col = (COLONNE *)dataframe->tete->data;
        printf("Nombre de lignes: %d\n", col->taille_logique);
    } else {
        printf("Le DataFrame est vide.\n");
    }
}

/* Affiche le nombre de colonnes dans le DataFrame */
void afficher_nombre_colonnes(CDataframe* dataframe) {
    int count = 0;
    noeud *current = dataframe->tete;
    while (current != NULL) {
        count++;
        current = current->suivant;
    }
    printf("Nombre de colonnes: %d\n", count);
}

/* Compte le nombre de cellules egales a une valeur specifiee */
void compter_cellules_egales_a(CDataframe* dataframe, COL_TYPE x) {
    int count = 0;
    noeud *current = dataframe->tete;
    while (current != NULL) {
        COLONNE *col = (COLONNE *)current->data;
        count += compter_valeur(col, x);
        current = current->suivant;
    }
    printf("Nombre de cellules contenant la valeur specifiee: %d\n", count);
}

/* Compte le nombre de cellules superieures a une valeur specifiee */
void compter_cellules_superieures_a(CDataframe* dataframe, COL_TYPE x) {
    int count = 0;
    noeud *current = dataframe->tete;
    while (current != NULL) {
        COLONNE *col = (COLONNE *)current->data;
        count += compter_superieur(col, x);
        current = current->suivant;
    }
    printf("Nombre de cellules contenant une valeur superieure a la valeur specifiee: %d\n", count);
}

/* Compte le nombre de cellules inferieures a une valeur specifiee */
void compter_cellules_inferieures_a(CDataframe* dataframe, COL_TYPE x) {
    int count = 0;
    noeud *current = dataframe->tete;
    while (current != NULL) {
        COLONNE *col = (COLONNE *)current->data;
        count += compter_inferieur(col, x);
        current = current->suivant;
    }
    printf("Nombre de cellules contenant une valeur inferieure a la valeur specifiee: %d\n", count);
}
