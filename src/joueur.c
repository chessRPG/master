/**

@brief Module de gestion des joueurs
@author GONDRAS Pierre-Louis, GREYL Robin, SCHREYECK Tiffanie
@file src/joueur.c
@version 1.0
@date 2014/04/21

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "joueur.h"

/* interne */

/**
@brief fonction permettant de déterminer le chemin d'accès des pièces que choisit le joueur en cours de création
@param joueurRef pointeur sur le Joueur 1 (joueur de référence)
@param joueur pointeur sur le Joueur en train de choisir ses pièces
@param pieces chaine de 32 caractères, contient le chemin d'accès des pièces du joueur à la fin de la fonction
@return Aucun

le joueur de référence permet de savoir si on est en train de choisir les pièces du joueur 1 ou du joueur 2
*/

void saisiePieces(Joueur * joueurRef, Joueur * joueur, char * pieces)
{
    Couleur couleurRef = getCouleurJoueur(joueurRef);
    int menu = -1;

    do
    {
        printf("1- Standard\n");
        printf("2- Invaders\n");
        scanf("%d", &menu);
    }while(menu < 1 || menu > 2);

    switch(menu)
    {
        case 1:
            strcpy(pieces, "STANDARD/");
            break;
        case 2:
            strcpy(pieces, "INVADER/");
            break;
        default:
            break;
    }

    menu = -1;
    printf("\n");

    do
    {
        if(couleurRef != BLANC) printf("1- BLANC\n");
        if(couleurRef != NOIR) printf("2- NOIR\n");
        if(couleurRef != BLEU) printf("3- BLEU\n");
        if(couleurRef != JAUNE) printf("4- JAUNE\n");
        scanf("%d", &menu);
    }while(menu < 1 || menu > 4 || menu-1 == couleurRef);

    switch(menu)
    {
        case 1:
            strcat(pieces, "BLANC/");
            setCouleurJoueur(joueur, BLANC);
            break;
        case 2:
            strcat(pieces, "NOIR/");
            setCouleurJoueur(joueur, NOIR);
            break;
        case 3:
            strcat(pieces, "BLEU/");
            setCouleurJoueur(joueur, BLEU);
            break;
        case 4:
            strcat(pieces, "JAUNE/");
            setCouleurJoueur(joueur, JAUNE);
            break;
        default:
            break;
    }
}

/* accesseurs */

/**
@brief renvoie le nom du joueur passé en paramètre
@param joueur pointeur sur le joueur dont on veut le nom
@return chaine de caractères (char *) contenant le nom du joueur passé en paramètre
*/

char * getNomJoueur(Joueur * joueur)
{
    return joueur->nomJoueur ;
}

/**
@brief renvoie la couleur du joueur passé en paramètre
@param joueur pointeur sur le Joueur dont on veut la couleur
@return Couleur choisie par le joueur
*/

Couleur getCouleurJoueur(Joueur * joueur)
{
    return joueur->couleur ;
}

/* mutateurs */

/**
@brief modifie le nom du joueur passé en paramètre
@param joueur pointeur sur le Joueur dont on veut modifier le nom
@param nomJoueur chaine de caractère contenant le nom qu'on veut donner au joueur
@return Aucun
*/

void setNomJoueur(Joueur * joueur, char * nomJoueur)
{
    int i = 0;
    while(nomJoueur[i] != '\0')
    {
        nomJoueur[i] = toupper(nomJoueur[i]);
        i++;
    }
    strcpy(joueur->nomJoueur, nomJoueur);
}

/**
@brief modifie la couleur des pièces du joueur passé en paramètre
@param joueur pointeur sur le Joueur dont on veut modifier la couleur des pièces
@param couleur Couleur choisie par le joueur
@return Aucun
*/

void setCouleurJoueur(Joueur * joueur, Couleur couleur)
{
    joueur->couleur = couleur ;
}

/**
@brief  Menu permettant de choisir le nom des joueurs et la couleur des pièces qu'ils vont jouer
@param joueur1 pointeur sur le Joueur 1
@param joueur2 pointeur sur le Joueur 2
@param piecesJ1 chaine de 32 caractères, contient le chemin d'accès des pièces du joueur 1 à la fin de la fonction
@param piecesJ2 chaine de 32 caractères, contient le chemin d'accès des pièces du joueur 2 à la fin de la fonction
@return Aucun
*/

void setDonneesJoueurs(Joueur * joueur1, Joueur * joueur2, char * piecesJ1, char * piecesJ2)
{
    char nom[32];
    char nomSecure[13];
    int cpt = 0;

    system("clear");
    printf("JOUEUR 1 :\n");
    printf("Nom : ");
    scanf("%s", nom);
    while(cpt < 12 && nom[cpt] != '\0')
    {
        nomSecure[cpt] = nom[cpt];
        cpt++;
    }
    nomSecure[cpt] = '\0';
    setNomJoueur(joueur1, nomSecure);
    printf("\nChoisis ton camp !\n");
    saisiePieces(joueur1, joueur1, piecesJ1);


    system("clear");
    printf("JOUEUR 2 :\n");
    printf("Nom : ");
    scanf("%s", nom);
    cpt = 0;
    while(cpt < 12 && nom[cpt] != '\0')
    {
        nomSecure[cpt] = nom[cpt];
        cpt++;
    }
    nomSecure[cpt] = '\0';
    setNomJoueur(joueur2, nomSecure);
    printf("\nChoisis ton camp !\n");
    saisiePieces(joueur1, joueur2, piecesJ2);
    system("clear");
}

/* creation / destruction(pas besoin) */

/**
@brief remplit la chaine de caractère contenant le nom du joueur par des '\0' et lui donne la couleur passée en paramètre
@param joueur pointeur sur le Joueur à initialiser
@param couleur Couleur à donner au joueur
@return Aucun
*/

void initJoueur(Joueur * joueur)
{
    int i = 0;
    for (i = 0 ; i < 32 ; i++)
    {
        joueur->nomJoueur[i] = '\0';
    }

    setCouleurJoueur(joueur, NUM_COULEUR);
}
