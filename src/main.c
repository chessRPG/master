#include "jeu.h"
#include "afficheNCURSES.h"
int main()
{
    Jeu jeu ;

    jeu.plateau = *creerPlateau(BLANC, NOIR) ;

    boucleEvent(&jeu) ;
    return 0 ;
}
