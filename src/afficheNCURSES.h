/**

@brief Module d'affichage du jeu en utilisant NCURSES
@author GONDRAS Pierre-Louis, GREYL Robin, SCHREYECK Tiffanie
@file src/afficheNCURSES.h
@version 1.0
@date 2015/05/22

*/

#ifndef _NCURSES_H
#define _NCURSES_H
#ifdef FOR_WINDOWS
#include <curses.h>
#else
#include <ncurses.h>
#endif /*FOR_WINDOWS*/

#include <assert.h>
#include <time.h>
#include <stdio.h>

#include "jeu.h"

/**
@struct JeuNCURSES
@brief

@param echiquier adresse de la fenetre contenant l'echiquier
@param fond adresse de la fenetre contenant le fond du jeu
@param jActif adresse de la fenetre affichant le nom du joueur actif
@param stats adresse de la fenetre affichant les statistiques de la piece selectionnee (type, couleur, pt vie, pt attaque)
@param logs adresse de la fenetre affichant les logs de combats et de déplacements
@param victoire adresse de la fenetre affichant le nom du vainqueur


@see jeu
*/

typedef struct
{
    Jeu jeu;

    WINDOW * echiquier ;
    WINDOW * fond;
    WINDOW * jActif;
    WINDOW * stats ;
    WINDOW * logs;
    WINDOW * victoire;

}JeuNCURSES;

/**
@brief Permet la saisie dans nom du nom du joueur numero J. maximum 12 caractères
@param jeuNcurses adresse de la structure où sont stoquées les fenetres et je jeu
@param nom chaine de caractère où le nom du joueur sera stocké
@param J numero du joueur (1 ou 2)
@return Aucun
*/
void NcursesSaisieNomJoueur(JeuNCURSES * jeuNcurses, char * nom, int J);

/**
@brief initialise la partie et les fenêtres
@param jeuNcurses adresse du jeu à initialiser
@return Aucun
*/
void NcursesInit(JeuNCURSES * jeuNcurses) ;

/**
@brief affiche le joueur vainqueur
@param jeuNcurses adresse de la structure où sont stoquées les fenetres et je jeu
@param joueur joueur vainqueur
@return Aucun
*/
void NcursesVictoire(JeuNCURSES * jeuNcurses, Joueur * joueur) ;

/**
@brief propose au joueur de recommencer ou de quitter
@param jeuNcurses adresse de la structure où sont stoquées les fenetres et je jeu
@return Aucun
*/
int NcursesChoixRecommencer(JeuNCURSES * jeuNcurses) ;

/**
@brief affiche le plateau dans la fentre echiquier
@param jeuNcurses adresse de la structure où sont stoquées les fenetres et je jeu
@return Aucun
*/
void affichagePlateau(JeuNCURSES * jeuNcurses) ;

/**
@brief fonction principale qui appelle toute les autres fonctions nécessaires au déroulement de la partie
@param jeuNcurses adresse de la structure où sont stoquées les fenetres et je jeu
@return Aucun
*/
void boucleEvent(JeuNCURSES * jeuNcurses);

/**
@brief libère tout ce qui a été aloué par NcursesInit
@param jeuNcurses adresse de la structure où sont stoquées les fenetres et je jeu
@return Aucun
*/
void NcursesLibere(JeuNCURSES * jeuNcurses);


#endif
