/*
Nom du projet : Gestion de DataFrame en C
Auteurs : Ali Ibnou Zahir et Arthur Hacques
Rôle : Ce fichier contient les déclarations des fonctions pour gérer une liste doublement chaînée.
*/

#ifndef LISTE_H
#define LISTE_H

typedef struct noeud {
    void *data;
    struct noeud *precedent;
    struct noeud *suivant;
} noeud;

typedef struct liste_ {
    noeud *tete;
    noeud *queue;
} LISTE;

noeud* liste_creer_noeud(void *data);

LISTE* liste_creer_liste();

void liste_supprimer_liste(LISTE *list);

void liste_inserer_tete(LISTE *list, noeud *node);

void liste_inserer_queue(LISTE *list, noeud *node);

void liste_inserer_apres(LISTE *list, noeud *node, noeud *apres);

void liste_supprimer_tete(LISTE *list);

void liste_supprimer_queue(LISTE *list);

void liste_supprimer_noeud(LISTE *list, noeud *node);

void liste_effacer(LISTE *list);

noeud* obtenir_premier_noeud(LISTE *list);

noeud* obtenir_dernier_noeud(LISTE *list);

noeud* obtenir_noeud_suivant(LISTE *list, noeud *node);

noeud* obtenir_noeud_precedent(LISTE *list, noeud *node);


#endif // LISTE_H
