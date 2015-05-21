/**

@brief Module d'affichage du jeu en utilisant SDL
@author GONDRAS Pierre-Louis, GREYL Robin, SCHREYECK Tiffanie
@file src/afficheSDL.c
@version 1.0
@date 2015/05/22

*/

#include "afficheSDL.h"

/* il faut répéter la déclaration de la fonction ici pour ne pas déclencher de warning à la compilation avec pedantic et ansi */

extern int usleep(__useconds_t __useconds);

/* taille d'une case en pixels */

const int TAILLE_CASE = 40 ;

/*  Origine de l'échiquier (en nombre de cases) */

const int ORIG_X = 2;
const int ORIG_Y = 2;

/* fonctions internes */

int ChoixRecommencer()
{
    SDL_Event event;

    while(1)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT :
                return 0;
                break;
            case SDL_KEYDOWN :
                switch ( event.key.keysym.sym )
				{
                    case SDLK_ESCAPE:
                        return 0;
                        break;
                    case SDLK_RETURN:
                        return 2;
                        break;
                    default:
                        break;
				}
                break;
            default :
                break;
        }
    }
    return 0;
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
        if (getCouleurPiece(piece) == getCouleurJoueur(&jeu->jeu.J1)) SDL_apply_surface(jeu->surface_T1, ecran, i, j);
        else SDL_apply_surface(jeu->surface_T2, ecran, i, j) ;
        break ;
    case CAVALIER:
        if (getCouleurPiece(piece) == getCouleurJoueur(&jeu->jeu.J1)) SDL_apply_surface(jeu->surface_C1, ecran, i, j) ;
        else SDL_apply_surface(jeu->surface_C2, ecran, i, j) ;
        break ;
    case FOU:
        if (getCouleurPiece(piece) == getCouleurJoueur(&jeu->jeu.J1)) SDL_apply_surface(jeu->surface_F1, ecran, i, j) ;
        else SDL_apply_surface(jeu->surface_F2, ecran, i, j) ;
        break ;
    case DAME:
        if (getCouleurPiece(piece) == getCouleurJoueur(&jeu->jeu.J1)) SDL_apply_surface(jeu->surface_D1, ecran, i, j) ;
        else SDL_apply_surface(jeu->surface_D2, ecran, i, j) ;
        break ;
    case ROI:
        if (getCouleurPiece(piece) == getCouleurJoueur(&jeu->jeu.J1)) SDL_apply_surface(jeu->surface_R1, ecran, i, j) ;
        else SDL_apply_surface(jeu->surface_R2, ecran, i, j) ;
        break ;
    default: /* pion */
        if (getCouleurPiece(piece) == getCouleurJoueur(&jeu->jeu.J1)) SDL_apply_surface(jeu->surface_P1, ecran, i, j) ;
        else SDL_apply_surface(jeu->surface_P2, ecran, i, j) ;
        break ;
    }
}

void dessineRectangle(SDL_Surface * ecran, int y, int x, int largeur, int hauteur, Couleur cou)
{
    SDL_Rect rectangle;
	rectangle.x = x;
	rectangle.y = y;
	rectangle.w = largeur;
	rectangle.h = hauteur;

	SDL_FillRect(ecran, &rectangle, cou);
}

void afficheInfosPiece(JeuSDL * jeuSDL, Piece * piece)
{
    int longueur;

    char texte[50];

    Uint32 noire = SDL_MapRGB(jeuSDL->surface_ecran->format, 0, 0, 0);
    SDL_Color couleur = {255, 255, 255};    /*blanc*/

    dessineRectangle(jeuSDL->surface_ecran, 0*TAILLE_CASE, 12*TAILLE_CASE, 8*TAILLE_CASE, 1*TAILLE_CASE, noire);

    if (piece != NULL)
    {
        sprintf(texte, "pt vie : %d  pt Attaque : %d ", getPointsVie(piece), getPointsAttaque(piece));

        jeuSDL->surface_texteInfos = TTF_RenderText_Blended(jeuSDL->police10, texte, couleur);

        longueur = jeuSDL->surface_texteInfos->w ;

        SDL_apply_surface(jeuSDL->surface_texteInfos, jeuSDL->surface_ecran, 0*TAILLE_CASE, 12*TAILLE_CASE+(8*TAILLE_CASE-longueur)/2);

        SDL_FreeSurface(jeuSDL->surface_texteInfos);

    }
}

void afficheLogs(JeuSDL * jeuSDL)
{
    Uint32 noire = SDL_MapRGB(jeuSDL->surface_ecran->format, 0, 0, 0);
    SDL_Color couleur = {255, 255, 255};    /*blanc*/
    int i = 9 ;
    int longueur ;
    char * pch ;
    int largeur = jeuSDL->surface_ecran->w;

    dessineRectangle(jeuSDL->surface_ecran, (ORIG_X+3)*TAILLE_CASE, (ORIG_Y+9)*TAILLE_CASE, (largeur-ORIG_X-12)*TAILLE_CASE, 8*TAILLE_CASE, noire);


    pch = strtok(jeuSDL->jeu.log,",-");
    while(pch != NULL)
    {
        jeuSDL->logs[i] = TTF_RenderText_Blended(jeuSDL->police10, pch, couleur);
        longueur = jeuSDL->logs[i]->w ;
        SDL_apply_surface(jeuSDL->logs[i], jeuSDL->surface_ecran, (ORIG_X+3+(9-i))*TAILLE_CASE, (ORIG_Y+10)*TAILLE_CASE+((8)*TAILLE_CASE-longueur)/2);
        SDL_FreeSurface(jeuSDL->logs[i]) ;
        i-- ;
        pch = strtok (NULL, ",-");
    }
}

void dossierParent(char * str)
{
    char temp[32];
    sprintf(temp, "../%s", str);
    strcpy(str, temp) ;
}

void SdlMenuAffichePiece(JeuSDL * jeuSDL, int numPiece)
{
    SDL_Surface* surface_ChoixPiece;
    const int cLargeurEcran = jeuSDL->surface_ecran->w;
    const int cPosLPiece = (cLargeurEcran-5.5*TAILLE_CASE)/2;
    const int cPosHPiece = 6*TAILLE_CASE;

    if (numPiece == 0)
    {
        surface_ChoixPiece = IMG_Load("data/STANDARD/BLANC/R.png");
        SDL_apply_surface(surface_ChoixPiece, jeuSDL->surface_ecran, 0*TAILLE_CASE+cPosHPiece, 0*TAILLE_CASE+cPosLPiece);
        SDL_FreeSurface(surface_ChoixPiece);
    }
    if (numPiece == 1)
    {
        surface_ChoixPiece = IMG_Load("data/STANDARD/NOIR/R.png");
        SDL_apply_surface(surface_ChoixPiece, jeuSDL->surface_ecran, 0*TAILLE_CASE+cPosHPiece, 1.5*TAILLE_CASE+cPosLPiece);
        SDL_FreeSurface(surface_ChoixPiece);
    }
    if (numPiece == 2)
    {
        surface_ChoixPiece = IMG_Load("data/STANDARD/BLEU/R.png");
        SDL_apply_surface(surface_ChoixPiece, jeuSDL->surface_ecran, 0*TAILLE_CASE+cPosHPiece, 3*TAILLE_CASE+cPosLPiece);
        SDL_FreeSurface(surface_ChoixPiece);
    }
    if (numPiece == 3)
    {
        surface_ChoixPiece = IMG_Load("data/STANDARD/JAUNE/R.png");
        SDL_apply_surface(surface_ChoixPiece, jeuSDL->surface_ecran, 0*TAILLE_CASE+cPosHPiece, 4.5*TAILLE_CASE+cPosLPiece);
        SDL_FreeSurface(surface_ChoixPiece);
    }

    if (numPiece == 4)
    {
        surface_ChoixPiece = IMG_Load("data/INVADER/BLANC/R.png");
        SDL_apply_surface(surface_ChoixPiece, jeuSDL->surface_ecran, 1.2*TAILLE_CASE+cPosHPiece, 0*TAILLE_CASE+cPosLPiece);
        SDL_FreeSurface(surface_ChoixPiece);
    }
    if (numPiece == 5)
    {
        surface_ChoixPiece = IMG_Load("data/INVADER/NOIR/R.png");
        SDL_apply_surface(surface_ChoixPiece, jeuSDL->surface_ecran, 1.2*TAILLE_CASE+cPosHPiece, 1.5*TAILLE_CASE+cPosLPiece);
        SDL_FreeSurface(surface_ChoixPiece);
    }
    if (numPiece == 6)
    {
        surface_ChoixPiece = IMG_Load("data/INVADER/BLEU/R.png");
        SDL_apply_surface(surface_ChoixPiece, jeuSDL->surface_ecran, 1.2*TAILLE_CASE+cPosHPiece, 3*TAILLE_CASE+cPosLPiece);
        SDL_FreeSurface(surface_ChoixPiece);
    }
    if (numPiece == 7)
    {
        surface_ChoixPiece = IMG_Load("data/INVADER/JAUNE/R.png");
        SDL_apply_surface(surface_ChoixPiece, jeuSDL->surface_ecran, 1.2*TAILLE_CASE+cPosHPiece, 4.5*TAILLE_CASE+cPosLPiece);
        SDL_FreeSurface(surface_ChoixPiece);
    }
}

void SdlMenuReaffichePieces(JeuSDL * jeuSDL)
{
    const int cLargeurEcran = jeuSDL->surface_ecran->w;
    const int cPosLPiece = (cLargeurEcran-5.5*TAILLE_CASE)/2;
    const int cPosHPiece = 6*TAILLE_CASE;
    Uint32 couleurFond = SDL_MapRGB(jeuSDL->surface_ecran->format, 0, 0, 0); /*Noir*/
    int i;

    dessineRectangle(jeuSDL->surface_ecran, cPosHPiece, cPosLPiece, 5.5*TAILLE_CASE, 2.2*TAILLE_CASE, couleurFond);
    for (i=0; i<8; i++)
            SdlMenuAffichePiece(jeuSDL, i);
}

int SdlMenuCaseSurvolee(JeuSDL * jeuSDL, int x, int y)
{
    const int cLargeurEcran = jeuSDL->surface_ecran->w;
    const int cPosLPiece = (cLargeurEcran-5.5*TAILLE_CASE)/2;
    const int cPosHPiece = 6*TAILLE_CASE;

    if (x > 0*TAILLE_CASE+cPosHPiece && x < 1*TAILLE_CASE+cPosHPiece)
    {
        if (y > 0*TAILLE_CASE+cPosLPiece && y < 1*TAILLE_CASE+cPosLPiece)
            return 0;
        else if (y > 1.5*TAILLE_CASE+cPosLPiece && y < 2.5*TAILLE_CASE+cPosLPiece)
            return 1;
        else if (y > 3*TAILLE_CASE+cPosLPiece && y < 4*TAILLE_CASE+cPosLPiece)
            return 2;
        else if (y > 4.5*TAILLE_CASE+cPosLPiece && y < 5.5*TAILLE_CASE+cPosLPiece)
            return 3;
    }
    else if (x > 1.2*TAILLE_CASE+cPosHPiece && x < 2.2*TAILLE_CASE+cPosHPiece)
    {
        if (y > 0*TAILLE_CASE+cPosLPiece && y < 1*TAILLE_CASE+cPosLPiece)
            return 4;
        else if (y > 1.5*TAILLE_CASE+cPosLPiece && y < 2.5*TAILLE_CASE+cPosLPiece)
            return 5;
        else if (y > 3*TAILLE_CASE+cPosLPiece && y < 4*TAILLE_CASE+cPosLPiece)
            return 6;
        else if (y > 4.5*TAILLE_CASE+cPosLPiece && y < 5.5*TAILLE_CASE+cPosLPiece)
            return 7;
    }
    return -1;
}

void SdlMenuColorePiece(JeuSDL * jeuSDL, int numPiece, Uint32 couleur)
{
    const int cLargeurEcran = jeuSDL->surface_ecran->w;
    const int cPosLPiece = (cLargeurEcran-5.5*TAILLE_CASE)/2;
    const int cPosHPiece = 6*TAILLE_CASE;

    switch(numPiece)
    {
        case 0:
            dessineRectangle(jeuSDL->surface_ecran, 0*TAILLE_CASE+cPosHPiece, 0*TAILLE_CASE+cPosLPiece, TAILLE_CASE, TAILLE_CASE, couleur);
            SdlMenuAffichePiece(jeuSDL, 0);
            break;
        case 1:
            dessineRectangle(jeuSDL->surface_ecran, 0*TAILLE_CASE+cPosHPiece, 1.5*TAILLE_CASE+cPosLPiece, TAILLE_CASE, TAILLE_CASE, couleur);
            SdlMenuAffichePiece(jeuSDL, 1);
            break;
        case 2:
            dessineRectangle(jeuSDL->surface_ecran, 0*TAILLE_CASE+cPosHPiece, 3*TAILLE_CASE+cPosLPiece, TAILLE_CASE, TAILLE_CASE, couleur);
            SdlMenuAffichePiece(jeuSDL, 2);
            break;
        case 3:
            dessineRectangle(jeuSDL->surface_ecran, 0*TAILLE_CASE+cPosHPiece, 4.5*TAILLE_CASE+cPosLPiece, TAILLE_CASE, TAILLE_CASE, couleur);
            SdlMenuAffichePiece(jeuSDL, 3);
            break;
        case 4:
            dessineRectangle(jeuSDL->surface_ecran, 1.2*TAILLE_CASE+cPosHPiece, 0*TAILLE_CASE+cPosLPiece, TAILLE_CASE, TAILLE_CASE, couleur);
            SdlMenuAffichePiece(jeuSDL, 4);
            break;
        case 5:
            dessineRectangle(jeuSDL->surface_ecran, 1.2*TAILLE_CASE+cPosHPiece, 1.5*TAILLE_CASE+cPosLPiece, TAILLE_CASE, TAILLE_CASE, couleur);
            SdlMenuAffichePiece(jeuSDL, 5);
            break;
        case 6:
            dessineRectangle(jeuSDL->surface_ecran, 1.2*TAILLE_CASE+cPosHPiece, 3*TAILLE_CASE+cPosLPiece, TAILLE_CASE, TAILLE_CASE, couleur);
            SdlMenuAffichePiece(jeuSDL, 6);
            break;
        case 7:
            dessineRectangle(jeuSDL->surface_ecran, 1.2*TAILLE_CASE+cPosHPiece, 4.5*TAILLE_CASE+cPosLPiece, TAILLE_CASE, TAILLE_CASE, couleur);
            SdlMenuAffichePiece(jeuSDL, 7);
            break;
    }
}

void SdlSaisieNomJoueur(JeuSDL * jeuSDL, char * nom, Couleur * couleur, int joueur)
{
    const int cLargeurEcran = jeuSDL->surface_ecran->w;
    const int cHauteurEcran = jeuSDL->surface_ecran->h;
    SDL_Surface* surface_Texte;
    Uint32 couleurSaisie = SDL_MapRGB(jeuSDL->surface_ecran->format, 48, 48, 48); /*Gris anthracite*/
    Uint32 couleurValide = SDL_MapRGB(jeuSDL->surface_ecran->format, 243, 214, 23); /*Saphran*/
    Uint32 couleurSelect = SDL_MapRGB(jeuSDL->surface_ecran->format, 255, 0, 0); /*Rouge*/
    Uint32 couleurFond = SDL_MapRGB(jeuSDL->surface_ecran->format, 0, 0, 0); /*Noir*/
    SDL_Color couleurTexteValide = {0, 86, 27};   /* vert */
    SDL_Color couleurTexte = {255, 255, 255};   /* blanc */
    SDL_Color couleurTexteNom = {128, 208, 208};  /*Givré*/
    int clicCouleur = 0;
    SDL_Event event;
    int cpt = 0;
    int cursX = 0;
    int cursY = 0;
    int i, pieceSelect = -1, pieceSurvol = -1;

    dessineRectangle(jeuSDL->surface_ecran, 0, 0, cLargeurEcran, cHauteurEcran, couleurFond);

    /*  affichage du menu  */

    if(joueur == 1) surface_Texte = TTF_RenderText_Blended(jeuSDL->police40, "Nom Joueur 1:", couleurTexte);
    if(joueur == 2) surface_Texte = TTF_RenderText_Blended(jeuSDL->police40, "Nom Joueur 2:", couleurTexte);
    SDL_apply_surface(surface_Texte, jeuSDL->surface_ecran, 2.5*TAILLE_CASE, (cLargeurEcran-(surface_Texte->w))/2);
    SDL_FreeSurface(surface_Texte);

    dessineRectangle(jeuSDL->surface_ecran, 4*TAILLE_CASE-5, (cLargeurEcran-8*TAILLE_CASE)/2-5, 8*TAILLE_CASE+10, 1.03*TAILLE_CASE+10, couleurValide);
    dessineRectangle(jeuSDL->surface_ecran, 4*TAILLE_CASE, (cLargeurEcran-8*TAILLE_CASE)/2, 8*TAILLE_CASE, 1.03*TAILLE_CASE, couleurSaisie);

    sprintf(nom, "JOUEUR%d", joueur);
    surface_Texte = TTF_RenderText_Blended(jeuSDL->policeNom, nom, couleurTexteNom);
    SDL_apply_surface(surface_Texte, jeuSDL->surface_ecran, 4*TAILLE_CASE, (cLargeurEcran-(surface_Texte->w))/2);
    SDL_FreeSurface(surface_Texte);

    for (i=0; i<8; i++)
        SdlMenuAffichePiece(jeuSDL, i);

    dessineRectangle(jeuSDL->surface_ecran, 10.15*TAILLE_CASE, (cLargeurEcran-6*TAILLE_CASE)/2, 6*TAILLE_CASE, 1*TAILLE_CASE, couleurValide);

    surface_Texte = TTF_RenderText_Blended(jeuSDL->police40, "Valider", couleurTexteValide);
    SDL_apply_surface(surface_Texte, jeuSDL->surface_ecran, 10*TAILLE_CASE, (cLargeurEcran-6*TAILLE_CASE)/2);
    SDL_FreeSurface(surface_Texte);

    while(joueur != 0)
    {
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) exit(0);

            if(event.type == SDL_KEYDOWN)
            {

                if (event.key.keysym.sym == SDLK_ESCAPE)    exit(0);

                /*  Saisie du nom   */

                if(((event.key.keysym.sym >= 'a' && event.key.keysym.sym <= 'z')
                    || (event.key.keysym.sym >= '0' && event.key.keysym.sym <= '9'))
                   && cpt < 12)
                {
                    nom[cpt] = toupper(event.key.keysym.sym);
                    cpt++;
                    nom[cpt] = '\0';
                }
                else if(event.key.keysym.sym == 8 /*backspace*/ && cpt > 0)
                {
                    cpt--;
                    nom[cpt] = '\0';
                }
            }

            /*  affichage du nom    */

            if (cpt == 0) sprintf(nom, "JOUEUR%d", joueur);

            dessineRectangle(jeuSDL->surface_ecran, 4*TAILLE_CASE, (cLargeurEcran-8*TAILLE_CASE)/2, 8*TAILLE_CASE, 1.03*TAILLE_CASE, couleurSaisie);
            surface_Texte = TTF_RenderText_Blended(jeuSDL->policeNom, nom, couleurTexteNom);
            SDL_apply_surface(surface_Texte, jeuSDL->surface_ecran, 4*TAILLE_CASE, (cLargeurEcran-(surface_Texte->w))/2);
            SDL_FreeSurface(surface_Texte);

            /*  sélection de la couleur et validation    */

            if (event.type == SDL_MOUSEMOTION)
            {
                SdlMenuReaffichePieces(jeuSDL);

                dessineRectangle(jeuSDL->surface_ecran, 10.15*TAILLE_CASE-5, (cLargeurEcran-6*TAILLE_CASE)/2-5, 6*TAILLE_CASE+10, 1*TAILLE_CASE+10, couleurFond);
                dessineRectangle(jeuSDL->surface_ecran, 10.15*TAILLE_CASE, (cLargeurEcran-6*TAILLE_CASE)/2, 6*TAILLE_CASE, 1*TAILLE_CASE, couleurValide);
                surface_Texte = TTF_RenderText_Blended(jeuSDL->police40, "Valider", couleurTexteValide);
                SDL_apply_surface(surface_Texte, jeuSDL->surface_ecran, 10*TAILLE_CASE, (cLargeurEcran-6*TAILLE_CASE)/2);
                SDL_FreeSurface(surface_Texte);

                SDL_GetMouseState(&cursY, &cursX) ;
                pieceSurvol = SdlMenuCaseSurvolee(jeuSDL, cursX, cursY);

                SdlMenuColorePiece(jeuSDL, pieceSurvol, couleurSelect);
                SdlMenuAffichePiece(jeuSDL, pieceSurvol);

                if (cursX > 10.15*TAILLE_CASE && cursX < 11.15*TAILLE_CASE && cursY > (cLargeurEcran-6*TAILLE_CASE)/2 && cursY < (cLargeurEcran-6*TAILLE_CASE)/2+6*TAILLE_CASE)
                {
                    dessineRectangle(jeuSDL->surface_ecran, 10.15*TAILLE_CASE-5, (cLargeurEcran-6*TAILLE_CASE)/2-5, 6*TAILLE_CASE+10, 1*TAILLE_CASE+10, couleurSelect);
                    dessineRectangle(jeuSDL->surface_ecran, 10.15*TAILLE_CASE, (cLargeurEcran-6*TAILLE_CASE)/2, 6*TAILLE_CASE, 1*TAILLE_CASE, couleurValide);

                    surface_Texte = TTF_RenderText_Blended(jeuSDL->police40, "Valider", couleurTexteValide);
                    SDL_apply_surface(surface_Texte, jeuSDL->surface_ecran, 10*TAILLE_CASE, (cLargeurEcran-6*TAILLE_CASE)/2);
                    SDL_FreeSurface(surface_Texte);
                }
            }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                SdlMenuReaffichePieces(jeuSDL);
                pieceSelect = SdlMenuCaseSurvolee(jeuSDL, cursX, cursY);
                if (pieceSelect != -1) clicCouleur = 1;

                if (clicCouleur == 1 && cursX > 10.15*TAILLE_CASE && cursX < 11.15*TAILLE_CASE && cursY > (cLargeurEcran-6*TAILLE_CASE)/2 && cursY < (cLargeurEcran-6*TAILLE_CASE)/2+6*TAILLE_CASE)
                    joueur = 0;
            }

            SdlMenuColorePiece(jeuSDL, pieceSelect, couleurValide);
        }

        SDL_Flip(jeuSDL->surface_ecran);
        usleep(100000);
    }

    /*

        Ici l'entier pieceSelect contient un nombre compris entre 0 et 7
        Il correspond à la couleur sélectionnée par le joueur

        0 : STANDARD BLANC
        1 : STANDARD NOIR
        2 : STANDARD BLEU
        3 : STANDARD JAUNE

        4 : INVADER BLANC
        5 : INVADER NOIR
        6 : INVADER BLEU
        7 : INVADER JAUNE

        couleur = ?

    */
}

void SdlMenu(JeuSDL * jeuSDL)
{
    Uint32 couleurSelection = SDL_MapRGB(jeuSDL->surface_ecran->format, 0, 86, 27);   /* vert foncé */
    Uint32 couleurFond = SDL_MapRGB(jeuSDL->surface_ecran->format, 48, 48, 48); /* Gris anthracite */
    Uint32 couleurSolo = couleurSelection;
    Uint32 couleurPartie = couleurFond;
    SDL_Event event;
    SDL_Surface * texte;
    SDL_Color couleurTexte = {255, 255, 255};   /* blanc */
    const int cLargeurEcran = jeuSDL->surface_ecran->w;
    int choix = 0;  /* 0:SOLO ; 1:2 JOUEURS */

    int boucle = 1;

    dessineRectangle(jeuSDL->surface_ecran, 4*TAILLE_CASE, (cLargeurEcran-8*TAILLE_CASE)/2, 8*TAILLE_CASE, 1.03*TAILLE_CASE, couleurSolo);
    dessineRectangle(jeuSDL->surface_ecran, 6*TAILLE_CASE, (cLargeurEcran-8*TAILLE_CASE)/2, 8*TAILLE_CASE, 1.03*TAILLE_CASE, couleurPartie);

    texte = TTF_RenderText_Blended(jeuSDL->policeNom, "SOLO", couleurTexte);
    SDL_apply_surface(texte, jeuSDL->surface_ecran, 4*TAILLE_CASE, (cLargeurEcran-(texte->w))/2);
    SDL_FreeSurface(texte);

    texte = TTF_RenderText_Blended(jeuSDL->policeNom, "2 JOUEURS", couleurTexte);
    SDL_apply_surface(texte, jeuSDL->surface_ecran, 6*TAILLE_CASE, (cLargeurEcran-(texte->w))/2);
    SDL_FreeSurface(texte);

    while(boucle)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_KEYDOWN :
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE :
                        exit(0);
                        break;
                    case SDLK_DOWN :
                        choix = 1;
                        couleurSolo = couleurFond;
                        couleurPartie = couleurSelection;
                        break;
                    case SDLK_UP :
                        choix = 0;
                        couleurSolo = couleurSelection;
                        couleurPartie = couleurFond;
                        break;
                    case SDLK_RETURN:
                        if (choix)  setTypeJeu(&jeuSDL->jeu, PARTIE);
                        else        setTypeJeu(&jeuSDL->jeu, SOLO);


                        boucle = 0;
                        break;
                }
                dessineRectangle(jeuSDL->surface_ecran, 4*TAILLE_CASE, (cLargeurEcran-8*TAILLE_CASE)/2, 8*TAILLE_CASE, 1.03*TAILLE_CASE, couleurSolo);
                dessineRectangle(jeuSDL->surface_ecran, 6*TAILLE_CASE, (cLargeurEcran-8*TAILLE_CASE)/2, 8*TAILLE_CASE, 1.03*TAILLE_CASE, couleurPartie);

                texte = TTF_RenderText_Blended(jeuSDL->policeNom, "SOLO", couleurTexte);
                SDL_apply_surface(texte, jeuSDL->surface_ecran, 4*TAILLE_CASE, (cLargeurEcran-(texte->w))/2);
                SDL_FreeSurface(texte);

                texte = TTF_RenderText_Blended(jeuSDL->policeNom, "2 JOUEURS", couleurTexte);
                SDL_apply_surface(texte, jeuSDL->surface_ecran, 6*TAILLE_CASE, (cLargeurEcran-(texte->w))/2);
                SDL_FreeSurface(texte);

                SDL_Flip(jeuSDL->surface_ecran);
                break;
            default:
                break;

         }

    }
}

/* fonctions externes */

void SdlInit(JeuSDL * jeuSDL)
{
    Jeu * jeu;

    char piecesJ1[32];
    char piecesJ2[32];
    char temp[32];
    char nom1[13];
    char nom2[13];
    Couleur couleur1;
    Couleur couleur2;
    int dimX = 21 * TAILLE_CASE ;
    int dimY = 12 * TAILLE_CASE ;

    jeu = &(jeuSDL->jeu);

    initJeu(jeu, piecesJ1, piecesJ2);

    strcpy(temp, piecesJ1);
    strcpy(piecesJ1, "data/");
    strcat(piecesJ1, temp);
    strcpy(temp, piecesJ2);
    strcpy(piecesJ2, "data/");
    strcat(piecesJ2, temp);

    assert(SDL_Init(SDL_INIT_VIDEO)!= -1) ;

    jeuSDL->surface_ecran = SDL_SetVideoMode(dimX, dimY, 32, SDL_SWSURFACE) ;
    assert(jeuSDL->surface_ecran != NULL);
    SDL_WM_SetCaption("ChessRPG", NULL) ;

    TTF_Init();

    sprintf(temp, "data/rmegg.ttf");
    jeuSDL->policeNom = TTF_OpenFont(temp, 40);
    dossierParent(temp);
    if(jeuSDL->policeNom == NULL) jeuSDL->policeNom = TTF_OpenFont(temp, 40);
    assert(jeuSDL->policeNom != NULL);

    sprintf(temp, "data/joystix.ttf");
    jeuSDL->police10 = TTF_OpenFont(temp, 10);
    dossierParent(temp);
    if(jeuSDL->police10 == NULL) jeuSDL->police10 = TTF_OpenFont(temp, 10);
    assert(jeuSDL->police10 != NULL);

    sprintf(temp, "data/joystix.ttf");
    jeuSDL->police40 = TTF_OpenFont(temp, 40);
    dossierParent(temp);
    if(jeuSDL->police40 == NULL) jeuSDL->police40 = TTF_OpenFont(temp, 40);
    assert(jeuSDL->police40 != NULL);

    SdlMenu(jeuSDL);

    if (jeuSDL->jeu.typeJeu == SOLO)
        SdlSaisieNomJoueur(jeuSDL, nom1, &couleur1, 1);
    else
    {
        SdlSaisieNomJoueur(jeuSDL, nom1, &couleur1, 1);
        SdlSaisieNomJoueur(jeuSDL, nom2, &couleur2, 2);
    }

    /*  Cases   */
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

    /*  Pièces Joueur 1 */
    sprintf(temp, "%sT.png", piecesJ1);
    jeuSDL->surface_T1 = IMG_Load(temp);
    dossierParent(temp);
    if(jeuSDL->surface_T1 == NULL) jeuSDL->surface_T1 = IMG_Load(temp);
    assert(jeuSDL->surface_T1 != NULL);

    sprintf(temp, "%sC.png", piecesJ1);
    jeuSDL->surface_C1 = IMG_Load(temp);
    dossierParent(temp);
    if(jeuSDL->surface_C1 == NULL) jeuSDL->surface_C1 = IMG_Load(temp);
    assert(jeuSDL->surface_C1 != NULL);

    sprintf(temp, "%sF.png", piecesJ1);
    jeuSDL->surface_F1 = IMG_Load(temp);
    dossierParent(temp);
    if(jeuSDL->surface_F1 == NULL) jeuSDL->surface_F1 = IMG_Load(temp);
    assert(jeuSDL->surface_F1 != NULL);

    sprintf(temp, "%sR.png", piecesJ1);
    jeuSDL->surface_R1 = IMG_Load(temp);
    dossierParent(temp);
    if(jeuSDL->surface_R1 == NULL) jeuSDL->surface_R1 = IMG_Load(temp);
    assert(jeuSDL->surface_R1 != NULL);

    sprintf(temp, "%sD.png", piecesJ1);
    jeuSDL->surface_D1 = IMG_Load(temp);
    dossierParent(temp);
    if(jeuSDL->surface_D1 == NULL) jeuSDL->surface_D1 = IMG_Load(temp);
    assert(jeuSDL->surface_D1 != NULL);

    sprintf(temp, "%sP.png", piecesJ1);
    jeuSDL->surface_P1 = IMG_Load(temp);
    dossierParent(temp);
    if(jeuSDL->surface_P1 == NULL) jeuSDL->surface_P1 = IMG_Load(temp);
    assert(jeuSDL->surface_P1 != NULL);

    /*  Pièces Joueur 2   */
    sprintf(temp, "%sT.png", piecesJ2);
    jeuSDL->surface_T2 = IMG_Load(temp);
    dossierParent(temp);
    if(jeuSDL->surface_T2 == NULL) jeuSDL->surface_T2 = IMG_Load(temp);
    assert(jeuSDL->surface_T2 != NULL);

    sprintf(temp, "%sC.png", piecesJ2);
    jeuSDL->surface_C2 = IMG_Load(temp);
    dossierParent(temp);
    if(jeuSDL->surface_C2 == NULL) jeuSDL->surface_C2 = IMG_Load(temp);
    assert(jeuSDL->surface_C2 != NULL);

    sprintf(temp, "%sF.png", piecesJ2);
    jeuSDL->surface_F2 = IMG_Load(temp);
    dossierParent(temp);
    if(jeuSDL->surface_F2 == NULL) jeuSDL->surface_F2 = IMG_Load(temp);
    assert(jeuSDL->surface_F2 != NULL);

    sprintf(temp, "%sR.png", piecesJ2);
    jeuSDL->surface_R2 = IMG_Load(temp);
    dossierParent(temp);
    if(jeuSDL->surface_R2 == NULL) jeuSDL->surface_R2 = IMG_Load(temp);
    assert(jeuSDL->surface_R2 != NULL);

    sprintf(temp, "%sD.png", piecesJ2);
    jeuSDL->surface_D2 = IMG_Load(temp);
    dossierParent(temp);
    if(jeuSDL->surface_D2 == NULL) jeuSDL->surface_D2 = IMG_Load(temp);
    assert(jeuSDL->surface_D2 != NULL);

    sprintf(temp, "%sP.png", piecesJ2);
    jeuSDL->surface_P2 = IMG_Load(temp);
    dossierParent(temp);
    if(jeuSDL->surface_P2 == NULL) jeuSDL->surface_P2 = IMG_Load(temp);
    assert(jeuSDL->surface_P2 != NULL);

    afficheLogs(jeuSDL) ;
}

void SdlLibere(JeuSDL* jeuSDL)
{
    TTF_CloseFont(jeuSDL->policeNom);
    TTF_CloseFont(jeuSDL->police10);
    TTF_CloseFont(jeuSDL->police40);

    TTF_Quit();

    SDL_FreeSurface(jeuSDL->surface_ecran);

    SDL_FreeSurface(jeuSDL->surface_T1);
    SDL_FreeSurface(jeuSDL->surface_C1);
    SDL_FreeSurface(jeuSDL->surface_F1);
    SDL_FreeSurface(jeuSDL->surface_D1);
    SDL_FreeSurface(jeuSDL->surface_R1);
    SDL_FreeSurface(jeuSDL->surface_P1);

    SDL_FreeSurface(jeuSDL->surface_T2);
    SDL_FreeSurface(jeuSDL->surface_C2);
    SDL_FreeSurface(jeuSDL->surface_F2);
    SDL_FreeSurface(jeuSDL->surface_D2);
    SDL_FreeSurface(jeuSDL->surface_R2);
    SDL_FreeSurface(jeuSDL->surface_P2);

    SDL_FreeSurface(jeuSDL->surface_BLANC);
    SDL_FreeSurface(jeuSDL->surface_NOIR);
    SDL_FreeSurface(jeuSDL->surface_BLEU);
    SDL_FreeSurface(jeuSDL->surface_ROUGE);

    detruireJeu(&jeuSDL->jeu);

    SDL_Quit();
}

void afficheCadre(JeuSDL * jeuSDL)
{
    int i;
    char s[2];
    SDL_Color couleurLettre = {255, 255, 255};   /* blanc */

    /*  Cadre autour de l'échiquier */
    Uint32 couleur = SDL_MapRGB(jeuSDL->surface_ecran->format, 126, 51, 0); /*  marron  */
    dessineRectangle(jeuSDL->surface_ecran, (ORIG_X-1)*TAILLE_CASE, (ORIG_Y-1)*TAILLE_CASE, 10*TAILLE_CASE, 10*TAILLE_CASE, couleur);

    jeuSDL->lettres[0] = TTF_RenderText_Blended(jeuSDL->police10, "A", couleurLettre);
    jeuSDL->lettres[1] = TTF_RenderText_Blended(jeuSDL->police10, "B", couleurLettre);
    jeuSDL->lettres[2] = TTF_RenderText_Blended(jeuSDL->police10, "C", couleurLettre);
    jeuSDL->lettres[3] = TTF_RenderText_Blended(jeuSDL->police10, "D", couleurLettre);
    jeuSDL->lettres[4] = TTF_RenderText_Blended(jeuSDL->police10, "E", couleurLettre);
    jeuSDL->lettres[5] = TTF_RenderText_Blended(jeuSDL->police10, "F", couleurLettre);
    jeuSDL->lettres[6] = TTF_RenderText_Blended(jeuSDL->police10, "G", couleurLettre);
    jeuSDL->lettres[7] = TTF_RenderText_Blended(jeuSDL->police10, "H", couleurLettre);

    /*  Indices des cases   */
    for (i=0; i<8; i++)
    {
        SDL_apply_surface(jeuSDL->lettres[i], jeuSDL->surface_ecran, (ORIG_X+8)*TAILLE_CASE, (ORIG_Y+0.4+i)*TAILLE_CASE);
        SDL_FreeSurface(jeuSDL->lettres[i]);

        itoa(i+1, s);
        jeuSDL->lettres[8+i] = TTF_RenderText_Blended(jeuSDL->police10, s, couleurLettre);
        SDL_apply_surface(jeuSDL->lettres[8+i], jeuSDL->surface_ecran, (ORIG_X+7.35-i)*TAILLE_CASE, (ORIG_Y-0.3)*TAILLE_CASE);
        SDL_FreeSurface(jeuSDL->lettres[8+i]);
    }
}

void SdlAffichage(JeuSDL * jeuSDL)
{
    int i, j, x, y, longueur1, longueur2;
    Case * cell;
    Piece * piece;

    Uint32 couleurJoueur = SDL_MapRGB(jeuSDL->surface_ecran->format, 0, 0, 0);  /* noir */
    Uint32 couleurJoueurActif = SDL_MapRGB(jeuSDL->surface_ecran->format, 0, 86, 27);   /* vert  */
    SDL_Color couleurNom = {255, 255, 255};   /* blanc */

    char * joueur1 = getNomJoueur(&jeuSDL->jeu.J1) ;
    char * joueur2 = getNomJoueur(&jeuSDL->jeu.J2) ;

    for (i=0 ; i < 8 ; i++)
    {
        for (j=0; j < 8 ; j++)
        {
            cell = getCase(&(jeuSDL->jeu.plateau), i, j);
            x = i+ORIG_X;
            y = j+ORIG_Y;
            piece = getPieceCase(cell);

            if (getCouleurCase(cell) == CROUGE)
                SDL_apply_surface(jeuSDL->surface_ROUGE, jeuSDL->surface_ecran, x*TAILLE_CASE, y*TAILLE_CASE) ;
            else if (getCouleurCase(cell) == CBLEU)
                SDL_apply_surface(jeuSDL->surface_BLEU, jeuSDL->surface_ecran, x*TAILLE_CASE, y*TAILLE_CASE) ;
            else if(getCouleurCase(cell) == CBLANC)
                SDL_apply_surface(jeuSDL->surface_BLANC, jeuSDL->surface_ecran, x*TAILLE_CASE, y*TAILLE_CASE) ;
            else
                SDL_apply_surface(jeuSDL->surface_NOIR, jeuSDL->surface_ecran, x*TAILLE_CASE, y*TAILLE_CASE) ;

            if (piece != NULL)
                SdlAffichePiece(jeuSDL, x*TAILLE_CASE, y*TAILLE_CASE, piece);
        }
    }

/*  affichage du nom des joueurs    */

    if (jeuSDL->jeu.joueurActif == &jeuSDL->jeu.J1)
    {
        dessineRectangle(jeuSDL->surface_ecran, (ORIG_X-2)*TAILLE_CASE, ORIG_Y*TAILLE_CASE, 8*TAILLE_CASE, 1*TAILLE_CASE, couleurJoueur);
        dessineRectangle(jeuSDL->surface_ecran, (ORIG_X+9)*TAILLE_CASE, ORIG_Y*TAILLE_CASE, 8*TAILLE_CASE, 1*TAILLE_CASE, couleurJoueurActif);
    }
    else
    {
        dessineRectangle(jeuSDL->surface_ecran, (ORIG_X-2)*TAILLE_CASE, ORIG_Y*TAILLE_CASE, 8*TAILLE_CASE, 1*TAILLE_CASE, couleurJoueurActif);
        dessineRectangle(jeuSDL->surface_ecran, (ORIG_X+9)*TAILLE_CASE, ORIG_Y*TAILLE_CASE, 8*TAILLE_CASE, 1*TAILLE_CASE, couleurJoueur);
    }

    jeuSDL->surface_texteJ1 = TTF_RenderText_Blended(jeuSDL->policeNom, joueur1, couleurNom);
    jeuSDL->surface_texteJ2 = TTF_RenderText_Blended(jeuSDL->policeNom, joueur2, couleurNom);

    longueur1 = jeuSDL->surface_texteJ1->w ;
    longueur2 = jeuSDL->surface_texteJ2->w ;

    SDL_apply_surface(jeuSDL->surface_texteJ1, jeuSDL->surface_ecran, (ORIG_X+9)*TAILLE_CASE, ORIG_Y*TAILLE_CASE+(8*TAILLE_CASE-longueur1)/2);
    SDL_apply_surface(jeuSDL->surface_texteJ2, jeuSDL->surface_ecran, (ORIG_X-2)*TAILLE_CASE, ORIG_Y*TAILLE_CASE+(8*TAILLE_CASE-longueur2)/2);

    SDL_FreeSurface(jeuSDL->surface_texteJ1);
    SDL_FreeSurface(jeuSDL->surface_texteJ2);

}

void SdlVictoire(JeuSDL * jeuSDL, Joueur * joueurVainqueur)
{
    int longueur;

    SDL_Color rouge = {255, 0, 0};
    char * texte = getNomJoueur(joueurVainqueur) ;

    jeuSDL->surface_vainqueur = TTF_RenderText_Blended(jeuSDL->police40, "Vainqueur", rouge);
    longueur = jeuSDL->surface_vainqueur->w;
    SDL_apply_surface(jeuSDL->surface_vainqueur, jeuSDL->surface_ecran, (ORIG_X+2)*TAILLE_CASE, ORIG_Y*TAILLE_CASE+(8*TAILLE_CASE-longueur)/2);
    SDL_FreeSurface(jeuSDL->surface_vainqueur);

    jeuSDL->surface_vainqueur = TTF_RenderText_Blended(jeuSDL->police40, texte, rouge);
    longueur = jeuSDL->surface_vainqueur->w;

    if(joueurVainqueur == &(jeuSDL->jeu.J1))
    {
        SDL_apply_surface(jeuSDL->surface_vainqueur, jeuSDL->surface_ecran, (ORIG_X+4)*TAILLE_CASE, ORIG_Y*TAILLE_CASE+(8*TAILLE_CASE-longueur)/2);
    }
    else
    {
        SDL_apply_surface(jeuSDL->surface_vainqueur, jeuSDL->surface_ecran, (ORIG_X+4)*TAILLE_CASE, ORIG_Y*TAILLE_CASE+(8*TAILLE_CASE-longueur)/2);
    }
    SDL_FreeSurface(jeuSDL->surface_vainqueur);

    jeuSDL->surface_vainqueur = TTF_RenderText_Blended(jeuSDL->police10, "echap:quitter      entrer:recommencer", rouge);
    longueur = jeuSDL->surface_vainqueur->w;
    SDL_apply_surface(jeuSDL->surface_vainqueur, jeuSDL->surface_ecran, (ORIG_X+5.5)*TAILLE_CASE, ORIG_Y*TAILLE_CASE+(8*TAILLE_CASE-longueur)/2);
    SDL_FreeSurface(jeuSDL->surface_vainqueur);

    SDL_Flip( jeuSDL->surface_ecran );
}

void SdlBoucle(JeuSDL * jeuSDL)
{
    SDL_Event event;
	int continue_boucle = 1;
	int x = 1000, y = 1000 ;
	int posX, posY ;
	CouleurCase couleurTemp ;
	bool selectionne = 0 ;
	Piece* piece ;
	Couleur couleurGagne = -1;

    SdlAffichage(jeuSDL);
    afficheCadre(jeuSDL);
	assert( SDL_Flip( jeuSDL->surface_ecran )!=-1 );

	while ( continue_boucle == 1 )
	{
	    couleurGagne = -1;

		while ( SDL_PollEvent( &event ) )
		{

			if ( event.type == SDL_QUIT )
				continue_boucle = 0;

            if (event.type == SDL_MOUSEMOTION)
            {
                if (caseValide(x, y)) setCouleurCase(getCase(&jeuSDL->jeu.plateau, x, y), couleurTemp);


                SDL_GetMouseState(&y, &x) ;
                x = (x/TAILLE_CASE) - ORIG_X;
                y = (y/TAILLE_CASE) - ORIG_Y;
                if (caseValide(x, y))
                {
                    couleurTemp = getCouleurCase(getCase(&jeuSDL->jeu.plateau, x, y)) ;
                    setCouleurCase(getCase(&jeuSDL->jeu.plateau, x, y), CROUGE);
                    piece = getPieceCase(getCase(&jeuSDL->jeu.plateau, x, y));
                    afficheInfosPiece(jeuSDL, piece);
                }
            }

            if (event.type == SDL_MOUSEBUTTONDOWN && caseValide(x, y))
            {
                if (couleurTemp == CBLEU && selectionne != 0 && (posX != x || posY != y))
                {
                    deplacerPiece(&jeuSDL->jeu, getPieceCase(getCase(&jeuSDL->jeu.plateau, posX, posY)), x, y, &couleurGagne) ;
                    afficheLogs(jeuSDL) ;
                    reinitCouleursEchiquier(&jeuSDL->jeu.plateau) ;
                    couleurTemp = (x+y)%2 ;

                    if(couleurGagne == -1)
                    {
                        if (jeuSDL->jeu.joueurActif == &jeuSDL->jeu.J1) setJoueurActif(&jeuSDL->jeu, &jeuSDL->jeu.J2);
                        else setJoueurActif(&jeuSDL->jeu, &jeuSDL->jeu.J1);
                    }
                    selectionne = 0 ;
                }
                else
                {
                    selectPiece(&jeuSDL->jeu, x, y) ;
                    couleurTemp = getCouleurCase(getCase(&jeuSDL->jeu.plateau, x, y)) ;
                    piece = getPieceCase(getCase(&jeuSDL->jeu.plateau, x, y)) ;
                    selectionne = (piece!= NULL) && (getCouleurPiece(piece) == getCouleurJoueur(getJoueurActif(&jeuSDL->jeu))) ;
                    posX = x ;
                    posY = y ;
                }
            }
            if ( event.type == SDL_KEYDOWN )
			{
				switch ( event.key.keysym.sym )
				{
				case SDLK_ESCAPE:
					continue_boucle = 0;
					break;
				default:
				    break;
				}
			}

			SdlAffichage(jeuSDL);
            SDL_Flip( jeuSDL->surface_ecran );
		}



        if(couleurGagne != -1)
        {
            if(getCouleurJoueur(&jeuSDL->jeu.J1) == couleurGagne)
                SdlVictoire(jeuSDL, &jeuSDL->jeu.J1) ;
            else
                SdlVictoire(jeuSDL, &jeuSDL->jeu.J2) ;

            continue_boucle = ChoixRecommencer() ;
        }

        if(continue_boucle == 2)
        {
            Couleur C1 = getCouleurJoueur(&jeuSDL->jeu.J1);
            Couleur C2 = getCouleurJoueur(&jeuSDL->jeu.J2);

            viderPlateau(&jeuSDL->jeu.plateau);
            initPlateau(&jeuSDL->jeu.plateau, C1, C2);
            setJoueurActif(&jeuSDL->jeu, &jeuSDL->jeu.J1);

            reinitCouleursEchiquier(&jeuSDL->jeu.plateau) ;

            continue_boucle = 1;
        }

        usleep(10000);
	}

}
