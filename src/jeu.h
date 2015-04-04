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
void reinitCouleursEchiquier(Plateau * plateau);

Joueur * getJoueurActif(Jeu * jeu);
void setJoueurActif(Jeu * jeu, Joueur* joueur);

void selectPiece(Jeu * jeu, int posX, int posY);
void deplacerPiece(Plateau * plateau, Piece * piece, int posX, int posY);

void combatPieces(Joueur * joueurActif, Piece * pieceJ1, Piece * pieceJ2);

#endif
