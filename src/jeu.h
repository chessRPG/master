#ifndef _JEU_H
#define _JEU_H

#include "joueur.h"
#include "plateau.h"

typedef struct
{
    Plateau plateau ;
    Joueur J1 ;
    Joueur J2 ;
    Joueur * joueurActif ;
} Jeu ;

void initJeu(Jeu * jeu, Couleur C1, Couleur C2);
void detruireJeu(Jeu * jeu);

Joueur * getJoueurActif(Jeu * jeu);
Joueur * getJoueurInactif(Jeu * jeu);
void setJoueurActif(Jeu * jeu, Joueur* joueur);

void selectPiece(Jeu * jeu, int posX, int posY);
void deplacerPiece(Plateau * plateau, Piece * piece, int posX, int posY, Couleur * couleurGagne);

Piece * combatPieces(Piece * pieceAtt, Piece * pieceDef, Couleur * couleurGagne);

#endif
