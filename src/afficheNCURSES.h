#ifndef _NCURSES_H
#define _NCURSES_H

#include <ncurses.h>

#include <assert.h>
#include <time.h>
#include <stdio.h>

#include "jeu.h"

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


void NcursesInit(JeuNCURSES * jeuNcurses) ;

void NcursesVictoire(JeuNCURSES * jeuNcurses, Joueur * joueur) ;

int NcursesChoixRecommencer(JeuNCURSES * jeuNcurses) ;

void affichagePlateau(JeuNCURSES * jeuNcurses) ;

void boucleEvent(JeuNCURSES * jeuNcurses);

void NcursesLibere(JeuNCURSES * jeuNcurses);


#endif
