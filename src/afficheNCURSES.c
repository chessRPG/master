#include "afficheNCURSES.h"
#include <string.h>

void affichePiece(WINDOW * win, int i, int j, Piece * piece)
{
    Type type = getTypePiece(piece) ;

    switch (type)
    {
    case TOUR:
        if (getCouleurPiece(piece) == 0) mvwprintw(win, i, j, "T") ;
        else mvwprintw(win, i, j, "t") ;
        break ;
    case CAVALIER:
        if (getCouleurPiece(piece) == 0) mvwprintw(win, i, j, "C") ;
        else mvwprintw(win, i, j, "c") ;
        break ;
    case FOU:
        if (getCouleurPiece(piece) == 0) mvwprintw(win, i, j, "F") ;
        else mvwprintw(win, i, j, "f") ;
        break ;
    case DAME:
        if (getCouleurPiece(piece) == 0) mvwprintw(win, i, j, "D") ;
        else mvwprintw(win, i, j, "d") ;
        break ;
    case ROI:
        if (getCouleurPiece(piece) == 0) mvwprintw(win, i, j, "R") ;
        else mvwprintw(win, i, j, "r") ;
        break ;
    default: /* pion */
        if (getCouleurPiece(piece) == 0) mvwprintw(win, i, j, "P") ;
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
                mvwprintw(win, i, j, ".") ;
            }
            else
            {
                affichePiece(win, i, j, piece) ;
            }
            if(cell->couleurCase == CBLEU)
            {
                mvwprintw(win, i, j, "$") ;
            }
        }
    }
    mvwprintw(win, 8, 0, "%s", getNomJoueur(getJoueurActif(jeu)));
}

void boucleEvent(Jeu * jeu)
{
    WINDOW * win ;
    int continue_boucle ;
    int y = 0, x = 0; /*coordonées du curseur : y ligne, x colonne*/

    int c;

    initscr() ;
    clear() ;
    noecho() ;
    cbreak() ;
    win = newwin(9, 8, 0, 0) ;
	keypad(win, true);		/* pour que les flèches soient traitées (il faut le faire après création de la fenêtre) */
	nodelay(win,true); /* Pour que l'appel à wgetch soit non-bloquant */

    continue_boucle = 1 ;


    affichage(win, jeu) ;
    wmove(win, y, x);


    while(continue_boucle != 0)
    {
        c = wgetch(win);

        switch(c)
        {
            case KEY_LEFT:
                if(x>0) x--;
                break;
            case KEY_RIGHT:
                if (x<7) x++;
                break;
            case KEY_UP:
                if(y>0) y--;
                break;
            case KEY_DOWN:
                if (y<7) y++;
                break;
            case KEY_BACKSPACE:
                selectPiece(jeu, y, x);
                break;
            case ' ':
                if(getJoueurActif(jeu) == &(jeu->J1))
                    setJoueurActif(jeu, &(jeu->J2));
                else
                    setJoueurActif(jeu, &(jeu->J1));
                break;
            case 27: /* ECHAP */
                continue_boucle = 0;
                break;
            default:
                break;
        }
        affichage(win, jeu);
        wmove(win, y, x);

    }
    assert(delwin(win)!=ERR);
    endwin();
}
