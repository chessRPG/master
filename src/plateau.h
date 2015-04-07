#ifndef _PLATEAU_H
#define _PLATEAU_H

#include "case.h"

typedef struct
{
    Case ** echiquier ;
    int nbTours ;
} Plateau ;

Plateau * creerPlateau(Couleur C1, Couleur C2) ;
void initPlateau(Plateau * plateau, Couleur C1, Couleur C2) ;
void reinitCouleursEchiquier(Plateau * plateau);

Case * getCase(Plateau * plateau, int posX, int posY) ;
int getNbTours(Plateau * plateau) ;

void viderPlateau(Plateau * plateau) ;
void detruirePlateau(Plateau * plateau) ;

#endif
