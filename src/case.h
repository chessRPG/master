#ifndef _CASE_H
#define _CASE_H

#include <stdbool.h>
#include "piece.h"

typedef enum {CBLANC, CNOIR, CBLEU} CouleurCase ;

typedef struct
{
    CouleurCase couleurCase ;
    Piece * piece ;
} Case ;

Case * creerCase(CouleurCase couleurCase) ;
void initCase(Case * cell) ;

CouleurCase getCouleurCase(Case * cell) ;
Piece * getPieceCase(Case * cell) ;

void setCouleurCase(Case * cell, CouleurCase couleur) ;
void setPieceCase(Case * cell, Piece * piece) ;

void viderCase(Case * cell) ;
void detruireCase(Case * cell) ;

bool caseValide(int x, int y);


#endif

