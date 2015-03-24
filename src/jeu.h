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

Joueur * getJoueurActif(Jeu * jeu);
void selectPiece(Jeu * jeu, int posX, int posY);

void setJoueurActif(Jeu * jeu, Joueur* joueur);
void deplacerPiece(Plateau * plateau, Piece * piece, int posX, int posY);

void combatPieces(Piece * pieceJ1, Piece * pieceJ2);

#endif
