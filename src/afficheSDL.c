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

void SDL_apply_surface( SDL_Surface* surface, SDL_Surface* ecran, int y, int x )
{
	/* Make a temporary rectangle to hold the offsets */
	SDL_Rect position;

	/* Give the offsets to the rectangle */
	position.x = x;
	position.y = y;

	/* Blit the surface */
	SDL_BlitSurface( surface, NULL, ecran, &position );
}

void SdlAffichePiece(JeuSDL * jeu, int i, int j, Piece * piece)
{
    Type type = getTypePiece(piece) ;
    SDL_Surface * ecran = jeu->surface_ecran;

    switch (type)
    {
    case TOUR:
        if (getCouleurPiece(piece) == 0) SDL_apply_surface(jeu->surface_T1, ecran, i, j);
        else SDL_apply_surface(jeu->surface_T2, ecran, i, j) ;
        break ;
    case CAVALIER:
        if (getCouleurPiece(piece) == 0) SDL_apply_surface(jeu->surface_C1, ecran, i, j) ;
        else SDL_apply_surface(jeu->surface_C2, ecran, i, j) ;
        break ;
    case FOU:
        if (getCouleurPiece(piece) == 0) SDL_apply_surface(jeu->surface_F1, ecran, i, j) ;
        else SDL_apply_surface(jeu->surface_F2, ecran, i, j) ;
        break ;
    case DAME:
        if (getCouleurPiece(piece) == 0) SDL_apply_surface(jeu->surface_D1, ecran, i, j) ;
        else SDL_apply_surface(jeu->surface_D2, ecran, i, j) ;
        break ;
    case ROI:
        if (getCouleurPiece(piece) == 0) SDL_apply_surface(jeu->surface_R1, ecran, i, j) ;
        else SDL_apply_surface(jeu->surface_R2, ecran, i, j) ;
        break ;
    default: /* pion */
        if (getCouleurPiece(piece) == 0) SDL_apply_surface(jeu->surface_P1, ecran, i, j) ;
        else SDL_apply_surface(jeu->surface_P2, ecran, i, j) ;
        break ;
    }
}

void dessineRectangle(SDL_Surface * ecran, int y, int x, int X, int Y, Couleur cou)
{
    SDL_Rect rectangle;
	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = X-x;
	rectangle.h = Y-y;

	SDL_FillRect(ecran, &rectangle, cou);
}

/* public */

const int TAILLE_CASE = 40 ;


void SdlInit(JeuSDL * jeuSDL, Couleur C1, Couleur C2)
{
    Jeu * jeu;

    int dimX = 8 * TAILLE_CASE ;
    int dimY = 9 * TAILLE_CASE ;

    jeu = &(jeuSDL->jeu);

    initJeu(jeu, C1, C2);

    assert(SDL_Init(SDL_INIT_EVERYTHING)!= -1) ;

    jeuSDL->surface_ecran = SDL_SetVideoMode(dimX, dimY, 32, SDL_SWSURFACE) ;
    assert(jeuSDL->surface_ecran != NULL);
    SDL_WM_SetCaption("ChessRPG v0.1b", NULL) ;

    jeuSDL->surface_BLANC = IMG_Load("data/CB.bmp") ;
    if(jeuSDL->surface_BLANC == NULL) jeuSDL->surface_BLANC = IMG_Load("../data/CB.bmp") ;
    assert(jeuSDL->surface_BLANC != NULL) ;

    jeuSDL->surface_NOIR = IMG_Load("data/CN.bmp") ;
    if(jeuSDL->surface_NOIR == NULL) jeuSDL->surface_NOIR = IMG_Load("../data/CN.bmp") ;
    assert(jeuSDL->surface_NOIR != NULL) ;

    jeuSDL->surface_BLEU = IMG_Load("data/CS.bmp") ;
    if(jeuSDL->surface_BLEU == NULL) jeuSDL->surface_BLEU = IMG_Load("../data/CS.bmp") ;
    assert(jeuSDL->surface_BLEU != NULL) ;

    jeuSDL->surface_ROUGE = IMG_Load("data/CR.bmp") ;
    if(jeuSDL->surface_ROUGE == NULL) jeuSDL->surface_ROUGE = IMG_Load("../data/CR.bmp") ;
    assert(jeuSDL->surface_ROUGE != NULL) ;

    jeuSDL->surface_T1 = IMG_Load("data/BLANC/T.png");
    assert(jeuSDL->surface_T1 != NULL);
    jeuSDL->surface_C1 = IMG_Load("data/BLANC/C.png");
    assert(jeuSDL->surface_C1 != NULL);
    jeuSDL->surface_F1 = IMG_Load("data/BLANC/F.png");
    assert(jeuSDL->surface_F1 != NULL);
    jeuSDL->surface_R1 = IMG_Load("data/BLANC/R.png");
    assert(jeuSDL->surface_R1 != NULL);
    jeuSDL->surface_D1 = IMG_Load("data/BLANC/D.png");
    assert(jeuSDL->surface_D1 != NULL);
    jeuSDL->surface_P1 = IMG_Load("data/BLANC/P.png");
    assert(jeuSDL->surface_P1 != NULL);

    jeuSDL->surface_T2 = IMG_Load("data/NOIR/T.png");
    assert(jeuSDL->surface_T2 != NULL);
    jeuSDL->surface_C2 = IMG_Load("data/NOIR/C.png");
    assert(jeuSDL->surface_C2 != NULL);
    jeuSDL->surface_F2 = IMG_Load("data/NOIR/F.png");
    assert(jeuSDL->surface_F2 != NULL);
    jeuSDL->surface_R2 = IMG_Load("data/NOIR/R.png");
    assert(jeuSDL->surface_R2 != NULL);
    jeuSDL->surface_D2 = IMG_Load("data/NOIR/D.png");
    assert(jeuSDL->surface_D2 != NULL);
    jeuSDL->surface_P2 = IMG_Load("data/NOIR/P.png");
    assert(jeuSDL->surface_P2 != NULL);
}
/*
void SdlLibere(JeuSDL* jeuSDL)
{
    SDL_FreeSurface(jeuSDL->surface_ecran);

    detruireJeu(&jeuSDL->jeu);

    SDL_Quit();
}
*/
void SdlAffichage(JeuSDL * jeuSDL)
{
    int i,j,longueur;
    Case * cell;
    Piece * piece;

    for (i=0 ; i < 8 ; i++)
    {
        for (j=0 ; j < 8 ; j++)
        {
            cell = getCase(&(jeuSDL->jeu.plateau), i, j);
            piece = getPieceCase(cell);

            if (getCouleurCase(cell) == CROUGE)
                SDL_apply_surface(jeuSDL->surface_ROUGE, jeuSDL->surface_ecran, i*TAILLE_CASE, j*TAILLE_CASE) ;
            else if (getCouleurCase(cell) == CBLEU)
                SDL_apply_surface(jeuSDL->surface_BLEU, jeuSDL->surface_ecran, i*TAILLE_CASE, j*TAILLE_CASE) ;
            else if(getCouleurCase(cell) == CBLANC)
                SDL_apply_surface(jeuSDL->surface_BLANC, jeuSDL->surface_ecran, i*TAILLE_CASE, j*TAILLE_CASE) ;
            else
                SDL_apply_surface(jeuSDL->surface_NOIR, jeuSDL->surface_ecran, i*TAILLE_CASE, j*TAILLE_CASE) ;

            if (piece != NULL)
                SdlAffichePiece(jeuSDL, i*TAILLE_CASE, j*TAILLE_CASE, piece);
        }
    }

/*  affichage du nom du joueur actif    */

    Uint32 noire = SDL_MapRGB(jeuSDL->surface_ecran->format, 0, 0, 0);
    dessineRectangle(jeuSDL->surface_ecran, 8*TAILLE_CASE, 0, 8*TAILLE_CASE, 1*TAILLE_CASE, noire);

    TTF_Init();
    TTF_Font * police = NULL;
    SDL_Surface * texte;
    char * joueurActif = getNomJoueur(jeuSDL->jeu.joueurActif);

    police = TTF_OpenFont("data/rmegg.ttf", 40);
    SDL_Color blanc = {255, 255, 255};
    texte = TTF_RenderText_Blended(police, joueurActif, blanc);

    longueur = texte->w;
    SDL_apply_surface(texte, jeuSDL->surface_ecran, 8*TAILLE_CASE, (8*TAILLE_CASE-longueur)/2);

    TTF_CloseFont(police);
    TTF_Quit();

}

void SdlBoucle(JeuSDL * jeuSDL)
{
    SDL_Event event;
	int continue_boucle = 1;
	int x = 1000, y = 1000 ;
	int posX, posY ;
	CouleurCase couleurTemp ;

	reinitCouleursEchiquier(&jeuSDL->jeu.plateau) ;

    SdlAffichage(jeuSDL);
	assert( SDL_Flip( jeuSDL->surface_ecran )!=-1 );

	while ( continue_boucle == 1 )
	{
		while ( SDL_PollEvent( &event ) )
		{

			if ( event.type == SDL_QUIT )
				continue_boucle = 0;

            if (event.type == SDL_MOUSEMOTION)
            {
                if (caseValide(x, y)) setCouleurCase(getCase(&jeuSDL->jeu.plateau, x, y), couleurTemp);


                SDL_GetMouseState(&y, &x) ;
                x = x / TAILLE_CASE ;
                y = y / TAILLE_CASE ;
                if (caseValide(x, y))
                {
                    couleurTemp = getCouleurCase(getCase(&jeuSDL->jeu.plateau, x, y)) ;
                    setCouleurCase(getCase(&jeuSDL->jeu.plateau, x, y), CROUGE);
                }
            }

            if (event.type == SDL_MOUSEBUTTONDOWN && caseValide(x, y))
            {
                if (couleurTemp == CBLEU)
                {
                    deplacerPiece(&jeuSDL->jeu.plateau, getPieceCase(getCase(&jeuSDL->jeu.plateau, posX, posY)), x, y) ;
                    reinitCouleursEchiquier(&jeuSDL->jeu.plateau) ;
                    couleurTemp = (x+y)%2 ;
                    if (jeuSDL->jeu.joueurActif == &jeuSDL->jeu.J1) setJoueurActif(&jeuSDL->jeu, &jeuSDL->jeu.J2);
                    else setJoueurActif(&jeuSDL->jeu, &jeuSDL->jeu.J1);
                }
                else
                {
                    selectPiece(&jeuSDL->jeu, x, y) ;
                    couleurTemp = CBLEU ;
                    posX = x ;
                    posY = y ;
                }
            }


			if ( event.type == SDL_KEYDOWN )
			{

				switch ( event.key.keysym.sym )
				{
                    case SDLK_SPACE:    //  Changement de joueur actif
                        if (jeuSDL->jeu.joueurActif == &jeuSDL->jeu.J1)
                            setJoueurActif(&jeuSDL->jeu, &jeuSDL->jeu.J2);
                        else    setJoueurActif(&jeuSDL->jeu, &jeuSDL->jeu.J1);
                        reinitCouleursEchiquier(&jeuSDL->jeu.plateau) ;
                        break;
                    case SDLK_ESCAPE:
                        continue_boucle = 0;
                        break;
                    default:
                        break;
				}
			}
		}

        SdlAffichage(jeuSDL);
        SDL_Flip( jeuSDL->surface_ecran );
	}

}

