#include "plateau.h"

/* accesseurs */

Case * getCase(Plateau * plateau, int posX, int posY)
{
    return &(plateau->echiquier[posX][posY]) ;
}

int getNbTours(Plateau * plateau)
{
    return plateau->nbTours ;
}

/* creation / destruction */

void initPlateau(Plateau * plateau, Couleur C1, Couleur C2)
{
    int i, j ;

    plateau->echiquier = malloc(8*sizeof(Case *)) ;

    for(i = 0 ; i<8; i++ )
    {
        plateau->echiquier[i] = malloc(8*sizeof(Case));
    }


    for(i = 0 ; i < 8 ; i++)
    {
        for(j = 0 ; j < 8 ; j++)
        {
            initCase(&(plateau->echiquier[i][j]));
        }
    }

    setPieceCase(&(plateau->echiquier[0][0]), creerPiece(TOUR, C2)) ;
    setPieceCase(&(plateau->echiquier[0][1]), creerPiece(CAVALIER, C2)) ;
    setPieceCase(&(plateau->echiquier[0][2]), creerPiece(FOU, C2)) ;
    setPieceCase(&(plateau->echiquier[0][3]), creerPiece(DAME, C2)) ;
    setPieceCase(&(plateau->echiquier[0][4]), creerPiece(ROI, C2)) ;
    setPieceCase(&(plateau->echiquier[0][5]), creerPiece(FOU, C2)) ;
    setPieceCase(&(plateau->echiquier[0][6]), creerPiece(CAVALIER, C2)) ;
    setPieceCase(&(plateau->echiquier[0][7]), creerPiece(TOUR, C2)) ;

    for(i = 0 ; i < 8 ; i++)
    {
        setPieceCase(&(plateau->echiquier[1][i]), creerPiece(PION, C2)) ;
    }

    setPieceCase(&(plateau->echiquier[7][7]), creerPiece(TOUR, C1)) ;
    setPieceCase(&(plateau->echiquier[7][6]), creerPiece(CAVALIER, C1)) ;
    setPieceCase(&(plateau->echiquier[7][5]), creerPiece(FOU, C1)) ;
    setPieceCase(&(plateau->echiquier[7][4]), creerPiece(ROI, C1)) ;
    setPieceCase(&(plateau->echiquier[7][3]), creerPiece(DAME, C1)) ;
    setPieceCase(&(plateau->echiquier[7][2]), creerPiece(FOU, C1)) ;
    setPieceCase(&(plateau->echiquier[7][1]), creerPiece(CAVALIER, C1)) ;
    setPieceCase(&(plateau->echiquier[7][0]), creerPiece(TOUR, C1)) ;

    for(i = 0 ; i < 8 ; i++)
    {
        setPieceCase(&(plateau->echiquier[6][i]), creerPiece(PION, C1)) ;
    }

    plateau->nbTours = 0 ;
}

Plateau * creerPlateau(Couleur C1, Couleur C2)
{
    Plateau * plateau ;

    plateau = malloc(sizeof(Plateau)) ;

    initPlateau(plateau, C1, C2) ;

    return plateau ;
}

void viderPlateau(Plateau * plateau)
{
    int i, j ;

    for(i = 0 ; i < 8 ; i++)
    {
        for(j = 0 ; j < 8 ; j++)
        {
            detruireCase(&(plateau->echiquier[i][j])) ;
        }
    }
}

void detruirePlateau(Plateau * plateau)
{
    viderPlateau(plateau) ;
    free(plateau) ;
}
