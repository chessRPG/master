#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "joueur.h"

/* interne */

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

void setDonneesJoueurs(Joueur * joueur1, Joueur * joueur2, char * piecesJ1, char * piecesJ2)
{
    char nom[32];

    system("clear");
    printf("JOUEUR 1 :\n");
    printf("Nom : ");
    scanf("%s", nom);
    setNomJoueur(joueur1, nom);
    printf("\nChoisis ton camp !\n");
    saisiePieces(joueur1, joueur1, piecesJ1);


    system("clear");
    printf("JOUEUR 2 :\n");
    printf("Nom : ");
    scanf("%s", nom);
    setNomJoueur(joueur2, nom);
    printf("\nChoisis ton camp !\n");
    saisiePieces(joueur1, joueur2, piecesJ2);
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
