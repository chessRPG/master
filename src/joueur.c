#include <string.h>

#include "joueur.h"

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
    strcpy(joueur->nomJoueur, nomJoueur);
}

void setCouleurJoueur(Joueur * joueur, Couleur couleur)
{
    joueur->couleur = couleur ;
}

/* creation / destruction */

Joueur * creerJoueur(char * nomJoueur, Couleur couleur)
{
    Joueur * joueur ;
    joueur = malloc(sizeof(Joueur)) ;
    initJoueur(joueur);

    return joueur;
}

void initJoueur(Joueur * joueur)
{
    int i = 0;
    for (i = 0 ; i < 32 ; i++)
    {
        joueur->nomJoueur[i] = '\0';
    }

    joueur->couleur = BLANC;
}

void detruireJoueur(Joueur * joueur)
{
    free(joueur);
}
