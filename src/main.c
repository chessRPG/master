#include "jeu.h"
#include "afficheNCURSES.h"
int main()
{
    Jeu jeu ;
<<<<<<< HEAD

    jeu.plateau = *creerPlateau(BLANC, NOIR) ;

=======
    jeu.plateau = *creerPlateau(BLANC, NOIR) ;
>>>>>>> adfb435f353152098c382447728fce244c067471
    boucleEvent(&jeu) ;
    return 0 ;
}
