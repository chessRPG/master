#include "afficheSDL.h"

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <assert.h>

/* privee */

SDL_Surface *SDL_load_image(const char* filename )
{
	/* Temporary storage for the image that's loaded */
	SDL_Surface* loadedImage = NULL;

	/* The optimized image that will be used */
	/*SDL_Surface* optimizedImage = NULL;*/

	/* Load the image */
	loadedImage = SDL_LoadBMP( filename );

    /*
	if ( loadedImage != NULL )
	{
		optimizedImage = SDL_DisplayFormat( loadedImage );
		SDL_FreeSurface( loadedImage );
	}
	*/

	/* Return the optimized image */

	return loadedImage;
}

void SDL_apply_surface( SDL_Surface* source, SDL_Surface* destination, int x, int y )
{
	/* Make a temporary rectangle to hold the offsets */
	SDL_Rect offset;

	/* Give the offsets to the rectangle */
	offset.x = x;
	offset.y = y;

	/* Blit the surface */
	SDL_BlitSurface( source, NULL, destination, &offset );
}

/* public */

const int TAILLE_CASE = 40 ;


void SdlInit(Jeu* jeu)
{
    JeuSDL jeuSDL ;
    int dimX = 8 * TAILLE_CASE ;
    int dimY = 8 * TAILLE_CASE ;

    assert(SDL_Init(SDL_INIT_EVERYTHING)!= -1) ;

    jeuSDL.surface_ecran = SDL_SetVideoMode(dimX, dimY, 40, SDL_SWSURFACE) ;
    SDL_WM_SetCaption("ChessRPG v0.1b", NULL) ;

    jeuSDL.surface_BLANC = SDL_load_image("data/CB.bmp") ;
    if(jeuSDL.surface_BLANC == NULL) jeuSDL.surface_BLANC = SDL_load_image("../data/CB.bmp") ;
    assert(jeuSDL.surface_BLANC != NULL) ;

    jeuSDL.surface_NOIR = SDL_load_image("data/CN.bmp") ;
    if(jeuSDL.surface_NOIR == NULL) jeuSDL.surface_NOIR = SDL_load_image("../data/CN.bmp") ;
    assert(jeuSDL.surface_NOIR != NULL) ;

    jeuSDL.surface_BLEU = SDL_load_image("data/CS.bmp") ;
    if(jeuSDL.surface_BLEU == NULL) jeuSDL.surface_BLEU = SDL_load_image("../data/CS.bmp") ;
    assert(jeuSDL.surface_BLEU != NULL) ;

    SdlAffichage(jeuSDL) ;

}

void SdlAffichage(const JeuSDL jeuSDL)
{
    int i,j ;

    for (i=0 ; i < 8 ; i++)
    {
        for (j=0 ; j < 8 ; j++)
        {
            if((i+j)%2 == 0)
            {
                SDL_apply_surface(jeuSDL.surface_BLANC, jeuSDL.surface_ecran, i*TAILLE_CASE, j*TAILLE_CASE) ;
            }
            else
            {
                SDL_apply_surface(jeuSDL.surface_NOIR, jeuSDL.surface_ecran, i*TAILLE_CASE, j*TAILLE_CASE) ;
            }
        }
    }
    SDL_Flip(jeuSDL.surface_ecran) ;

}

/*void SdlBoucle(JeuSDL* jeuSDL, Jeu* jeu)
{

}

void SdlLibere(JeuSDL* jeuSDL, Jeu* jeu)
{

}*/
