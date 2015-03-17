#ifndef _JEU_H
#define _JEU_H

#include "joueur.h"
#include "plateau.h"

typedef struct
{
    Plateau plateau ;
    Joueur J1 ;
    Joueur J2 ;
    Joueur * joueurActif ;
} Jeu ;

#endif
