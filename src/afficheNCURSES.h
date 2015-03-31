#ifndef _NCURSES_H
#define _NCURSES_H

#include <ncurses.h>
#include <assert.h>
#include <time.h>
#include <stdio.h>

#include "jeu.h"

void affichage(WINDOW * win, Jeu * jeu) ;
void SdlInit(Jeu* jeu) ;

#endif
