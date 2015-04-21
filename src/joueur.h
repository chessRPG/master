#ifndef _JOUEUR_H
#define _JOUEUR_H

#include "couleur.h"

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
