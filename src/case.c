#include "case.h"

/* accesseurs */

/* mutateurs */

/* creation / destruction */

void initCase(Case * cell, CouleurCase couleurCase)
{
    cell->couleurCase = couleurCase ;
    cell->piece = NULL ;
}

Case * creerCase(CouleurCase couleurCase)
{
    Case * cell ;
    cell = malloc(sizeof(Case)) ;
    initCase(cell, couleurCase) ;

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
