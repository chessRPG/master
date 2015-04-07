#include "piece.h"

/* accesseurs */

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

Type getTypePiece(Piece * piece)
{
    return piece->type ;
}

Couleur getCouleurPiece(Piece * piece)
{
    return piece->couleur ;
}

int getPointsAttaque(Piece * piece)
{
    return piece->pointsAttaque ;
}

int getPointsVie(Piece * piece)
{
    return piece->pointsVie ;
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

void setPointsAttaque(Piece * piece, int pointsAttaque)
{
    piece->pointsAttaque = pointsAttaque ;
}

void setPointsVie(Piece * piece, int pointsVie)
{
    piece->pointsVie = pointsVie ;
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
