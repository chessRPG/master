#include "jeu.h"
#include "afficheNCURSES.h"
int main()
{
    Jeu jeu ;
    printf("coucou1") ;
    jeu.plateau = *creerPlateau(BLANC, NOIR) ;
    printf("coucou1000") ;
    //boucleEvent(&jeu) ;
    return 0 ;
}
