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

/* accesseurs */

/**
@brief renvoie l'adresse du joueur actif
@param jeu adresse du Jeu courant
@return adresse du Joueur actif
*/

Joueur * getJoueurActif(Jeu * jeu);

/**
@brief renvoie l'adresse du joueur inactif
@param jeu adresse du Jeu courant
@return adresse du Joueur inactif
*/

Joueur * getJoueurInactif(Jeu * jeu);

/* mutateurs */

/**
@brief modifie l'adresse contenue dans joueurActif
@param jeu adresse du Jeu courant
@param joueur adresse du Joueur qui devient le joueur actif
@return Aucun
*/

void setJoueurActif(Jeu * jeu, Joueur* joueur);

/* création / destruction */

/**
@brief initialise les joueurs, le plateau, et donne la main au joueur 1
@param jeu adresse du Jeu à initialiser
@param piecesJ1 chemin d'accès des pièces du Joueur 1
@param piecesJ2 chemin d'accès des pièces du Joueur 2
@return Aucun
*/

void initJeu(Jeu * jeu, char * piecesJ1, char * piecesJ2, char * log);

/**
@brief remet le joueur actif à NULL et détruit le plateau
@param jeu adresse du Jeu à détruire
@return Aucun
*/


void detruireJeu(Jeu * jeu);

/* fonctions de jeu */

/**
@brief selectionne une pièce et affiche les cases où elle peut se rendre
@param jeu adresse du Jeu courant
@param posX ordonnée de la Piece sélectionnée
@param posY abscisse de la Piece sélectionnée
@return Aucun
*/

void selectPiece(Jeu * jeu, int posX, int posY);

/**
@brief déplace la pièce sélectionnée à la position (y,x) et déclenche un combat si la case est occupée
@param plateau adresse du Plateau de jeu
@param piece adresse de la Piece à déplacer
@param posX abscisse de la Case d'arrivée
@param posY ordonnée de la Case d'arrivée
@param couleurGagne adresse de la couleur gagnante si un combat se déclenche
@see combatPieces
@return Aucun
*/

void deplacerPiece(Jeu * jeu, Piece * piece, int posX, int posY, Couleur * couleurGagne, char * log);

/**
@brief fait combattre les deux pièces passées en paramètre et détruit la pièce perdante
@param pieceAtt adresse de la Piece attaquante
@param pieceDef adresse de la Piece en défense
@param couleurGagne contient la Couleur de la Piece qui a gagné le combat à la fin de la fonction
@return adresse de la Piece qui gagne le combat
*/

Piece * combatPieces(Jeu * jeu, Piece * pieceAtt, Piece * pieceDef, Couleur * couleurGagne, char * log);

/* autre */

/**
@brief convertit un entier en chaine de caractères
@param n entier à convertir
@param s chaine de caractère contenant les caractères de n à la fin de la fonction
@return Aucun
*/

void itoa(int n, char s[]) ;

/**
@brief renverse la chaine de caractère passée en paramètre
@param s chaine à renverser
@return Aucun
*/

void reverse(char s []);

#endif
