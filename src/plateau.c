#include "plateau.h"

/* accesseurs */

Case * getCase(Plateau * plateau, int posX, int posY)
{
    return plateau->echiquier[posX][posY] ;
}

int getNbTours(Plateau * plateau)
{
    return plateau->nbTours ;
}

/* creation / destruction */

void initPlateau(Plateau * plateau, Couleur C1, Couleur C2)
{
    int i, j ;

    for(i = 0 ; i < 8 ; i++)
    {
        for(j = 0 ; j < 8 ; j++)
        {
            plateau->echiquier[i][j] = NULL ;
        }
    }

    setPieceCase(plateau->echiquier[0][0], creerPiece(TOUR, C1)) ;
    setPieceCase(plateau->echiquier[1][0], creerPiece(CAVALIER, C1)) ;
    setPieceCase(plateau->echiquier[2][0], creerPiece(FOU, C1)) ;
    setPieceCase(plateau->echiquier[3][0], creerPiece(DAME, C1)) ;
    setPieceCase(plateau->echiquier[4][0], creerPiece(ROI, C1)) ;
    setPieceCase(plateau->echiquier[5][0], creerPiece(FOU, C1)) ;
    setPieceCase(plateau->echiquier[6][0], creerPiece(CAVALIER, C1)) ;
    setPieceCase(plateau->echiquier[7][0], creerPiece(TOUR, C1)) ;

    for(i = 0 ; i < 8 ; i++)
    {
        setPieceCase(plateau->echiquier[i][1], creerPiece(PION, C1)) ;
    }

    setPieceCase(plateau->echiquier[7][7], creerPiece(TOUR, C2)) ;
    setPieceCase(plateau->echiquier[6][7], creerPiece(CAVALIER, C2)) ;
    setPieceCase(plateau->echiquier[5][7], creerPiece(FOU, C2)) ;
    setPieceCase(plateau->echiquier[4][7], creerPiece(DAME, C2)) ;
    setPieceCase(plateau->echiquier[3][7], creerPiece(ROI, C2)) ;
    setPieceCase(plateau->echiquier[2][7], creerPiece(FOU, C2)) ;
    setPieceCase(plateau->echiquier[1][7], creerPiece(CAVALIER, C2)) ;
    setPieceCase(plateau->echiquier[0][7], creerPiece(TOUR, C2)) ;

    for(i = 0 ; i < 8 ; i++)
    {
        setPieceCase(plateau->echiquier[i][6], creerPiece(PION, C2)) ;
    }

    plateau->nbTours = 0 ;
}

Plateau * creerPlateau(Couleur C1, Couleur C2)
{
    Plateau * plateau ;
    int i, j ;

    plateau = malloc(sizeof(Plateau)) ;
    plateau->echiquier = malloc(8*8*sizeof(Case)) ;

    for(i = 0 ; i < 8 ; i++)
    {
        for(j = 0 ; j < 8 ; j++)
        {
            plateau->echiquier[i][j] = creerCase((i+j)%2) ;
        }
    }

    //initPlateau(plateau, C1, C2) ;

    return plateau ;
}

void viderPlateau(Plateau * plateau)
{
    int i, j ;

    for(i = 0 ; i < 8 ; i++)
    {
        for(j = 0 ; j < 8 ; j++)
        {
            detruireCase(plateau->echiquier[i][j]) ;
        }
    }
}

void detruirePlateau(Plateau * plateau)
{
    viderPlateau(plateau) ;
    free(plateau) ;
}
















