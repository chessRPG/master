#include "jeu.h"

/*#define JEU_NCURSES
#define JEU_SDL*/

#ifdef JEU_NCURSES
#include "afficheNCURSES.h"
#endif

#ifdef JEU_SDL
#include "afficheSDL.h"
#endif

int main()
{
    #ifdef JEU_NCURSES
        Jeu jeu ;
        char piecesJ1[32];
        char piecesJ2[32];
        char log[1024];

        initJeu(&jeu, piecesJ1, piecesJ2);

        boucleEvent(&jeu);

        detruireJeu(&jeu);
    #endif


    #ifdef JEU_SDL
        JeuSDL jeuSdl;

        SdlInit(&jeuSdl) ;

        SdlBoucle(&jeuSdl);

        SdlLibere(&jeuSdl);
    #endif

    return 0 ;
}
