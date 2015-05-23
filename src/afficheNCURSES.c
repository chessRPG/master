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

int maximum(int a, int b)
{
    if(a >= b) return a;
    else return b;
}

void NcursesAfficheInfosPiece(JeuNCURSES * jeuNcurses, Piece * piece)
{
    if (piece != NULL)
    {
        werase(jeuNcurses->stats);
        mvwprintw(jeuNcurses->stats, 1, 1, "Type : %s Couleur : %s", getType(getTypePiece(piece)), getCouleur(getCouleurPiece(piece)));
        mvwprintw(jeuNcurses->stats, 2, 1, "PT Vie : %d  PT Attaque : %d", getPointsVie(piece), getPointsAttaque(piece));
        box(jeuNcurses->stats,ACS_VLINE,ACS_HLINE) ; /* bordures du fond */
        wrefresh(jeuNcurses->stats);
    }
}
void NcursesAfficheJoueurActif(JeuNCURSES * jeuNcurses, Joueur * joueurActif)
{
    werase(jeuNcurses->jActif);
    mvwprintw(jeuNcurses->jActif, 1, 1, "Tour de %s", getNomJoueur(joueurActif));
    box(jeuNcurses->jActif,ACS_VLINE,ACS_HLINE);
    wrefresh(jeuNcurses->jActif);
}

void NcursesInit(JeuNCURSES * jeuNcurses)
{
    char nom1[13];
    char nom2[13];
    char nom[32];
    int ecranX, ecranY;
    int tailleNomJ1, tailleNomJ2;

    system("clear");
    printf("Saisir le nom du Joueur 1: ");
    scanf("%s", nom);
    secureNom(nom1, nom);

    printf("Saisir le nom du Joueur 2 : ");
    scanf("%s", nom);
    secureNom(nom2, nom);

    system("clear");

    initJeu(&jeuNcurses->jeu, nom1, nom2, BLANC, NOIR); /*Pas de couleurs donc BLANC et NOIR par défaut*/

    tailleNomJ1 = strlen(getNomJoueur(&jeuNcurses->jeu.J1));
    tailleNomJ2 = strlen(getNomJoueur(&jeuNcurses->jeu.J2));


    initscr() ; //initialisation Ncurses
    clear() ;   //efface écran
    noecho() ;  //n'affiche pas les touches saisies
    cbreak() ;  //permet de ne pas appuyer sur entrer pour une saisie

    getmaxyx(stdscr, ecranY, ecranX);

    jeuNcurses->fond = newwin(20, 60, (ecranY-20)/2, (ecranX-60)/2) ;
	box(jeuNcurses->fond,ACS_VLINE,ACS_HLINE) ; /* bordures du fond */
	mvwprintw(jeuNcurses->fond, 4, 2+(12-tailleNomJ2)/2, "%s", getNomJoueur(&jeuNcurses->jeu.J2));
	mvwprintw(jeuNcurses->fond, 15, 2+(12-tailleNomJ1)/2, "%s", getNomJoueur(&jeuNcurses->jeu.J1));
    wrefresh(jeuNcurses->fond);

    jeuNcurses->jActif = newwin(3, maximum(tailleNomJ1, tailleNomJ2)+10, 16+(ecranY-20)/2, 1+(58-maximum(tailleNomJ1, tailleNomJ2)-8)/2+(ecranX-60)/2)  ;
	NcursesAfficheJoueurActif(jeuNcurses, getJoueurActif(&jeuNcurses->jeu));

	jeuNcurses->stats = newwin(4, 33, 1+(ecranY-20)/2, 19+(ecranX-60)/2);

	jeuNcurses->logs = newwin(11, 39, 5+(ecranY-20)/2, 16+(ecranX-60)/2);
	box(jeuNcurses->logs,ACS_VLINE,ACS_HLINE);
	mvwprintw(jeuNcurses->logs, 1, 1, "----------- ChessRPG logs -----------");
	wrefresh(jeuNcurses->logs);

    jeuNcurses->echiquier = newwin(10, 10, 5+(ecranY-20)/2, 3+(ecranX-60)/2) ;
	keypad(jeuNcurses->echiquier, true);		/* pour que les flèches soient traitées (il faut le faire après création de la fenêtre) */
	nodelay(jeuNcurses->echiquier,true); /* Pour que l'appel à wgetch soit non-bloquant */
	box(jeuNcurses->echiquier,ACS_VLINE,ACS_HLINE) ; /* bordures de l'échiquier */
}

void NcursesVictoire(JeuNCURSES * jeuNcurses, Joueur * joueur)
{

}

int NcursesChoixRecommencer()
{
    return 0;
}

void NcursesLibere(JeuNCURSES * jeuNcurses)
{
    assert(delwin(jeuNcurses->echiquier)!=ERR);
    assert(delwin(jeuNcurses->fond)!=ERR);
    assert(delwin(jeuNcurses->jActif)!=ERR);
    assert(delwin(jeuNcurses->logs)!=ERR);
    assert(delwin(jeuNcurses->stats)!=ERR);
    endwin();

    detruireJeu(&jeuNcurses->jeu);
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

void affichagePlateau(WINDOW * win, Jeu * jeu)
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
                mvwprintw(win, i+1, j+1, ".") ;
            }
            else
            {
                affichePiece(win, jeu, i+1, j+1, piece) ;
            }
            if(cell->couleurCase == CBLEU)
            {
                mvwprintw(win, i+1, j+1, "$") ;
            }
        }
    }
}

void boucleEvent(JeuNCURSES * jeuNcurses)
{
    int continue_boucle ;
    int y = 0, x = 0; /*coordonées du curseur : y ligne, x colonne*/
    int posX = 0, posY = 0;
    int c;
    Couleur couleurGagne = -1;

    continue_boucle = 1 ;


    affichagePlateau(jeuNcurses->echiquier, &jeuNcurses->jeu) ;
    wmove(jeuNcurses->echiquier, y, x);


    while(continue_boucle == 1)
    {
        c = wgetch(jeuNcurses->echiquier);

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
            case ' ':

                if(getCouleurCase(getCase(&jeuNcurses->jeu.plateau, y, x)) == CBLEU && (posX != x || posY != y))
                {
                    deplacerPiece(&jeuNcurses->jeu, getPieceCase(getCase(&jeuNcurses->jeu.plateau, posY, posX)), y, x, &couleurGagne);
                    reinitCouleursEchiquier(&jeuNcurses->jeu.plateau);

                    if (couleurGagne == -1) //les deux rois sont vivants, on continue !
                    {
                        if(getJoueurActif(&jeuNcurses->jeu) == &(jeuNcurses->jeu.J1))
                            setJoueurActif(&jeuNcurses->jeu, &(jeuNcurses->jeu.J2));
                        else
                            setJoueurActif(&jeuNcurses->jeu, &(jeuNcurses->jeu.J1));

                        NcursesAfficheJoueurActif(jeuNcurses, getJoueurActif(&jeuNcurses->jeu));
                    }
                }
                else
                {
                    selectPiece(&jeuNcurses->jeu, y, x);
                    posX = x;
                    posY = y;
                }
                break;
            case 27: /* ECHAP */
                continue_boucle = 0;
                break;
            default:
                break;
        }
        affichagePlateau(jeuNcurses->echiquier, &jeuNcurses->jeu);
        wmove(jeuNcurses->echiquier, y+1, x+1);
        NcursesAfficheInfosPiece(jeuNcurses, getPieceCase(getCase(&jeuNcurses->jeu.plateau, y, x)));

        wrefresh(jeuNcurses->echiquier);

        if(couleurGagne != -1)
        {
            if(getCouleurJoueur(&jeuNcurses->jeu.J1) == couleurGagne)
                NcursesVictoire(jeuNcurses, &jeuNcurses->jeu.J1) ;
            else
                NcursesVictoire(jeuNcurses, &jeuNcurses->jeu.J2) ;

            continue_boucle = NcursesChoixRecommencer() ;
        }

        if(continue_boucle == 2)
        {
            Couleur C1 = getCouleurJoueur(&jeuNcurses->jeu.J1);
            Couleur C2 = getCouleurJoueur(&jeuNcurses->jeu.J2);

            viderPlateau(&jeuNcurses->jeu.plateau);
            initPlateau(&jeuNcurses->jeu.plateau, C1, C2);
            setJoueurActif(&jeuNcurses->jeu, &jeuNcurses->jeu.J1);

            reinitCouleursEchiquier(&jeuNcurses->jeu.plateau) ;

            continue_boucle = 1;
        }

        usleep(10000);
    }
}
