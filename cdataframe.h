/*
Nom du projet : Gestion de DataFrame en C
Auteurs : Ali Ibnou Zahir et Arthur Hacques
Rôle : Ce fichier contient les déclarations des fonctions pour gérer un DataFrame en utilisant des listes doublement chaînées.
*/

#ifndef CDATAFRAME_H
#define CDATAFRAME_H

#include "colonne.h"
#include "liste.h"

typedef LISTE CDataframe;

CDataframe* creer_dataframe_vide(int nombre_colonnes);

void supprimer_dataframe(CDataframe **cdf);

void supprimer_colonne_dataframe(CDataframe *cdf, char *nom_colonne);

int obtenir_taille_colonnes(CDataframe *cdf);

void remplir_dataframe_utilisateur(CDataframe* dataframe);

void remplir_dataframe_valeurs_predefinies(CDataframe* dataframe);

void afficher_dataframe(CDataframe* dataframe);

void afficher_lignes_partielles(CDataframe* dataframe, int limite);

void afficher_colonnes_partielles(CDataframe* dataframe, int limite);

void ajouter_ligne(CDataframe* dataframe, COL_TYPE* valeurs);

void supprimer_ligne(CDataframe* dataframe, int index);

void ajouter_colonne(CDataframe* dataframe, ENUM_TYPE type, const char* titre);

void renommer_colonne(CDataframe* dataframe, int index, const char* nouveau_titre);

int valeur_existe(CDataframe* dataframe, COL_TYPE valeur);

COL_TYPE obtenir_valeur_cellule(CDataframe* dataframe, int ligne, int col);

void definir_valeur_cellule(CDataframe* dataframe, int ligne, int col, COL_TYPE valeur);

void afficher_noms_colonnes(CDataframe* dataframe);

void afficher_nombre_lignes(CDataframe* dataframe);

void afficher_nombre_colonnes(CDataframe* dataframe);

void compter_cellules_egales_a(CDataframe* dataframe, COL_TYPE x);

void compter_cellules_superieures_a(CDataframe* dataframe, COL_TYPE x);

void compter_cellules_inferieures_a(CDataframe* dataframe, COL_TYPE x);

void effacer_index(COLONNE* col);

int verifier_index(COLONNE* col);

void mettre_a_jour_index(COLONNE* col);

int rechercher_valeur_dans_colonne(COLONNE* col, void* val);

void trier(COLONNE* col, int direction_tri);

void afficher_colonne_par_index(COLONNE* col);


#endif // CDATAFRAME_H
