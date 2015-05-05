/**

@brief Module de gestion des couleurs possibles pour les pièces
@author GONDRAS Pierre-Louis, GREYL Robin, SCHREYECK Tiffanie
@file src/couleur.h
@version 1.0
@date 2014/04/21

*/


#ifndef _COULEUR_H
#define _COULEUR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**

@struct Couleur
@brief liste des couleurs de pièces disponibles
@param enum Blanc / Noir / Bleu / Jaune : couleurs proposées \n
            num_couleur : nombre de couleurs disponibles

*/

typedef enum {BLANC, NOIR, BLEU, JAUNE, NUM_COULEUR} Couleur ;
//const char *TabCouleur[] = {"BLANC", "NOIR", "BLEU", "JAUNE", "NULL"};

Couleur * getListeCouleurs() ;

#endif
