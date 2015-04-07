#include "jeu.h"

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
        Jeu jeu ;

        initJeu(&jeu, BLANC, NOIR);

        setNomJoueur(&(jeu.J1), "joueur1");
        setNomJoueur(&(jeu.J2), "joueur2");

        setJoueurActif(&jeu, &(jeu.J1));

        boucleEvent(&jeu);

        detruireJeu(&jeu);
    #endif


    #ifdef JEU_SDL
        JeuSDL jeuSdl;

        SdlInit(&jeuSdl, BLANC, NOIR) ;

        setNomJoueur(&(jeuSdl.jeu.J1), "JOUEUR 1");
        setNomJoueur(&(jeuSdl.jeu.J2), "TRUCMUCHE");

        setJoueurActif(&(jeuSdl.jeu), &(jeuSdl.jeu.J1));

        SdlBoucle(&jeuSdl);
//        SdlLibere(&jeuSdl);

        detruireJeu(&(jeuSdl.jeu));
    #endif

    return 0 ;
}
