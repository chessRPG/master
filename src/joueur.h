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

void setDonneesJoueurs(Joueur * joueur1, Joueur * joueur2, char * piecesJ1, char * piecesJ2) ;

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
@brief Securise une chaine de  12 caractères en la coupant si elle est trop longue
@param nomSecure chaine de 12 caractères sécurisée
@param nom chaine caractères à sécuriser
@return Aucun
*/

void secureNom(char* nomSecure, char* nom) ;

#endif
