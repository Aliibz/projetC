/*
Nom du projet : Gestion de DataFrame en C
Auteurs : Ali Ibnou Zahir et Arthur Hacques
Rôle : Ce fichier contient les fonctions pour gerer une liste doublement chaînee.
*/

#include "liste.h"
#include <stdlib.h>

/* Cree un noeud de liste avec les donnees specifiees */
noeud* liste_creer_noeud(void *data) {
    noeud *node = (noeud *)malloc(sizeof(noeud));
    node->data = data;
    node->precedent = NULL;
    node->suivant = NULL;
    return node;
}

/* Cree une nouvelle liste */
LISTE* liste_creer_liste() {
    LISTE *list = (LISTE *)malloc(sizeof(LISTE));
    list->tete = NULL;
    list->queue = NULL;
    return list;
}

/* Supprime une liste et libere la memoire associee */
void liste_supprimer_liste(LISTE *list) {
    while (list->tete != NULL) {
        liste_supprimer_tete(list);
    }
    free(list);
}

/* Insere un noeud en tête de liste */
void liste_inserer_tete(LISTE *list, noeud *node) {
    if (list->tete == NULL) {
        list->tete = node;
        list->queue = node;
    } else {
        node->suivant = list->tete;
        list->tete->precedent = node;
        list->tete = node;
    }
}

/* Insere un noeud en queue de liste */
void liste_inserer_queue(LISTE *list, noeud *node) {
    if (list->queue == NULL) {
        list->tete = node;
        list->queue = node;
    } else {
        node->precedent = list->queue;
        list->queue->suivant = node;
        list->queue = node;
    }
}

/* Insere un noeud apres un noeud specifique */
void liste_inserer_apres(LISTE *list, noeud *node, noeud *apres) {
    if (apres == list->queue) {
        liste_inserer_queue(list, node);
    } else {
        node->suivant = apres->suivant;
        node->precedent = apres;
        apres->suivant->precedent = node;
        apres->suivant = node;
    }
}

/* Supprime le noeud en tête de liste */
void liste_supprimer_tete(LISTE *list) {
    if (list->tete != NULL) {
        noeud *node = list->tete;
        list->tete = list->tete->suivant;
        if (list->tete != NULL) {
            list->tete->precedent = NULL;
        } else {
            list->queue = NULL;
        }
        free(node);
    }
}

/* Supprime le noeud en queue de liste */
void liste_supprimer_queue(LISTE *list) {
    if (list->queue != NULL) {
        noeud *node = list->queue;
        list->queue = list->queue->precedent;
        if (list->queue != NULL) {
            list->queue->suivant = NULL;
        } else {
            list->tete = NULL;
        }
        free(node);
    }
}

/* Supprime un noeud specifique de la liste */
void liste_supprimer_noeud(LISTE *list, noeud *node) {
    if (node == list->tete) {
        liste_supprimer_tete(list);
    } else if (node == list->queue) {
        liste_supprimer_queue(list);
    } else {
        node->precedent->suivant = node->suivant;
        node->suivant->precedent = node->precedent;
        free(node);
    }
}

/* Efface tous les noeuds de la liste */
void liste_effacer(LISTE *list) {
    while (list->tete != NULL) {
        liste_supprimer_tete(list);
    }
}

/* Retourne le premier noeud de la liste */
noeud* obtenir_premier_noeud(LISTE *list) {
    return list->tete;
}

/* Retourne le dernier noeud de la liste */
noeud* obtenir_dernier_noeud(LISTE *list) {
    return list->queue;
}

/* Retourne le noeud suivant dans la liste */
noeud* obtenir_noeud_suivant(LISTE *list, noeud *node) {
    return node->suivant;
}

/* Retourne le noeud precedent dans la liste */
noeud* obtenir_noeud_precedent(LISTE *list, noeud *node) {
    return node->precedent;
}
