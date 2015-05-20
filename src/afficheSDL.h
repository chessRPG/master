/**

@brief Module d'affichage du jeu en utilisant SDL
@author GONDRAS Pierre-Louis, GREYL Robin, SCHREYECK Tiffanie
@file src/afficheSDL.h
@version 1.0
@date 2015/05/22

*/

#ifndef _AFFICHESDL_H
#define _AFFICHESDL_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>

#include "jeu.h"

/**
@struct JeuSDL
@brief

@param surface_ecran adresse de la surface utilisée par la fenetre de jeu

@param surface_T1 adresse de la surface utilisée pour stocker l'image de la tour du joueur 1
@param surface_C1 adresse de la surface utilisée pour stocker l'image du cavalier du joueur 1
@param surface_F1 adresse de la surface utilisée pour stocker l'image du fou du joueur 1
@param surface_D1 adresse de la surface utilisée pour stocker l'image de la dame du joueur 1
@param surface_R1 adresse de la surface utilisée pour stocker l'image du roi du joueur 1
@param surface_P1 adresse de la surface utilisée pour stocker l'image des pions du joueur 1

@param surface_T2 adresse de la surface utilisée pour stocker l'image de la tour du joueur 2
@param surface_C2 adresse de la surface utilisée pour stocker l'image du cavalier du joueur 2
@param surface_F2 adresse de la surface utilisée pour stocker l'image du fou du joueur 2
@param surface_D2 adresse de la surface utilisée pour stocker l'image de la dame du joueur 2
@param surface_R2 adresse de la surface utilisée pour stocker l'image du roi du joueur 2
@param surface_P2 adresse de la surface utilisée pour stocker l'image des pions du joueur 2

@param surface_BLANC adresse de la surface utilisée pour stocker l'image des cases blanches
@param surface_NOIR adresse de la surface utilisée pour stocker l'image des cases noires
@param surface_BLEU adresse de la surface utilisée pour stocker l'image des cases bleues (destination possible d'une piece selectionnée)
@param surface_ROUGE adresse de la surface utilisée pour stocker l'image des cases rouges (case visée par le pointeur de la souris)

@param surface_texteJ1 adresse de la surface utilisée pour afficher le nom du Joueur 1
@param surface_texteJ2 adresse de la surface utilisée pour afficher le nom du Joueur 2
@param surface_texteInfos adresse de la surface utilisée pour afficher les informations sur la pièce survolée

@param surface_vainqueur adresse de la surface utilisée pour afficher le nom du joueur vainqueur et les choix possibles (recommencer / quitter)

@param lettres tableau de 16 surfaces qui permettent d'afficher la lettre et le nombre associé à chaque ligne et colonne

@param policeNom adresse de la police utilisée pour les noms des joueurs
@param police10 adresse de la police utilisée pour l'affichage des logs, des informations sur les pièces, et de la légende autour de l'échiquier
@param police40 adresse de la police utilisée pour afficher le nom du vainqueur en fin de partie et la plupart du texte lors du choix du nom du joueur

@param logs tableau de 10 surfaces qui permettent d'afficher les logs de combat et de déplacement

@see jeu
*/

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
void SdlBoucle(JeuSDL * jeuSDL) ;
void SdlLibere(JeuSDL * jeuSDL) ;

#endif
