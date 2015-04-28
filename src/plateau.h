/**

@brief Module de gestion du plateau
@author GONDRAS Pierre-Louis, GREYL Robin, SCHREYECK Tiffanie
@file src/plateau.h
@version 1.0
@date 2014/04/21

*/

#ifndef _PLATEAU_H
#define _PLATEAU_H

#include "case.h"

/**

@struct Plateau
@brief structure permettant de gérer le plateau de jeu ainsi que le nombre de tours écoulés
@param echiquier tableau de 8*8 Cases, chaque case est une case sur l'échiquier
@param nbTours nombre de tours écoulés depuis le début de la partie (un tour = J1 joue puis J2 joue)
@see Case

*/

typedef struct
{
    Case ** echiquier ;
    int nbTours ;
} Plateau ;

void initPlateau(Plateau * plateau, Couleur C1, Couleur C2) ;
void reinitCouleursEchiquier(Plateau * plateau);

Case * getCase(Plateau * plateau, int posX, int posY) ;
int getNbTours(Plateau * plateau) ;

void viderPlateau(Plateau * plateau) ;

#endif
