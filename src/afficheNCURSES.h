#ifndef _NCURSES_H
#define _NCURSES_H

#include <ncurses.h>
#include <assert.h>
#include <time.h>
#include <stdio.h>

#include "jeu.h"

void NcursesInit(Jeu * jeu);
void affichage(WINDOW * win, Jeu * jeu) ;
void boucleEvent(Jeu * jeu);

#endif
