/**

@brief Module de gestion des joueurs
@author GONDRAS Pierre-Louis, GREYL Robin, SCHREYECK Tiffanie
@file src/joueur.c
@version 1.0
@date 2015/05/22

*/



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

char * getNomJoueur(Joueur * joueur)
{
    return joueur->nomJoueur ;
}

Couleur getCouleurJoueur(Joueur * joueur)
{
    return joueur->couleur ;
}

/* mutateurs */

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

void setCouleurJoueur(Joueur * joueur, Couleur couleur)
{
    joueur->couleur = couleur ;
}

void setNbPiecesJoueur(Joueur * joueur, int nbPieces)
{
    joueur->nbPieces = nbPieces;
}

void secureNom(char* nomSecure, char* nom)
{
    int cpt = 0;

    while(cpt < 12 && nom[cpt] != '\0')
    {
        nomSecure[cpt] = nom[cpt];
        cpt++;
    }
    nomSecure[cpt] = '\0';
}

void setDonneesJoueurs(Joueur * joueur1, Joueur * joueur2, char * nom1, char * nom2, Couleur C1, Couleur C2)
{
    /*char nom[32];
    char nomSecure[13];

    system("clear");
    printf("JOUEUR 1 :\n");
    printf("Nom : ");
    scanf("%s", nom);
    secureNom(nomSecure, nom);

    setNomJoueur(joueur1, nomSecure);
    printf("\nChoisis ton camp !\n");
    saisiePieces(joueur1, joueur1, piecesJ1);


    system("clear");
    printf("JOUEUR 2 :\n");
    printf("Nom : ");
    scanf("%s", nom);
    secureNom(nomSecure, nom);

    setNomJoueur(joueur2, nomSecure);
    printf("\nChoisis ton camp !\n");
    saisiePieces(joueur1, joueur2, piecesJ2);
    system("clear");*/

    setNomJoueur(joueur1, nom1);
    setNomJoueur(joueur2, nom2);

    setCouleurJoueur(joueur1, C1);
    setCouleurJoueur(joueur2, C2);
}

void setPieceJoueur(Joueur * joueur, Piece * piece)
{
    joueur->ensPieces[joueur->nbPieces] = *piece;
    joueur->nbPieces++;
}

/* creation / destruction */

void initJoueur(Joueur * joueur)
{
    joueur->nomJoueur[0] = '\0';

    setCouleurJoueur(joueur, NUM_COULEUR);
    setNbPiecesJoueur(joueur, 0);
}
