#include "jeu.h"

//#define FOR_WINDOWS

//#define JEU_NCURSES
#define JEU_SDL

#ifdef JEU_NCURSES
#include "afficheNCURSES.h"
#endif

#ifdef JEU_SDL
#include "afficheSDL.h"
#endif

int main()
{
    #ifdef JEU_NCURSES
        JeuNCURSES jeuNcurses ;

        NcursesInit(&jeuNcurses);

        boucleEvent(&jeuNcurses);

        NcursesLibere(&jeuNcurses);
    #endif


    #ifdef JEU_SDL
        JeuSDL jeuSdl;

        SdlInit(&jeuSdl) ;

        SdlBoucle(&jeuSdl);

        SdlLibere(&jeuSdl);
    #endif

    return 0 ;
}
