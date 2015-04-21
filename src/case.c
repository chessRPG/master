#include <stdbool.h>
#include "case.h"

/* accesseurs */

CouleurCase getCouleurCase(Case * cell)
{
    return cell->couleurCase ;
}

Piece * getPieceCase(Case * cell)
{
    return cell->piece ;
}

/* mutateurs */

void setCouleurCase(Case * cell, CouleurCase couleur)
{
    cell->couleurCase = couleur ;
}

void setPieceCase(Case * cell, Piece * piece)
{
    cell->piece = piece ;
}

/* creation / destruction */

void initCase(Case * cell)
{
    cell->piece = NULL ;
    cell->couleurCase = 0 ;
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
}

/*  autre   */

bool caseValide(int x, int y)
{
    if (x<8 && x>=0 && y<8 && y>=0)
        return true;
    else
        return false;
}
