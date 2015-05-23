#include "afficheNCURSES.h"
#include <string.h>

void secureNom(char* nomSecure, char* nom)
{
    int cpt = 0;

    while(cpt < 12 && nom[cpt] != '\0')
    {
        nomSecure[cpt] = nom[cpt];
        cpt++;
    }
    nomSecure[cpt] = '\0';
}

void NcursesInit(Jeu * jeu)
{
    char nom1[13];
    char nom2[13];
    char nom[32];

    system("clear");
    printf("Saisir le nom du Joueur 1: ");
    scanf("%s", nom);
    secureNom(nom1, nom);

    printf("Saisir le nom du Joueur 2 : ");
    scanf("%s", nom);
    secureNom(nom2, nom);

    system("clear");

    initJeu(jeu, nom1, nom2, BLANC, NOIR); /*Pas de couleurs donc BLANC et NOIR par défaut*/
}

void affichePiece(WINDOW * win, Jeu * jeu, int i, int j, Piece * piece)
{
    Type type = getTypePiece(piece) ;

    switch (type)
    {
    case TOUR:
        if (getCouleurPiece(piece) == getCouleurJoueur(&jeu->J1)) mvwprintw(win, i, j, "T") ;
        else mvwprintw(win, i, j, "t") ;
        break ;
    case CAVALIER:
        if (getCouleurPiece(piece) == getCouleurJoueur(&jeu->J1)) mvwprintw(win, i, j, "C") ;
        else mvwprintw(win, i, j, "c") ;
        break ;
    case FOU:
        if (getCouleurPiece(piece) == getCouleurJoueur(&jeu->J1)) mvwprintw(win, i, j, "F") ;
        else mvwprintw(win, i, j, "f") ;
        break ;
    case DAME:
        if (getCouleurPiece(piece) == getCouleurJoueur(&jeu->J1)) mvwprintw(win, i, j, "D") ;
        else mvwprintw(win, i, j, "d") ;
        break ;
    case ROI:
        if (getCouleurPiece(piece) == getCouleurJoueur(&jeu->J1)) mvwprintw(win, i, j, "R") ;
        else mvwprintw(win, i, j, "r") ;
        break ;
    default: /* pion */
        if (getCouleurPiece(piece) == getCouleurJoueur(&jeu->J1)) mvwprintw(win, i, j, "P") ;
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
                affichePiece(win, jeu, i, j, piece) ;
            }
            if(cell->couleurCase == CBLEU)
            {
                mvwprintw(win, i, j, "$") ;
            }
        }
    }
    mvwprintw(win, 0, 9, "%s", getNomJoueur(&jeu->J2));
    mvwprintw(win, 7, 9, "%s", getNomJoueur(&jeu->J1));
    mvwprintw(win, 8, 0, "%s", getNomJoueur(getJoueurActif(jeu)));
}

void boucleEvent(Jeu * jeu)
{
    WINDOW * win ;
    int continue_boucle ;
    int y = 0, x = 0; /*coordonées du curseur : y ligne, x colonne*/
    int posX = 0, posY = 0;
    int c;
    Couleur couleurGagne;

    initscr() ; //initialisation Ncurses
    clear() ;   //efface écran
    noecho() ;  //n'affiche pas les touches saisies
    cbreak() ;  //permet de ne pas appuyer sur entrer pour une saisie
    win = newwin(9, 40, 0, 0) ;
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
                if(getCouleurCase(getCase(&jeu->plateau, y, x)) == CBLEU && (posX != x || posY != y))
                {
                    deplacerPiece(jeu, getPieceCase(getCase(&jeu->plateau, posY, posX)), y, x, &couleurGagne);
                    reinitCouleursEchiquier(&jeu->plateau);
                    if(getJoueurActif(jeu) == &(jeu->J1))
                        setJoueurActif(jeu, &(jeu->J2));
                    else
                        setJoueurActif(jeu, &(jeu->J1));
                }
                else
                {
                    selectPiece(jeu, y, x);
                    posX = x;
                    posY = y;
                }
                break;
            /*case ' ':
                if(getJoueurActif(jeu) == &(jeu->J1))
                    setJoueurActif(jeu, &(jeu->J2));
                else
                    setJoueurActif(jeu, &(jeu->J1));
                break;*/
            case 27: /* ECHAP */
                continue_boucle = 0;
                break;
            default:
                break;
        }
        affichage(win, jeu);
        wmove(win, y, x);

        wrefresh(win);

        usleep(10000);
    }
    assert(delwin(win)!=ERR);
    endwin();
}
