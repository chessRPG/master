#include "couleur.h"

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
