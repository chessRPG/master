/**

@brief Module de gestion des pièces
@author GONDRAS Pierre-Louis, GREYL Robin, SCHREYECK Tiffanie
@file src/piece.h
@version 1.0
@date 2014/04/21

*/


#ifndef _PIECE_H
#define _PIECE_H

#include "couleur.h"

/**

@struct Type
@brief types possibles pour chaque pièce

*/

typedef enum {PION, TOUR, CAVALIER, FOU, DAME, ROI} Type ;

/**

@struct Piece
@brief structure permettant de gérer une pièce
@param type type de la pièce, permet de connaitre ses déplacements possibles
@param couleur couleur de la pièce, permet de savoir quel joueur peut la jouer
@param pointsVie points de vie de la pièce (entiere de 100 à 1100)
@param pointsAttaque points d'attaque de la pièce (entier de 100 à 500)
@see Couleur
@see Type

*/

typedef struct
{
    Type type ;
    Couleur couleur ;
    int pointsVie ;
    int pointsAttaque ;
} Piece ;

Piece * creerPiece(Type, Couleur) ;
void initPiece(Piece *, Type, Couleur) ;

Type getTypePiece(Piece * piece) ;
Couleur getCouleurPiece(Piece * piece) ;
int getPointsVie(Piece * piece) ;
int getPointsAttaque(Piece * piece) ;

void setTypePiece(Piece * piece, Type type) ;
void setCouleurPiece(Piece * piece, Couleur couleur) ;
void setPointsVie(Piece * piece, int pointsVie) ;
void setPointsAttaque(Piece * piece, int pointsAttaque) ;

void detruirePiece(Piece * piece) ;

#endif
