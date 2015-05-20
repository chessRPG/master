#ifndef _AFFICHESDL_H
#define _AFFICHESDL_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>

#include <assert.h>
#include <time.h>
#include <stdio.h>

#include "jeu.h"

typedef struct
{
    Jeu jeu;

    SDL_Surface* surface_ecran ;

    SDL_Surface* surface_T1 ;
    SDL_Surface* surface_C1 ;
    SDL_Surface* surface_F1 ;
    SDL_Surface* surface_D1 ;
    SDL_Surface* surface_R1 ;
    SDL_Surface* surface_P1 ;

    SDL_Surface* surface_T2 ;
    SDL_Surface* surface_C2 ;
    SDL_Surface* surface_F2 ;
    SDL_Surface* surface_D2 ;
    SDL_Surface* surface_R2 ;
    SDL_Surface* surface_P2 ;

    SDL_Surface* surface_BLANC ;
    SDL_Surface* surface_NOIR ;
    SDL_Surface* surface_BLEU ;
    SDL_Surface* surface_ROUGE ;

    SDL_Surface* surface_texteJ1 ;
    SDL_Surface* surface_texteJ2 ;
    SDL_Surface* surface_texteInfos ;

    SDL_Surface* surface_vainqueur;

    SDL_Surface* lettres[16];

    TTF_Font* policeNom;
    TTF_Font* police10;
    TTF_Font* police40;

    SDL_Surface* logs[10] ;


} JeuSDL ;

void SdlInit(JeuSDL * jeuSdl) ;
void SdlAffichage(JeuSDL * jeuSDL) ;
void SdlVictoire(JeuSDL * jeuSDL, Joueur * joueurVainqueur) ;
void SdlBoucle(JeuSDL * jeuSDL) ;
void SdlLibere(JeuSDL * jeuSDL) ;

#endif
