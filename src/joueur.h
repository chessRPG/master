/**

@brief Module de gestion des joueurs
@author GONDRAS Pierre-Louis, GREYL Robin, SCHREYECK Tiffanie
@file src/joueur.h
@version 1.0
@date 2015/05/22

*/

#ifndef _JOUEUR_H
#define _JOUEUR_H

#include "couleur.h"
#include "piece.h"

/**
@struct Joueur
@brief structure stockant le nom du joueur et la couleur des pièces choisie
@param nomJoueur chaine de 32 caractères stockant le nom du joueur
@param couleur Couleur choisie par le joueur
@see Joueur
*/
typedef struct
{
    char nomJoueur[13] ;
    Couleur couleur ;

    int nbPieces;
    Piece * ensPieces[16];
}  Joueur;

/* accesseurs */

/**
@brief renvoie le nom du joueur passé en paramètre
@param joueur pointeur sur le joueur dont on veut le nom
@return chaine de caractères (char *) contenant le nom du joueur passé en paramètre
*/
char * getNomJoueur(Joueur * joueur) ;

/**
@brief renvoie la couleur du joueur passé en paramètre
@param joueur pointeur sur le Joueur dont on veut la couleur
@return Couleur choisie par le joueur
*/
Couleur getCouleurJoueur(Joueur * joueur) ;

/**
@brief renvoie le nombre de pièces vivantes d'un joueur
@param joueur pointeur sur le joueur dont on veut le nombre de pièces
@return nombre de pieces vivantes du joueur
*/
int getNbPiecesJoueur(Joueur * joueur);

/* mutateurs */

/**
@brief modifie le nom du joueur passé en paramètre
@param joueur pointeur sur le Joueur dont on veut modifier le nom
@param nomJoueur chaine de caractère contenant le nom qu'on veut donner au joueur
@return Aucun
*/
void setNomJoueur(Joueur * joueur, char * nomJoueur) ;

/**
@brief modifie la couleur des pièces du joueur passé en paramètre
@param joueur pointeur sur le Joueur dont on veut modifier la couleur des pièces
@param couleur Couleur choisie par le joueur
@return Aucun
*/
void setCouleurJoueur(Joueur * joueur, Couleur couleur) ;

/**
@brief  Menu permettant de choisir le nom des joueurs et la couleur des pièces qu'ils vont jouer
@param joueur1 pointeur sur le Joueur 1
@param joueur2 pointeur sur le Joueur 2
@param piecesJ1 chaine de 32 caractères, contient le chemin d'accès des pièces du joueur 1 à la fin de la fonction
@param piecesJ2 chaine de 32 caractères, contient le chemin d'accès des pièces du joueur 2 à la fin de la fonction
@return Aucun
*/
void setDonneesJoueurs(Joueur * joueur1, Joueur * joueur2, char * nom1, char * nom2, Couleur C1, Couleur C2) ;

/**
@brief ajoute une pièce à la liste des pièces d'un joueur
@param joueur pointeur vers le joueur à qui on veut ajouter les pièces
@param piece pointeur vers la pièce à ajouter
@return Aucun
*/
void setPieceJoueur(Joueur * joueur, Piece * piece);

/* creation / destruction */

/**
@brief remplit la chaine de caractère contenant le nom du joueur par des '\0' et lui donne la couleur passée en paramètre
@param joueur pointeur sur le Joueur à initialiser
@param couleur Couleur à donner au joueur
@return Aucun
*/
void initJoueur(Joueur * joueur) ;

/* ... */

/**
@brief Verifie si une piece est dans la liste des pièces d'un joueur et renvoie son indice
@param piece pointeur vers la pièce à rechercher
@param joueur pointeur vers le joueur dont on vérifie la possession de la pièce
@return l'indice de la pièce dans le tableau, ou -1 si elle n'y est pas
*/
int estDansEnsPieces(Piece * piece, Joueur * joueur);

#endif
