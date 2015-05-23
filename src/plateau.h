/**

@brief Module de gestion du plateau
@author GONDRAS Pierre-Louis, GREYL Robin, SCHREYECK Tiffanie
@file src/plateau.h
@version 1.0
@date 2015/05/22

*/

#ifndef _PLATEAU_H
#define _PLATEAU_H

#include "case.h"


/**
@struct Plateau
@brief structure permettant de gérer le plateau de jeu ainsi que le nombre de tours écoulés
@param echiquier tableau 2D de 8*8 Cases, chaque Case correspond à une case sur l'échiquier
@param nbTours nombre de tours écoulés depuis le début de la partie (un tour = J1 joue puis J2 joue)
@see Case
*/

typedef struct
{
    Case ** echiquier ;
    int nbTours ;
} Plateau ;

/* accesseurs */

/**
@brief renvoie l'adresse de la case aux coordonnées (posY, posX) sur le plateau
@param plateau adresse du Plateau sur lequel chercher la case
@param posX ordonnée de la case
@param posY abcisse de la case
@return pointeur sur la Case de coordonnées passés en paramètres
*/

Case * getCase(Plateau * plateau, int posX, int posY) ;

/**
@brief renvoie le nombre de tours écoulés depuis le début de la partie
@param plateau adresse du Plateau de jeu
@return nombre de tours écoulés
*/

int getNbTours(Plateau * plateau) ;

/* creation / destruction */

/**
@brief met en place les cases et les pièces à partir des couleurs des joueurs
@param plateau adresse du Plateau à initialiser
@param C1 Couleur choisie par le Joueur 1
@param C2 Couleur choisie par le Joueur 2
@return Aucun
*/

void initPlateau(Plateau * plateau, Couleur C1, Couleur C2) ;

/**
@brief détruit le contenu des cases puis détruit le tableau ligne par ligne
@param plateau adresse du Plateau à détruire
@return Aucun
*/

void viderPlateau(Plateau * plateau) ;

/* autre */

/**
@brief redonne leur couleur de base (blanc / noir) aux cases du plateau
@param plateau adresse du Plateau à réinitialiser
@return Aucun
*/

void reinitCouleursEchiquier(Plateau * plateau);

#endif
