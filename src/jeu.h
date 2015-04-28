/**

@brief Module de gestion du jeu, module principal du programme
@author GONDRAS Pierre-Louis, GREYL Robin, SCHREYECK Tiffanie
@file src/jeu.h
@version 1.0
@date 2014/04/21

*/

#ifndef _JEU_H
#define _JEU_H

#include "joueur.h"
#include "plateau.h"

/**

@struct Jeu
@brief Structure permettant de gérer le plateau de jeu et les joueurs
@param plateau structure Plateau qui permet de gérer une partie
@param J1 structure Joueur contenant le nom et la couleur des pièces du joueur 1
@param J2 structure Joueur contenant le nom et la couleur des pièces du joueur 2
@param joueurActif pointeur sur Joueur permettant d'accéder rapidement au joueur actif
@see Joueur
@see Plateau

*/

typedef struct
{
    Plateau plateau ;
    Joueur J1 ;
    Joueur J2 ;
    Joueur * joueurActif ;
} Jeu ;

void initJeu(Jeu * jeu, char * piecesJ1, char * piecesJ2);
void detruireJeu(Jeu * jeu);

Joueur * getJoueurActif(Jeu * jeu);
Joueur * getJoueurInactif(Jeu * jeu);
void setJoueurActif(Jeu * jeu, Joueur* joueur);

void selectPiece(Jeu * jeu, int posX, int posY);
void deplacerPiece(Plateau * plateau, Piece * piece, int posX, int posY, Couleur * couleurGagne);

Piece * combatPieces(Piece * pieceAtt, Piece * pieceDef, Couleur * couleurGagne);

#endif
