/**

@brief Module de gestion des pièces
@author GONDRAS Pierre-Louis, GREYL Robin, SCHREYECK Tiffanie
@file src/piece.c
@version 1.0
@date 2014/04/21

*/

#include "piece.h"

/* interne */

/**
@brief renvoie le nombre de points de vie initial d'une pièce d'un Type donné
@param type Type de la pièce dont on veut connaitre les points de vie initiaux
@return points de vie de la pièce de type passé en paramètre
*/

int getPointsVieMax(Type type)
{
    switch (type)
    {
    case PION:
        return 100 ;
        break ;
    case TOUR:
        return 500 ;
        break ;
    case CAVALIER:
        return 250 ;
        break ;
    case FOU:
        return 100 ;
        break ;
    case DAME:
        return 500 ;
        break ;
    case ROI:
        return 1100 ;
        break ;
    default:
        printf("type invalide") ;
        return 0 ;

    }
}

/**
@brief renvoie le nombre de points d'attaque initial d'une pièce d'un Type donné
@param type Type de la pièce dont on veut connaitre les points d'attaque initiaux
@return points d'attaque de la pièce de type passé en paramètre
*/

int getPointsAttaqueMax(Type type)
{
    switch (type)
    {
    case PION:
        return 100 ;
        break ;
    case TOUR:
        return 100 ;
        break ;
    case CAVALIER:
        return 250 ;
        break ;
    case FOU:
        return 500 ;
        break ;
    case DAME:
        return 500 ;
        break ;
    case ROI:
        return 250 ;
        break ;
    default:
        printf("type invalide") ;
        return 0 ;

    }
}

/* accesseurs */

Type getTypePiece(Piece * piece)
{
    return piece->type ;
}

Couleur getCouleurPiece(Piece * piece)
{
    if (piece == NULL) return NUM_COULEUR;
    return piece->couleur ;
}

int getPointsVie(Piece * piece)
{
    if (piece == NULL) return 0;
    return piece->pointsVie ;
}

int getPointsAttaque(Piece * piece)
{
    if (piece == NULL) return 0;
    return piece->pointsAttaque ;
}

/* mutateurs */

void setTypePiece(Piece * piece, Type type)
{
    piece->type = type ;
}

void setCouleurPiece(Piece * piece, Couleur couleur)
{
    piece->couleur = couleur ;
}

void setPointsVie(Piece * piece, int pointsVie)
{
    piece->pointsVie = pointsVie ;
}

void setPointsAttaque(Piece * piece, int pointsAttaque)
{
    piece->pointsAttaque = pointsAttaque ;
}

/* creation / destruction */



Piece * creerPiece(Type type, Couleur couleur)
{
    Piece * piece ;
    piece = malloc(sizeof(Piece)) ;
    initPiece(piece, type, couleur) ;

    return piece ;
}



void initPiece(Piece * piece, Type type, Couleur couleur)
{
    setTypePiece(piece, type) ;
    setCouleurPiece(piece, couleur) ;
    setPointsVie(piece, getPointsVieMax(type)) ;
    setPointsAttaque(piece, getPointsAttaqueMax(type)) ;
}



void detruirePiece(Piece * piece)
{
    free(piece) ;
}
