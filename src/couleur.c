#include "couleur.h"

/**
@brief crée une liste des couleurs de pièces disponibles
@return Pointeur une liste des couleurs disponibles
*/

Couleur * getListeCouleurs()
{
    Couleur * liste ;
    int longueur, i ;

    longueur = NUM_COULEUR ;

    liste = malloc(sizeof(longueur*sizeof(longueur))) ;

    for(i=0; i<longueur; i++)
    {
        liste[i] = (Couleur) i ;
    }

    return liste ;
}
