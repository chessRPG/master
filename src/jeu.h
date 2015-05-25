/**

@brief Module de gestion du jeu, module principal du programme
@author GONDRAS Pierre-Louis, GREYL Robin, SCHREYECK Tiffanie
@file src/jeu.h
@version 1.0
@date 2015/05/22

*/

#ifndef _JEU_H
#define _JEU_H

#include "joueur.h"
#include "plateau.h"

/**
@struct TypeJeu
@param enum SOLO : partie contre l'ordinateur \n
            MULTI : partie à 2 joueurs
*/

typedef enum {SOLO, MULTI} TypeJeu;

/**

@struct Jeu
@brief Structure permettant de gérer le plateau de jeu et les joueurs
@param plateau structure Plateau qui permet de gérer une partie
@param J1 structure Joueur contenant le nom et la couleur des pièces du joueur 1
@param J2 structure Joueur contenant le nom et la couleur des pièces du joueur 2
@param joueurActif pointeur sur Joueur permettant d'accéder rapidement au joueur actif
@param log chaine de caractères utilisée pour stocker et afficher les logs
@param typeJeu type du jeu en cours (solo / multi)
@param couleurGagnant vaut le numéro de la couleur du gagnant (-1 sinon)
@see Joueur
@see Plateau
@see Couleur
@see TypeJeu

*/

typedef struct
{
    Plateau plateau ;
    Joueur J1 ;
    Joueur J2 ;
    Joueur * joueurActif ;
    char log[1000];
    TypeJeu typeJeu;
    Couleur couleurGagnant;
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

/**
@brief renvoie le type de jeu en cours
@param jeu adresse du Jeu courant
@return TypeJeu type de jeu en cours
*/


TypeJeu getTypeJeu(Jeu * jeu);

/* mutateurs */

/**
@brief modifie l'adresse contenue dans joueurActif
@param jeu adresse du Jeu courant
@param joueur adresse du Joueur qui devient le joueur actif
@return Aucun
*/

void setJoueurActif(Jeu * jeu, Joueur* joueur);

/**
@brief modifie le type du jeu (solo / multi)
@param jeu adresse du Jeu courant
@param type TypeJeu, type à attribuer au jeu
@return Aucun
*/


void setTypeJeu(Jeu * jeu, TypeJeu type);

/**
@brief attribue une valeur correspondante à la couleur du gagnant lorsqu'il y en a un
@param jeu adresse du Jeu courant
@param couleur Couleur gagnante
@return Aucun
*/


void setCouleurGagnant(Jeu * jeu, Couleur couleur);

/* création / destruction */

/**
@brief initialise les joueurs, le plateau, et donne la main au joueur 1
@param jeu adresse du Jeu à initialiser
@param piecesJ1 chemin d'accès des pièces du Joueur 1
@param piecesJ2 chemin d'accès des pièces du Joueur 2
@return Aucun
*/

void initJeu(Jeu * jeu, char * nom1, char * nom2, Couleur C1, Couleur C2);

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
@param jeu adresse du Jeu (utilisée pour accéder au plateau et écrire dans log)
@param piece adresse de la Piece à déplacer
@param posX abscisse de la Case d'arrivée
@param posY ordonnée de la Case d'arrivée
@param couleurGagne adresse de la couleur gagnante si un combat se déclenche
@see combatPieces
@return Aucun
*/

void deplacerPiece(Jeu * jeu, Piece * piece, int posX, int posY);

/**
@brief fait combattre les deux pièces passées en paramètre et détruit la pièce perdante
@param jeu adresse du Jeu (utilisée pour accéder au plateau et écrire dans log)
@param pieceAtt adresse de la Piece attaquante
@param pieceDef adresse de la Piece en défense
@param couleurGagne contient la Couleur de la Piece qui a gagné le combat à la fin de la fonction
@return adresse de la Piece qui gagne le combat
*/

Piece * combatPieces(Jeu * jeu, Piece * pieceAtt, Piece * pieceDef);

/* autre */

/**
@brief convertit un entier en chaine de caractères
@param n entier à convertir
@param s chaine de caractère contenant les caractères de n à la fin de la fonction
@return Aucun
*/

void iTOa(int n, char s[]) ;

/**
@brief renverse la chaine de caractère passée en paramètre
@param s chaine à renverser
@return Aucun
*/

void reverse(char s []);

#endif
