/**

@brief Module de gestion des pièces
@author GONDRAS Pierre-Louis, GREYL Robin, SCHREYECK Tiffanie
@file src/piece.h
@version 1.0
@date 2015/05/22

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

typedef struct Piece Piece;

struct Piece
{
    Type type ;
    Couleur couleur ;

    int pointsVie ;
    int pointsAttaque ;

    int posX;
    int posY;

    int nbPiecesControlees;
    struct Piece * piecesControlees[8];

};

/* accesseurs */

/**
@brief renvoie le type de la pièce passé en paramètre
@param piece pointeur sur la Piece dont on veut le type
@return Type de la pièce
*/

Type getTypePiece(Piece * piece) ;

/**
@brief renvoie la couleur de la pièce passé en paramètre
@param piece pointeur sur la Piece dont on veut le Couleur
@return Couleur de la pièce
*/

Couleur getCouleurPiece(Piece * piece) ;

/**
@brief renvoie les points de vie de la pièce passé en paramètre
@param piece pointeur sur la Piece dont on veut les points de vie
@return points de vie de la pièce
*/


int getPointsVie(Piece * piece) ;

/**
@brief renvoie les points d'attaque de la pièce passé en paramètre
@param piece pointeur sur la Piece dont on veut les points d'attaque
@return points d'attaque de la pièce
*/

int getPointsAttaque(Piece * piece) ;

/* mutateurs */

/**
@brief modifie le type de pièce passée en paramètre
@param piece pointeur sur la Piece à modifier
@param type Type à donner à la pièce
@return Aucun
*/

void setTypePiece(Piece * piece, Type type) ;

/**
@brief modifie la couleur de pièce passée en paramètre
@param piece pointeur sur la Piece à modifier
@param couleur Couleur à donner à la pièce
@return Aucun
*/

void setCouleurPiece(Piece * piece, Couleur couleur) ;

/**
@brief modifie les points de vie de pièce passée en paramètre
@param piece pointeur sur la Piece à modifier
@param pointsVie points de vie à donner à la pièce
@return Aucun
*/

void setPointsVie(Piece * piece, int pointsVie) ;

/**
@brief modifie les points d'attaque de pièce passée en paramètre
@param piece pointeur sur la Piece à modifier
@param pointsAttaque points d'attaque à donner à la pièce
@return Aucun
*/

void setPointsAttaque(Piece * piece, int pointsAttaque) ;

void setPositionPiece(Piece * piece, int x, int y);

void setPieceControlee(Piece * piece, Piece * controlee);

/* création / destruction */

/**
@brief crée une structure Piece dans le tas
@param type Type à donner à la pièce crée
@param couleur Couleur à donner à la pièce crée
@return Pointeur sur la structure Piece crée
*/

Piece * creerPiece(Type, Couleur) ;

/**
@brief initialise la pièce passée en paramètre avec le type et la couleur donnée
@param piece pointeur sur la Piece à initialiser
@param type Type à donner à la pièce
@param couleur Couleur à donner à la pièce
@return Aucun

les points de vie et d'attaque de la pièce sont déterminés automatiquement grâce à son type
*/

void initPiece(Piece *, Type, Couleur) ;

/**
@brief détruit la pièce passée en paramètre
@param piece pointeur sur la Piece à supprimer
@return Aucun
*/

void detruirePiece(Piece * piece) ;

#endif
