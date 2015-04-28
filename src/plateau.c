/**

@brief Module de gestion des joueurs
@author GONDRAS Pierre-Louis, GREYL Robin, SCHREYECK Tiffanie
@file src/plateau.c
@version 1.0
@date 2014/04/21

*/

#include "plateau.h"

/**
@brief redonne leur couleur de base (blanc / noir) aux cases du plateau
@param plateau adresse du Plateau à réinitialiser
@return Aucun
*/

void reinitCouleursEchiquier(Plateau * plateau)
{
    int i, j;

    for(i = 0 ; i < 8 ; i++)
    {
        for(j = 0 ; j < 8 ; j++)
        {
            setCouleurCase(getCase(plateau, i, j), (i+j)%2);
        }
    }
}

/* accesseurs */

/**
@brief renvoie l'adresse de la case aux coordonnées (posY, posX) sur le plateau
@param plateau adresse du Plateau sur lequel chercher la case
@param posX ordonnée de la case
@param posY abcisse de la case
@return pointeur sur la Case de coordonnées passés en paramètres
*/

Case * getCase(Plateau * plateau, int posX, int posY)
{
    return &(plateau->echiquier[posX][posY]) ;
}

/**
@brief renvoie le nombre de tours écoulés depuis le début de la partie
@param plateau adresse du Plateau
@return nombre de tours écoulés
*/

int getNbTours(Plateau * plateau)
{
    return plateau->nbTours ;
}

/* creation / destruction */

/**
@brief met en place les cases et les pièces à partir des couleurs des joueurs
@param plateau adresse du Plateau à initialiser
@param C1 Couleur choisie par le Joueur 1
@param C2 Couleur choisie par le Joueur 2
@return Aucun
*/

void initPlateau(Plateau * plateau, Couleur C1, Couleur C2)
{
    int i, j ;

    plateau->echiquier = malloc(8*sizeof(Case *)) ;

    for(i = 0 ; i<8; i++ )
    {
        plateau->echiquier[i] = malloc(8*sizeof(Case));
    }


    for(i = 0 ; i < 8 ; i++)
    {
        for(j = 0 ; j < 8 ; j++)
        {
            initCase(&(plateau->echiquier[i][j]));
        }
    }

    setPieceCase(&(plateau->echiquier[0][0]), creerPiece(TOUR, C2)) ;
    setPieceCase(&(plateau->echiquier[0][1]), creerPiece(CAVALIER, C2)) ;
    setPieceCase(&(plateau->echiquier[0][2]), creerPiece(FOU, C2)) ;
    setPieceCase(&(plateau->echiquier[0][3]), creerPiece(DAME, C2)) ;
    setPieceCase(&(plateau->echiquier[0][4]), creerPiece(ROI, C2)) ;
    setPieceCase(&(plateau->echiquier[0][5]), creerPiece(FOU, C2)) ;
    setPieceCase(&(plateau->echiquier[0][6]), creerPiece(CAVALIER, C2)) ;
    setPieceCase(&(plateau->echiquier[0][7]), creerPiece(TOUR, C2)) ;

    for(i = 0 ; i < 8 ; i++)
    {
        setPieceCase(&(plateau->echiquier[1][i]), creerPiece(PION, C2)) ;
    }

    setPieceCase(&(plateau->echiquier[7][7]), creerPiece(TOUR, C1)) ;
    setPieceCase(&(plateau->echiquier[7][6]), creerPiece(CAVALIER, C1)) ;
    setPieceCase(&(plateau->echiquier[7][5]), creerPiece(FOU, C1)) ;
    setPieceCase(&(plateau->echiquier[7][4]), creerPiece(ROI, C1)) ;
    setPieceCase(&(plateau->echiquier[7][3]), creerPiece(DAME, C1)) ;
    setPieceCase(&(plateau->echiquier[7][2]), creerPiece(FOU, C1)) ;
    setPieceCase(&(plateau->echiquier[7][1]), creerPiece(CAVALIER, C1)) ;
    setPieceCase(&(plateau->echiquier[7][0]), creerPiece(TOUR, C1)) ;

    for(i = 0 ; i < 8 ; i++)
    {
        setPieceCase(&(plateau->echiquier[6][i]), creerPiece(PION, C1)) ;
    }

    plateau->nbTours = 0 ;
}

/**
@brief détruit le contenu des cases puis détruit le tableau ligne par ligne
@param plateau adresse du Plateau à détruire
@return Aucun
*/

void viderPlateau(Plateau * plateau)
{
    int i, j ;

    for(i = 0 ; i < 8 ; i++)
    {
        for(j = 0 ; j < 8 ; j++)
        {
            detruireCase(&(plateau->echiquier[i][j])) ;
        }
        free(plateau->echiquier[i]);
    }
    free(plateau->echiquier);
}
