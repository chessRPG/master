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
    IApiece iaPiecesJ1[16];
    IApiece iaPiecesJ2[16];

} IAjeu ;

/*  Fonction principale IA   */
void ia (Jeu * jeu);

/*  Initialisation  */
void initIAjeu(IAjeu * iaJeu, Jeu * jeu);
void initIApiece(IApiece * iaPiece, Jeu * jeu, Piece * piece);
void resetIApiece(IApiece * iaPiece);

/*  Mutateurs  */
void setNbCasesControleesIApiece(IApiece * iaPiece, int n);
void setNbPiecesControleesIApiece(IApiece * iaPiece, int n);
void setNbDeplacementsPossiblespiece(IApiece * iaPiece, int n);

void setCaseControleeIApiece(IApiece * iaPiece, Case * cell);
void setPieceControleeIApiece(IApiece * iaPiece, Piece * piece);
void setDeplacementPossibleIApiece(IApiece * iaPiece, Case * cell);

/*  Fonctions de l'IA   */
void casesPiecesControleesIApiece(IApiece * iaPiece, Jeu * jeu, int x, int y);
void deplacementsPossiblesIApiece(IApiece * iaPiece, Jeu * jeu, int x, int y);

bool pieceVulnerableIAjeu(IAjeu * iaJeu, Jeu * jeu, Piece * piece, int x, int y);
bool pieceProtegeeIAjeu(IAjeu * iaJeu, Jeu * jeu, Piece * piece, int x, int y);
Piece * joueurVulnerableIAjeu(IAjeu * iaJeu, Jeu * jeu, Joueur * joueur);

IApiece * IApieceRandom(IAjeu * iaJeu, Jeu * jeu, Joueur * joueur);
Case * deplacementRandom(IApiece * iaPiece, Jeu * jeu);
Case * deplacementPrudent(IAjeu * iaJeu, IApiece * iaPiece, Jeu * jeu);

IApiece * rechercheIApieceAttaquante(IAjeu * iaJeu, Piece * pieceVulnerable, Jeu * jeu, Joueur * joueur);

/*  Fonctions internes */
void piecesControleesIApiece(IApiece * iaPiece);
void casesControleesLigneColonneIApiece(IApiece * iaPiece, Jeu *jeu, int x, int y);
void casesControleesDiagonalesIApiece(IApiece * iaPiece, Jeu * jeu, int x, int y);
IApiece * rechercheIApiece(IAjeu * iaJeu, Piece * piece);

#endif
