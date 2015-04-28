#include <stdbool.h>
#include "case.h"

/* accesseurs */

/**
@brief renvoie la couleur de la Case passée en paramètre
@param cell pointeur sur la Case dont on veut la couleur
@return couleur de la case (CouleurCase) donnée en paramètre
*/

CouleurCase getCouleurCase(Case * cell)
{
    return cell->couleurCase ;
}

/**
@brief renvoie l'adresse de la pièce posée sur la Case passée en paramètre (NULL si non occupée)
@param cell pointeur sur la Case dont on veut l'adresse de la pièce
@return pointeur sur la Piece posée sur la case donnée en paramètre
*/

Piece * getPieceCase(Case * cell)
{
    return cell->piece ;
}

/* mutateurs */

/**
@brief modifie la couleur de la case (CouleurCase) passée en paramètre
@param cell pointeur sur la Case à modifier
@param couleur couleur à donner à la case
@return Aucun
*/

void setCouleurCase(Case * cell, CouleurCase couleur)
{
    cell->couleurCase = couleur ;
}

/**
@brief modifie le pointeur sur la Piece posée sur la case
@param cell pointeur sur la Case à modifier
@param piece adresse de la nouvelle pièce à poser sur la case
@return Aucun
*/

void setPieceCase(Case * cell, Piece * piece)
{
    cell->piece = piece ;
}

/* creation / destruction */

/**
@brief initiatilise proprement une case en faisant pointer sur NULL le pointeur sur Piece et la couleur de la case à 0
@param cell Case à initialiser
@return Aucun
*/

void initCase(Case * cell)
{
    cell->piece = NULL ;
    cell->couleurCase = 0 ;
}

/**
@brief si la Case était occupée par une pièce, on détruit cette pièce
@param cell adresse de la case à vider
@return Aucun
*/

void viderCase(Case * cell)
{
    Piece * piece = getPieceCase(cell) ;
    if (piece != NULL)
    {
        detruirePiece(piece) ;
        setPieceCase(cell, NULL) ;
    }
}

/**
@brief vide la Case pour la préparer à se faire détruire
@param cell adresse de la case à vider
@return Aucun
@warning Le tableau n'est pas un tableau de pointeurs sur case mais un tableau de case, donc il ne faut pas free les cases ici
*/

void detruireCase(Case * cell)
{
    viderCase(cell) ;
}

/*  autre   */

/**
@brief renvoie vrai si les coordonnées passés en paramètres correspond à une case sur l'échiquier
@param x coordonnée en x
@param y coordonnée en y
@return booleen
*/

bool caseValide(int x, int y)
{
    if (x<8 && x>=0 && y<8 && y>=0)
        return true;
    else
        return false;
}
