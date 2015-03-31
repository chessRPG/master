#include "jeu.h"
#include "afficheNCURSES.h"

int main()
{
    Jeu jeu ;

    jeu.plateau = *creerPlateau(BLANC, NOIR) ;
    jeu.J1 = *creerJoueur("Robin", BLANC);
    jeu.J2 = *creerJoueur("Pilou", NOIR);
    jeu.joueurActif = &(jeu.J2);
    jeu.plateau = *creerPlateau(BLANC, NOIR) ;
    boucleEvent(&jeu) ;

    return 0 ;
}
