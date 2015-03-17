#ifndef _PIECE_H
#define _PIECE_H

#include "couleur.h"

typedef enum {PION, TOUR, CAVALIER, FOU, DAME, ROI} Type ;

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
