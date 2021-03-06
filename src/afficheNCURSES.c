#include "afficheNCURSES.h"
#include "ia.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* il faut répéter la déclaration de la fonction ici pour ne pas déclencher de warning à la compilation avec pedantic et ansi */
#ifndef FOR_WINDOWS
extern int usleep(__useconds_t __useconds);
#endif /*FOR_WINDOWS*/

const short TAILLE_FOND_X = 70;
const short TAILLE_FOND_Y = 20;

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
    werase(jeuNcurses->stats);

    if (piece != NULL)
    {
        mvwprintw(jeuNcurses->stats, 1, 1, "Type : %s", getType(getTypePiece(piece)));
        mvwprintw(jeuNcurses->stats, 1, 17, "Couleur : %s", getCouleur(getCouleurPiece(piece)));
        mvwprintw(jeuNcurses->stats, 2, 1, "PT Vie : %d ", getPointsVie(piece));
        mvwprintw(jeuNcurses->stats, 2, 16, "PT Attaque : %d",getPointsAttaque(piece));
    }
    else
    {
        mvwprintw(jeuNcurses->stats, 1, 1, "Type : NULL");
        mvwprintw(jeuNcurses->stats, 1, 17, "Couleur : NULL");
        mvwprintw(jeuNcurses->stats, 2, 1, "PT Vie : 0");
        mvwprintw(jeuNcurses->stats, 2, 16, "PT Attaque : 0");
    }
    box(jeuNcurses->stats,ACS_VLINE,ACS_HLINE) ; /* bordures du fond */
    wrefresh(jeuNcurses->stats);
}

void NcursesAfficheJoueurActif(JeuNCURSES * jeuNcurses)
{
    Joueur * joueurActif = getJoueurActif(&jeuNcurses->jeu);
    char nomJoueurActif[13];
    sprintf(nomJoueurActif, "%s", getNomJoueur(joueurActif));

    werase(jeuNcurses->jActif);
    mvwprintw(jeuNcurses->jActif, 1, 1+((getmaxx(jeuNcurses->jActif)-2)-(strlen(nomJoueurActif)+5))/2, "%s joue", nomJoueurActif);
    box(jeuNcurses->jActif,ACS_VLINE,ACS_HLINE);
    wrefresh(jeuNcurses->jActif);
}

void NcursesAfficheLogs(JeuNCURSES * jeuNcurses)
{
    int i = 3 ;
    char * pch ;

    werase(jeuNcurses->logs);
    box(jeuNcurses->logs, ACS_VLINE, ACS_HLINE);

    pch = strtok(jeuNcurses->jeu.log,",-");
    while(pch != NULL)
    {
        mvwprintw(jeuNcurses->logs, i, (49-strlen(pch))/2, "%s", pch);
        i+= 1 ;
        pch = strtok (NULL, ",-");
    }

    wrefresh(jeuNcurses->logs);
}

void NcursesChoixTypeJeu(JeuNCURSES * jeuNcurses)
{
    char c;

	mvwprintw(jeuNcurses->fond, 1, 1+14, "solo");
	setTypeJeu(&jeuNcurses->jeu, SOLO);
	do
	{
	    werase(jeuNcurses->fond);
	    box(jeuNcurses->fond,ACS_VLINE,ACS_HLINE) ;
	    mvwprintw(jeuNcurses->fond, (TAILLE_FOND_Y-1)/2, (TAILLE_FOND_X-23)/2, "mode de jeu : ");
	    c = wgetch(jeuNcurses->fond);

	    if (c == ' ')
        {
            if(getTypeJeu(&jeuNcurses->jeu) == MULTI) setTypeJeu(&jeuNcurses->jeu, SOLO);
            else setTypeJeu(&jeuNcurses->jeu, MULTI);
        }

	    if(getTypeJeu(&jeuNcurses->jeu) == MULTI) mvwprintw(jeuNcurses->fond, (TAILLE_FOND_Y-1)/2, 14+(TAILLE_FOND_X-23)/2, "2 Joueurs");
	    else mvwprintw(jeuNcurses->fond, (TAILLE_FOND_Y-1)/2, 14+(TAILLE_FOND_X-23)/2, "1 Joueur");

	    mvwprintw(jeuNcurses->fond, TAILLE_FOND_Y-2, (TAILLE_FOND_X-61)/2, "espace : changer de mode                    echap : continuer");

	    wrefresh(jeuNcurses->fond);

	    usleep(100000);
	}while(c != 27 /*echap*/);
}

void NcursesSaisieNomJoueur(JeuNCURSES * jeuNcurses, char * nom, int numeroJoueur)
{
    int cpt = 0;
    char c;

    nom[0] = '\0';
	do
    {
        werase(jeuNcurses->fond);
	    box(jeuNcurses->fond,ACS_VLINE,ACS_HLINE) ;

	    c = wgetch(jeuNcurses->fond);

        mvwprintw(jeuNcurses->fond, (TAILLE_FOND_Y-1)/2-1, (TAILLE_FOND_X-16)/2, "Nom du Joueur %d:", numeroJoueur);
        mvwprintw(jeuNcurses->fond, TAILLE_FOND_Y-2, (TAILLE_FOND_X-53)/2, "espace : effacer                    echap : continuer");

        if(((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) && cpt < 13)
        {
            nom[cpt] = c;
            cpt++;
            nom[cpt] = '\0';
        }
        if(c == ' ' /*espace*/ && cpt > 0)
        {
            cpt--;
            nom[cpt] = '\0';
        }

        if(nom[0] != '\0') mvwprintw(jeuNcurses->fond, (TAILLE_FOND_Y-1)/2, (TAILLE_FOND_X-strlen(nom))/2, nom);

        wrefresh(jeuNcurses->fond);

	    usleep(100000);
    }while(c != 27 /*echap*/ /*&& cpt == 0*/);
}

void NcursesInit(JeuNCURSES * jeuNcurses)
{
    char nom1[13];
    char nom2[13];
    int ecranX, ecranY;
    int tailleNomJ1, tailleNomJ2;

    system("clear");


    initscr() ; /*initialisation Ncurses*/
    clear() ;   /*efface écran*/
    noecho() ;  /*n'affiche pas les touches saisies*/
    cbreak() ;  /*permet de ne pas appuyer sur entrer pour une saisie*/

    getmaxyx(stdscr, ecranY, ecranX);

    jeuNcurses->fond = newwin(TAILLE_FOND_Y, TAILLE_FOND_X, (ecranY-TAILLE_FOND_Y)/2, (ecranX-TAILLE_FOND_X)/2) ;
    keypad(jeuNcurses->fond, 1);
    nodelay(jeuNcurses->fond, 1);
	box(jeuNcurses->fond,ACS_VLINE,ACS_HLINE) ; /* bordures du fond */

	curs_set(0);

	NcursesChoixTypeJeu(jeuNcurses);

	NcursesSaisieNomJoueur(jeuNcurses, nom1, 1);

	if(getTypeJeu(&jeuNcurses->jeu) == MULTI) NcursesSaisieNomJoueur(jeuNcurses, nom2, 2);
	else sprintf(nom2, "BOT BOT BOT");

	curs_set(1);

	initJeu(&jeuNcurses->jeu, nom1, nom2, BLANC, NOIR); /*Pas de couleurs donc BLANC et NOIR par défaut*/

	tailleNomJ1 = strlen(getNomJoueur(&jeuNcurses->jeu.J1));
    tailleNomJ2 = strlen(getNomJoueur(&jeuNcurses->jeu.J2));

    werase(jeuNcurses->fond);
    box(jeuNcurses->fond,ACS_VLINE,ACS_HLINE) ;
    mvwprintw(jeuNcurses->fond, 4, 3+(12-tailleNomJ2)/2, "%s", getNomJoueur(&jeuNcurses->jeu.J2));
	mvwprintw(jeuNcurses->fond, 15, 3+(12-tailleNomJ1)/2, "%s", getNomJoueur(&jeuNcurses->jeu.J1));
    wrefresh(jeuNcurses->fond);

    jeuNcurses->jActif = newwin(3, maximum(tailleNomJ1, tailleNomJ2)+7, 16+(ecranY-TAILLE_FOND_Y)/2, 1+((TAILLE_FOND_X-2)-maximum(tailleNomJ1, tailleNomJ2)-8)/2+(ecranX-TAILLE_FOND_X)/2)  ;
	NcursesAfficheJoueurActif(jeuNcurses);

	jeuNcurses->stats = newwin(4, 33, 1+(ecranY-TAILLE_FOND_Y)/2, 17+(49-33)/2+(ecranX-TAILLE_FOND_X)/2);

	jeuNcurses->logs = newwin(11, 49, 5+(ecranY-TAILLE_FOND_Y)/2, 17+(ecranX-TAILLE_FOND_X)/2);
	box(jeuNcurses->logs,ACS_VLINE,ACS_HLINE);
	mvwprintw(jeuNcurses->logs, 1, 1, "---------------- ChessRPG logs ----------------");
	wrefresh(jeuNcurses->logs);

	jeuNcurses->victoire = newwin(13, 40, (ecranY-13)/2, (ecranX-40)/2);

    jeuNcurses->echiquier = newwin(10, 10, 5+(ecranY-TAILLE_FOND_Y)/2, 4+(ecranX-TAILLE_FOND_X)/2) ;
	keypad(jeuNcurses->echiquier, 1);		/* pour que les flèches soient traitées (il faut le faire après création de la fenêtre) */
	nodelay(jeuNcurses->echiquier, 1); /* Pour que l'appel à wgetch soit non-bloquant */
	box(jeuNcurses->echiquier,ACS_VLINE,ACS_HLINE) ; /* bordures de l'échiquier */
}

void NcursesVictoire(JeuNCURSES * jeuNcurses, Joueur * joueur)
{
    char nomVainqueur[13];
    sprintf(nomVainqueur, "%s", getNomJoueur(joueur));

    box(jeuNcurses->victoire,ACS_VLINE,ACS_HLINE) ;
    mvwprintw(jeuNcurses->victoire, 2, (40-10)/2, "VICTOIRE !");
    mvwprintw(jeuNcurses->victoire, 6, (40-(12+strlen(nomVainqueur)))/2, "VAINQUEUR : %s", nomVainqueur);
    mvwprintw(jeuNcurses->victoire, 10, 1, "echap : quiter    espace : recommencer");

    wrefresh(jeuNcurses->victoire);
}

int NcursesChoixRecommencer(JeuNCURSES * jeuNcurses)
{
    int c;

    while(1)
    {
        c = wgetch(jeuNcurses->echiquier);

        switch(c)
        {
            case 27: /* ECHAP */
                return 0;
                break;
            case ' ':
                return 2;
                break;

            default:
                break;
        }
        usleep(10000);
    }
    return 0;
}

void NcursesLibere(JeuNCURSES * jeuNcurses)
{
    assert(delwin(jeuNcurses->echiquier)!=ERR);
    assert(delwin(jeuNcurses->fond)!=ERR);
    assert(delwin(jeuNcurses->jActif)!=ERR);
    assert(delwin(jeuNcurses->logs)!=ERR);
    assert(delwin(jeuNcurses->stats)!=ERR);
    assert(delwin(jeuNcurses->victoire)!=ERR);
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

void affichagePlateau(JeuNCURSES * jeuNcurses)
{
    int i, j ;
    Case * cell ;
    Piece * piece ;

    for(i = 0 ; i < 8 ; i++)
    {
        for(j = 0 ; j < 8 ; j++)
        {
            cell = getCase(&(jeuNcurses->jeu.plateau), i, j) ;
            piece = getPieceCase(cell) ;

            if(piece == NULL)
            {
                mvwprintw(jeuNcurses->echiquier, i+1, j+1, ".") ;
            }
            else
            {
                affichePiece(jeuNcurses->echiquier, &jeuNcurses->jeu, i+1, j+1, piece) ;
            }
            if(cell->couleurCase == CBLEU)
            {
                mvwprintw(jeuNcurses->echiquier, i+1, j+1, "$") ;
            }
        }
    }
}

void boucleEvent(JeuNCURSES * jeuNcurses)
{
    int continue_boucle = 1 ;
    int y = 0, x = 0; /*coordonées du curseur : y ligne, x colonne*/
    int posX = 0, posY = 0;
    int c;

    setCouleurGagnant(&jeuNcurses->jeu, -1);

    NcursesAfficheLogs(jeuNcurses);

    while(continue_boucle == 1)
    {
        setCouleurGagnant(&jeuNcurses->jeu, -1);

        if(getJoueurActif(&jeuNcurses->jeu) == &jeuNcurses->jeu.J2 && getTypeJeu(&jeuNcurses->jeu) == SOLO)
        {
            #ifdef FOR_WINDOWS
            //Sleep(1000);
            #else
            sleep(1);
            #endif /*FOR_WINDOWS*/

            ia(&jeuNcurses->jeu);

            NcursesAfficheLogs(jeuNcurses);
            reinitCouleursEchiquier(&jeuNcurses->jeu.plateau) ;
            setJoueurActif(&jeuNcurses->jeu, getJoueurInactif(&jeuNcurses->jeu));
            affichagePlateau(jeuNcurses);

            wrefresh(jeuNcurses->echiquier);
        }
        else
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
                        deplacerPiece(&jeuNcurses->jeu, getPieceCase(getCase(&jeuNcurses->jeu.plateau, posY, posX)), y, x);
                        reinitCouleursEchiquier(&jeuNcurses->jeu.plateau);
                        NcursesAfficheLogs(jeuNcurses);

                        if (jeuNcurses->jeu.couleurGagnant == -1) /*les deux rois sont vivants, on continue !*/
                        {
                            if(getJoueurActif(&jeuNcurses->jeu) == &(jeuNcurses->jeu.J1))
                                setJoueurActif(&jeuNcurses->jeu, &(jeuNcurses->jeu.J2));
                            else
                                setJoueurActif(&jeuNcurses->jeu, &(jeuNcurses->jeu.J1));

                            NcursesAfficheJoueurActif(jeuNcurses);
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

            NcursesAfficheInfosPiece(jeuNcurses, getPieceCase(getCase(&jeuNcurses->jeu.plateau, y, x)));
            affichagePlateau(jeuNcurses);
            wmove(jeuNcurses->echiquier, y+1, x+1);
            wrefresh(jeuNcurses->echiquier);
        }

        if(jeuNcurses->jeu.couleurGagnant != -1)
        {
            curs_set(0);

            if(getCouleurJoueur(&jeuNcurses->jeu.J1) == jeuNcurses->jeu.couleurGagnant)
                NcursesVictoire(jeuNcurses, &jeuNcurses->jeu.J1) ;
            else
                NcursesVictoire(jeuNcurses, &jeuNcurses->jeu.J2) ;

            continue_boucle = NcursesChoixRecommencer(jeuNcurses) ;

            curs_set(1);
        }

        if(continue_boucle == 2)
        {
            Couleur C1 = getCouleurJoueur(&jeuNcurses->jeu.J1);
            Couleur C2 = getCouleurJoueur(&jeuNcurses->jeu.J2);
            char nom1[13], nom2[13];

            strcpy(nom1, getNomJoueur(&jeuNcurses->jeu.J1));
            strcpy(nom2, getNomJoueur(&jeuNcurses->jeu.J2));

            detruireJeu(&jeuNcurses->jeu);
            initJeu(&jeuNcurses->jeu, nom1, nom2, C1, C2);

            werase(jeuNcurses->victoire);
            wrefresh(jeuNcurses->victoire);

            NcursesAfficheJoueurActif(jeuNcurses);

            NcursesAfficheLogs(jeuNcurses);

            continue_boucle = 1;
            setCouleurGagnant(&jeuNcurses->jeu, -1);
        }

        usleep(10000);
    }
}
