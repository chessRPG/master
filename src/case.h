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

/* accesseurs */

/**
@brief renvoie la couleur de la Case passée en paramètre
@param cell pointeur sur la Case dont on veut la couleur
@return couleur de la case (CouleurCase) donnée en paramètre
*/

CouleurCase getCouleurCase(Case * cell) ;

/**
@brief renvoie l'adresse de la pièce posée sur la Case passée en paramètre (NULL si non occupée)
@param cell pointeur sur la Case dont on veut l'adresse de la pièce
@return pointeur sur la Piece posée sur la case donnée en paramètre
*/

Piece * getPieceCase(Case * cell) ;

/* mutateurs */

/**
@brief modifie la couleur de la case (CouleurCase) passée en paramètre
@param cell pointeur sur la Case à modifier
@param couleur couleur à donner à la case
@return Aucun
*/

void setCouleurCase(Case * cell, CouleurCase couleur) ;

/**
@brief modifie le pointeur sur la Piece posée sur la case
@param cell pointeur sur la Case à modifier
@param piece adresse de la nouvelle pièce à poser sur la case
@return Aucun
*/

void setPieceCase(Case * cell, Piece * piece) ;

/* création / destruction */

/**
@brief initiatilise proprement une case en faisant pointer sur NULL le pointeur sur Piece et la couleur de la case à 0
@param cell Case à initialiser
@return Aucun
*/

void initCase(Case * cell) ;

/**
@brief si la Case était occupée par une pièce, on détruit cette pièce
@param cell adresse de la Case à vider
@return Aucun
*/

void viderCase(Case * cell) ;

/**
@brief vide la Case pour la préparer à se faire détruire
@param cell adresse de la Case à vider
@return Aucun
@warning Le tableau n'est pas un tableau de pointeurs sur case mais un tableau de case, donc il ne faut pas free les cases ici
*/

void detruireCase(Case * cell) ;

/* autre */

/**
@brief renvoie vrai si les coordonnées passés en paramètres correspond à une case sur l'échiquier
@param x coordonnée en x
@param y coordonnée en y
@return booleen
*/

bool caseValide(int x, int y);


#endif

