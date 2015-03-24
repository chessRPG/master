#include "jeu.h"
#include "afficheNCURSES.h"
int main()
{
    Jeu jeu ;
    printf("coucou1\n") ;
    jeu.plateau = *creerPlateau(BLANC, NOIR) ;
    printf("coucou1000\n") ;
    //boucleEvent(&jeu) ;
    return 0 ;
}
