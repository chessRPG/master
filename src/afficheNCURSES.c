#include "afficheNCURSES.h"

void affichePiece(WINDOW * win, int i, int j, Piece * piece)
{
    Type type = piece->type ;

    switch (type)
    {
    case TOUR:
        if (piece->couleur == 0) mvwprintw(win, i, j, "T") ;
        else mvwprintw(win, i, j, "t") ;
        break ;
    case CAVALIER:
        if (piece->couleur == 0) mvwprintw(win, i, j, "C") ;
        else mvwprintw(win, i, j, "c") ;
        break ;
    case FOU:
        if (piece->couleur == 0) mvwprintw(win, i, j, "F") ;
        else mvwprintw(win, i, j, "f") ;
        break ;
    case DAME:
        if (piece->couleur == 0) mvwprintw(win, i, j, "D") ;
        else mvwprintw(win, i, j, "d") ;
        break ;
    case ROI:
        if (piece->couleur == 0) mvwprintw(win, i, j, "R") ;
        else mvwprintw(win, i, j, "r") ;
        break ;
    default: /* pion */
        if (piece->couleur == 0) mvwprintw(win, i, j, "P") ;
        else mvwprintw(win, i, j, "p") ;
        break ;
    }
}

void affichage(WINDOW * win, Jeu * jeu)
{
    int i, j ;
    Case * cell ;
    Piece * piece ;

    for(i = 0 ; i < 8 ; i++)
    {
        for(j = 0 ; j < 8 ; j++)
        {
            cell = getCase(&(jeu->plateau), i, j) ;
            piece = getPieceCase(cell) ;

            if(piece == NULL)
            {
                mvwprintw(win, i, j, " ") ;
            }
            else
            {
                affichePiece(win, i, j, piece) ;
            }
        }
    }
}

void boucleEvent(Jeu * jeu)
{
    WINDOW * win ;
    int continue_boucle ;
    int i ;
    char c ;

    initscr() ;
    clear() ;
    noecho() ;
    cbreak() ;

    win = newwin(8, 8, 0, 0) ;

    continue_boucle = 1 ;

    printf("coucou") ;

    affichage(win, jeu) ;

    while(1)
    {
        c = wgetch(win) ;
        if((c - '0') < 8)
        {
            if(continue_boucle == 1)
            {
                for(i = 0 ; i < 8 ; i++)
                {
                    mvwprintw(win, i, c - '0', "#") ;
                }
                continue_boucle = 2 ;
            }
            else
            {
                for(i = 0 ; i < 8 ; i++)
                {
                    mvwprintw(win, c - '0', i, "*") ;
                }
                continue_boucle = 1 ;
            }
        }
    }
}
