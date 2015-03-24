#ifndef _JOUEUR_H
#define _JOUEUR_H

#include "couleur.h"

typedef struct
{
    char * nomJoueur ;
    Couleur couleur ;
}  Joueur;

Joueur * creerJoueur(char * nomJoueur, Couleur couleur) ;
void initJoueur(Joueur * joueur) ;
void detruireJoueur(Joueur * joueur) ;

char * getNomJoueur(Joueur * joueur) ;
Couleur getCouleurJoueur(Joueur * joueur) ;

void setNomJoueur(Joueur * joueur, char * nomJoueur) ;
void setCouleurJoueur(Joueur * joueur, Couleur couleur) ;

#endif
