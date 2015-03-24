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
    joueur->nomJoueur = nomJoueur ;
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

}

void initJoueur(Joueur * joueur)
{

}

void detruireJoueur(Joueur * joueur)
{

}










