#include "case.h"

/* accesseurs */

/* mutateurs */

/* creation / destruction */

void initCase(Case * cell)
{
    cell->piece = NULL ;
    cell->couleurCase = NULL ;
}

Case * creerCase(CouleurCase couleurCase)
{
    Case * cell ;
    cell = malloc(sizeof(Case)) ;

    initCase(cell, couleurCase) ;

    cell->couleurCase = couleurCase ;


    return cell ;
}

void viderCase(Case * cell)
{
    Piece * piece = getPieceCase(cell) ;
    if (piece != NULL)
    {
        detruirePiece(piece) ;
        setPieceCase(cell, NULL) ;
    }
}

void detruireCase(Case * cell)
{
    viderCase(cell) ;
    free(cell) ;
}
