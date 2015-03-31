#include "jeu.h"
#include "afficheNCURSES.h"
#include "afficheSDL.h"

int main()
{
    Jeu jeu ;
    jeu.plateau = *creerPlateau(BLANC, NOIR) ;
    SdlInit(&jeu) ;

    return 0 ;
}
