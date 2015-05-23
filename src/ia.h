#ifndef _IA_H
#define _IA_H

#include <stdlib.h>
#include <time.h>

#include "jeu.h"

typedef struct
{
    Piece * piece;

    int nbCasesControlees;
    Case * casesControlees[27];

    int nbPiecesControlees;
    Piece * piecesControlees[8];

    int nbDeplacementsPossibles;
    Case * deplacementsPossibles[27];

} IApiece ;

typedef struct
{
    int nbPiecesJeu;
    IApiece iaPiece[32];

} IAjeu ;

/*  Fonction principale IA   */
void ia (Jeu * jeu);

/*  Initialisation  */
void initIApiece(IApiece * iaPieces, Piece * piece);
void initIAjeu(IAjeu * iaJeu, Jeu * jeu);

/*  Accesseurs  */
void setNbCasesControleesIApiece(IApiece * iaPiece, int n);
void setNbPiecesControleesIApiece(IApiece * iaPiece, int n);
void setNbDeplacementsPossiblespiece(IApiece * iaPiece, int n);

void setCaseControleeIApiece(IApiece * iaPiece, Case * cell);
void setPieceControleeIApiece(IApiece * iaPiece, Piece * piece);
void setDeplacementPossibleIApiece(IApiece * iaPiece, Case * cell);

/*  Fonctions de l'IA   */
void casesPiecesControleesIApiece(IApiece * iaPiece, Jeu * jeu, int x, int y);
void deplacementsPossiblesIApiece(IApiece * iaPiece, Jeu * jeu, int x, int y);

void coloreCasesControleesIApiece(IApiece * iaPiece);
void colorePiecesControlees(IApiece * iaPiece, Jeu * jeu);
void coloreDeplacementsPossiblesIApiece(IApiece * iaPiece);

/*  Fonctions internes */
void piecesControleesIApiece(IApiece * iaPiece, int x, int y);
void casesControleesLigneColonneIApiece(IApiece * iaPiece, Jeu *jeu, int x, int y);
void casesControleesDiagonalesIApiece(IApiece * iaPiece, Jeu * jeu, int x, int y);

#endif
