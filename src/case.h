/**

@brief Module de gestion des cases
@author GONDRAS Pierre-Louis, GREYL Robin, SCHREYECK Tiffanie
@file src/case.h
@version 1.0
@date 2014/04/21

*/


#ifndef _CASE_H
#define _CASE_H

#include <stdbool.h>
#include "piece.h"

/**

@struct CouleurCase
@brief couleurs possibles pour les cases
@param enum Blanc / Noir : damier habituel \n
            Rouge : case pointée par le curseur de la souris \n
            Bleu : case où il est possible de se déplacer

*/

typedef enum {CBLANC, CNOIR, CBLEU, CROUGE} CouleurCase ;

/**

@struct Case
@brief structure permettant de gérer une case
@param couleurCase couleur actuelle de la case
@param piece pointeur sur la pièce posée dans la case, NULL si aucune pièce
@see CouleurCase
@see Piece

*/

typedef struct
{
    CouleurCase couleurCase ;
    Piece * piece ;
} Case ;

void initCase(Case * cell) ;

CouleurCase getCouleurCase(Case * cell) ;
Piece * getPieceCase(Case * cell) ;

void setCouleurCase(Case * cell, CouleurCase couleur) ;
void setPieceCase(Case * cell, Piece * piece) ;

void viderCase(Case * cell) ;
void detruireCase(Case * cell) ;

bool caseValide(int x, int y);


#endif

