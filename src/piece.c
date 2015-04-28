/**

@brief Module de gestion des joueurs
@author GONDRAS Pierre-Louis, GREYL Robin, SCHREYECK Tiffanie
@file src/piece.c
@version 1.0
@date 2014/04/21

*/

#include "piece.h"

/* accesseurs */

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

/**
@brief renvoie le type de la pièce passé en paramètre
@param type pointeur sur la Piece dont on veut le type
@return Type de la pièce
*/

Type getTypePiece(Piece * piece)
{
    return piece->type ;
}

/**
@brief renvoie la couleur de la pièce passé en paramètre
@param type pointeur sur la Piece dont on veut le Couleur
@return Couleur de la pièce
*/

Couleur getCouleurPiece(Piece * piece)
{
    return piece->couleur ;
}

/**
@brief renvoie les points d'attaque de la pièce passé en paramètre
@param type pointeur sur la Piece dont on veut les points d'attaque
@return points d'attaque de la pièce
*/


int getPointsAttaque(Piece * piece)
{
    return piece->pointsAttaque ;
}

/**
@brief renvoie les points de vie de la pièce passé en paramètre
@param type pointeur sur la Piece dont on veut les points de vie
@return points de vie de la pièce
*/

int getPointsVie(Piece * piece)
{
    return piece->pointsVie ;
}

/* mutateurs */

/**
@brief modifie le type de pièce passée en paramètre
@param piece pointeur sur la Piece à modifier
@param type Type à donner à la pièce
@return Aucun
*/

void setTypePiece(Piece * piece, Type type)
{
    piece->type = type ;
}

/**
@brief modifie la couleur de pièce passée en paramètre
@param piece pointeur sur la Piece à modifier
@param couleur Couleur à donner à la pièce
@return Aucun
*/

void setCouleurPiece(Piece * piece, Couleur couleur)
{
    piece->couleur = couleur ;
}

/**
@brief modifie les points d'attaque de pièce passée en paramètre
@param piece pointeur sur la Piece à modifier
@param pointsAttaque points d'attaque à donner à la pièce
@return Aucun
*/

void setPointsAttaque(Piece * piece, int pointsAttaque)
{
    piece->pointsAttaque = pointsAttaque ;
}

/**
@brief modifie les points de vie de pièce passée en paramètre
@param piece pointeur sur la Piece à modifier
@param pointsVie points de vie à donner à la pièce
@return Aucun
*/

void setPointsVie(Piece * piece, int pointsVie)
{
    piece->pointsVie = pointsVie ;
}

/* creation / destruction */

/**
@brief crée une structure Piece dans le tas
@param type Type à donner à la pièce crée
@param couleur Couleur à donner à la pièce crée
@return Pointeur sur la structure Piece crée
*/

Piece * creerPiece(Type type, Couleur couleur)
{
    Piece * piece ;
    piece = malloc(sizeof(Piece)) ;
    initPiece(piece, type, couleur) ;

    return piece ;
}

/**
@brief initialise la pièce passée en paramètre avec le type et la couleur donnée
@param piece pointeur sur la Piece à initialiser
@param type Type à donner à la pièce
@param couleur Couleur à donner à la pièce
@return Aucun

les points de vie et d'attaque de la pièce sont déterminés automatiquement grâce à son type
*/

void initPiece(Piece * piece, Type type, Couleur couleur)
{
    setTypePiece(piece, type) ;
    setCouleurPiece(piece, couleur) ;
    setPointsVie(piece, getPointsVieMax(type)) ;
    setPointsAttaque(piece, getPointsAttaqueMax(type)) ;
}

/**
@brief détruit la pièce passée en paramètre
@param piece pointeur sur la Piece à supprimer
@return Aucun
*/

void detruirePiece(Piece * piece)
{
    free(piece) ;
}
