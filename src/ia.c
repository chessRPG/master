#include "ia.h"

void ia (Jeu * jeu, Couleur * couleurGagne)
{
   // int nbTours = getNbTours(&jeu->plateau);

    int i, j, k;
    Piece * piece;

    for (i=0; i<16; i++)
    {
        piece = jeu->J2.ensPieces[i];
        if (piece != NULL)
        {
            selectPiece(jeu, piece->posX, piece->posY);
            for (j=0; j<8; j++)
                for (k=0; k<8; k++)
                    if (getCouleurCase(getCase(&jeu->plateau, j, k)) == CBLEU && (getPieceCase(getCase(&jeu->plateau, j, k)) == NULL || getCouleurPiece(getPieceCase(getCase(&jeu->plateau, j, k))) != getCouleurJoueur(&jeu->J2)))
                    {
                        deplacerPiece(jeu, piece, j, k, couleurGagne);
                        return;
                    }
        }
    }
}

void piecesControleesLigneColonne(Jeu *jeu, Piece * piece, int x, int y)
{
    int i = 1;
    while (caseValide(x-i, y) && getPieceCase(getCase(&(jeu->plateau), x-i, y)) == NULL)
        i++;
    if (caseValide(x-i, y))
        setPieceControlee(piece, getPieceCase(getCase(&(jeu->plateau), x-i, y)));

    i = 1;
    while (caseValide(x+i, y) && getPieceCase(getCase(&(jeu->plateau), x+i, y)) == NULL)
        i++;
    if (caseValide(x+i, y))
        setPieceControlee(piece, getPieceCase(getCase(&(jeu->plateau), x+i, y)));

    i = 1;
    while (caseValide(x, y-i) && getPieceCase(getCase(&(jeu->plateau), x, y-i)) == NULL)
        i++;
    if (caseValide(x, y-i))
        setPieceControlee(piece, getPieceCase(getCase(&(jeu->plateau), x, y-i)));

    i = 1;
    while (caseValide(x, y+i) && getPieceCase(getCase(&(jeu->plateau), x, y+i)) == NULL)
        i++;
    if (caseValide(x, y+i))
        setPieceControlee(piece, getPieceCase(getCase(&(jeu->plateau), x, y+i)));
}

void piecesControleesDiagonales(Jeu * jeu, Piece * piece, int x, int y)
{
    int i = 1;
    while (caseValide(x-i, y-i) && getPieceCase(getCase(&jeu->plateau, x-i, y-i)) == NULL)
        i++;
    if (caseValide(x-i, y-i))
        setPieceControlee(piece, getPieceCase(getCase(&jeu->plateau, x-i, y-i)));

    i = 1;
    while (caseValide(x-i, y+i) && getPieceCase(getCase(&jeu->plateau, x-i, y+i)) == NULL)
        i++;
    if (caseValide(x-i, y+i))
        setPieceControlee(piece, getPieceCase(getCase(&jeu->plateau, x-i, y+i)));

    i = 1;
    while (caseValide(x+i, y-i) && getPieceCase(getCase(&jeu->plateau, x+i, y-i)) == NULL)
        i++;
    if (caseValide(x+i, y-i))
        setPieceControlee(piece, getPieceCase(getCase(&jeu->plateau, x+i, y-i)));

    i = 1;
    while (caseValide(x+i, y+i) && getPieceCase(getCase(&jeu->plateau, x+i, y+i)) == NULL)
        i++;
    if (caseValide(x+i, y+i))
        setPieceControlee(piece, getPieceCase(getCase(&jeu->plateau, x+i, y+i)));
}

void piecesControlees(Jeu * jeu, Piece * piece)
{
    Couleur couleur = getCouleurPiece(piece);
    int a, i, j;
    int x = piece->posX;
    int y = piece->posY;

    switch(piece->type)
    {
        case PION:
            if (couleur == getCouleurJoueur(&jeu->J1))  a = -1;
            else    a = 1;

            if (caseValide(x+a, y-1) && getPieceCase(getCase(&(jeu->plateau), x+a, y-1)) != NULL)
                setPieceControlee(piece, getPieceCase(getCase(&(jeu->plateau), x+a, y-1)));
            if (caseValide(x+a, y+1) && getPieceCase(getCase(&(jeu->plateau), x+a, y+1)) != NULL)
                setPieceControlee(piece, getPieceCase(getCase(&(jeu->plateau), x+a, y+1)));
            break;

        case TOUR:
            piecesControleesLigneColonne(jeu, piece, x, y);
            break;

        case CAVALIER:
            if (caseValide(x-2, y-1) && getPieceCase(getCase(&(jeu->plateau), x-2, y-1)) != NULL)
                setPieceControlee(piece, getPieceCase(getCase(&(jeu->plateau), x-2, y-1)));
            if (caseValide(x-2, y+1) && getPieceCase(getCase(&(jeu->plateau), x-2, y+1)) != NULL)
                setPieceControlee(piece, getPieceCase(getCase(&(jeu->plateau), x-2, y+1)));
            if (caseValide(x-1, y-2) && getPieceCase(getCase(&(jeu->plateau), x-1, y-2)) != NULL)
                setPieceControlee(piece, getPieceCase(getCase(&(jeu->plateau), x-1, y-2)));
            if (caseValide(x-1, y+2) && getPieceCase(getCase(&(jeu->plateau), x-1, y+2)) != NULL)
                setPieceControlee(piece, getPieceCase(getCase(&(jeu->plateau), x-1, y+2)));
            if (caseValide(x+1, y-2) && getPieceCase(getCase(&(jeu->plateau), x+1, y-2)) != NULL)
                setPieceControlee(piece, getPieceCase(getCase(&(jeu->plateau), x+1, y-2)));
            if (caseValide(x+1, y+2) && getPieceCase(getCase(&(jeu->plateau), x+1, y+2)) != NULL)
                setPieceControlee(piece, getPieceCase(getCase(&(jeu->plateau), x+1, y+2)));
            if (caseValide(x+2, y-1) && getPieceCase(getCase(&(jeu->plateau), x+2, y-1)) != NULL)
                setPieceControlee(piece, getPieceCase(getCase(&(jeu->plateau), x+2, y-1)));
            if (caseValide(x+2, y+1) && getPieceCase(getCase(&(jeu->plateau), x+2, y+1)) != NULL)
                setPieceControlee(piece, getPieceCase(getCase(&(jeu->plateau), x+2, y+1)));
            break;

        case FOU:
            piecesControleesDiagonales(jeu, piece, x, y);
            break;

        case DAME:
            piecesControleesLigneColonne(jeu, piece, x, y);
            piecesControleesDiagonales(jeu, piece, x, y);
            break;

        case ROI:
            for (i = x-1 ; i<x+2 ; i++)
            {
                for (j = y-1; j<y+2; j++)
                {
                    if (caseValide(i, j) && getPieceCase(getCase(&(jeu->plateau), i, j)) != NULL)
                        setPieceControlee(piece, getPieceCase(getCase(&(jeu->plateau), i, j)));
                }
            }
            break;

        default:
            break;
    }
}
