#include "jeu.h"

#define JEU_NCURSES
//#define JEU_SDL

#ifdef JEU_NCURSES
#include "afficheNCURSES.h"
#endif

#ifdef JEU_SDL
#include "afficheSDL.h"
#endif

int main()
{
    #ifdef JEU_NCURSES
        //test();
        Jeu jeu ;

        NcursesInit(&jeu);

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
