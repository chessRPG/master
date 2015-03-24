#include "plateau.h"

/* accesseurs */

Case * getCase(Plateau * plateau, int posX, int posY)
{
    return plateau->echiquier[posX][posY] ;
}

int getNbTours(Plateau * plateau)
{
    return plateau->nbTours ;
}

/* creation / destruction */

void initPlateau(Plateau * plateau)
{
    int i, j ;

    for(i = 0 ; i < 8 ; i++)
    {
        for(j = 0 ; j < 8 ; j++)
        {
            plateau->echiquier[i][j] = NULL ;
        }
    }

    plateau->nbTours = 0 ;
}

Plateau * creerPlateau()
{
    Plateau * plateau ;
    int i, j ;
    plateau = malloc(sizeof(Plateau)) ;

    initPlateau(plateau) ;

    for(i = 0 ; i < 8 ; i++)
    {
        for(j = 0 ; j < 8 ; j++)
        {
            plateau->echiquier[i][j] = creerCase((i+j)%2) ;
        }
    }
}

void viderPlateau(Plateau * plateau)
{
    int i, j ;

    for(i = 0 ; i < 8 ; i++)
    {
        for(j = 0 ; j < 8 ; j++)
        {
            detruireCase(plateau->echiquier[i][j]) ;
        }
    }
}

void detruirePlateau(Plateau * plateau)
{
    viderPlateau(plateau) ;
    free(plateau) ;
}
















