/**

@brief Module de gestion des joueurs
@author GONDRAS Pierre-Louis, GREYL Robin, SCHREYECK Tiffanie
@file src/joueur.h
@version 1.0
@date 2014/04/21

*/

#ifndef _JOUEUR_H
#define _JOUEUR_H

#include "couleur.h"

/**

@struct Joueur
@brief structure stockant le nom du joueur et la couleur des pièces choisie
@param nomJoueur chaine de 32 caractères stockant le nom du joueur
@param couleur Couleur choisie par le joueur
@see Joueur

*/

typedef struct
{
    char nomJoueur[32] ;
    Couleur couleur ;
}  Joueur;

void initJoueur(Joueur * joueur, Couleur couleur) ;

char * getNomJoueur(Joueur * joueur) ;
Couleur getCouleurJoueur(Joueur * joueur) ;

void setNomJoueur(Joueur * joueur, char * nomJoueur) ;
void setCouleurJoueur(Joueur * joueur, Couleur couleur) ;

#endif
