/**

@brief Module de gestion des couleurs possibles pour les pièces
@author GONDRAS Pierre-Louis, GREYL Robin, SCHREYECK Tiffanie
@file src/couleur.c
@version 1.0
@date 2015/05/22

*/

#include "couleur.h"

const char *TabCouleur[] = {"BLANC", "NOIR", "BLEU", "JAUNE", "NULL"};

Couleur * getListeCouleurs()
{
    Couleur * liste ;
    int longueur, i ;

    longueur = NUM_COULEUR ;

    liste = malloc(sizeof(longueur*sizeof(longueur))) ;

    for(i=0; i<longueur; i++)
    {
        liste[i] = (Couleur) i ;
    }

    return liste ;
}

