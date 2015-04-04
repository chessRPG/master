#include "jeu.h"

/*  Création/Destruction    */

void initJeu(Jeu * jeu, Couleur C1, Couleur C2)
{
    jeu->plateau = *creerPlateau(C1, C2);
    jeu->J1 = *creerJoueur(C1);
    jeu->J2 = *creerJoueur(C2);
}
/*
void detruireJeu(Jeu * jeu)
{
    detruirePlateau(&jeu->plateau);
    detruireJoueur(&jeu->J1);
    detruireJoueur(&jeu->J2);
}
*/
void reinitCouleursEchiquier(Plateau * plateau)
{
    int i, j;

    for(i = 0 ; i < 8 ; i++)
    {
        for(j = 0 ; j < 8 ; j++)
        {
            setCouleurCase(getCase(plateau, i, j), (i+j)%2);
        }
    }
}

/* Interne */

void coloreLigne(Jeu * jeu, int x, int y)
{
    int i = 1;
    Couleur couleur = getCouleurJoueur(jeu->joueurActif);

    while (caseValide(x, y-i) && getPieceCase(getCase(&(jeu->plateau), x, y-i)) == NULL)
    {
        setCouleurCase(getCase(&(jeu->plateau), x, y-i), CBLEU);
        i++;
    }
    if (caseValide(x, y-i) && getCouleurPiece(getPieceCase(getCase(&(jeu->plateau), x, y-i))) != couleur)
        setCouleurCase(getCase(&(jeu->plateau), x, y-i), CBLEU);

    i = 1;

    while (caseValide(x, y+i) && getPieceCase(getCase(&(jeu->plateau), x, y+i)) == NULL)
    {
        setCouleurCase(getCase(&(jeu->plateau), x, y-i), CBLEU);
        i++;
    }
    if (caseValide(x, y+i) && getCouleurPiece(getPieceCase(getCase(&(jeu->plateau), x, y+i))) != couleur)
        setCouleurCase(getCase(&(jeu->plateau), x, y+i), CBLEU);
}

void coloreColonne(Jeu * jeu, int x, int y)
{
    int i = 1;
    Couleur couleur = getCouleurJoueur(jeu->joueurActif);

    while (caseValide(x-i, y) && getPieceCase(getCase(&(jeu->plateau), x-i, y)) == NULL)
    {
        setCouleurCase(getCase(&(jeu->plateau), x-i, y), CBLEU);
        i++;
    }
    if (caseValide(x-i, y) && getCouleurPiece(getPieceCase(getCase(&(jeu->plateau), x-i, y))) != couleur)
        setCouleurCase(getCase(&(jeu->plateau), x-i, y), CBLEU);

    i = 1;

    while (caseValide(x+i, y) && getPieceCase(getCase(&(jeu->plateau), x+i, y)) == NULL)
    {
        setCouleurCase(getCase(&(jeu->plateau), x+i, y), CBLEU);
        i++;
    }
    if (caseValide(x+i, y) && getCouleurPiece(getPieceCase(getCase(&(jeu->plateau), x+i, y))) != couleur)
        setCouleurCase(getCase(&(jeu->plateau), x+i, y), CBLEU);
}

void coloreDiagonales(Jeu * jeu, int x, int y)
{
    int i = 1;
    Couleur couleur = getCouleurJoueur(jeu->joueurActif);

    while (caseValide(x-i, y-i) && getPieceCase(getCase(&(jeu->plateau), x-i, y-i)) == NULL)
    {
        setCouleurCase(getCase(&(jeu->plateau), x-i, y-i), CBLEU);
        i++;
    }
    if (caseValide(x-i, y-i) && getCouleurPiece(getPieceCase(getCase(&(jeu->plateau), x-i, y-i))) != couleur)
        setCouleurCase(getCase(&(jeu->plateau), x-i, y-i), CBLEU);

    i = 1;

    while (caseValide(x+i, y-i) && getPieceCase(getCase(&(jeu->plateau), x+i, y-i)) == NULL)
    {
        setCouleurCase(getCase(&(jeu->plateau), x+i, y-i), CBLEU);
        i++;
    }
    if (caseValide(x+i, y-i) && getCouleurPiece(getPieceCase(getCase(&(jeu->plateau), x+i, y-i))) != couleur)
        setCouleurCase(getCase(&(jeu->plateau), x+i, y-i), CBLEU);

    i = 1;

    while (caseValide(x-i, y+i) && getPieceCase(getCase(&(jeu->plateau), x-i, y+i)) == NULL)
    {
        setCouleurCase(getCase(&(jeu->plateau), x-i, y+i), CBLEU);
        i++;
    }
    if (caseValide(x-i, y+i) && getCouleurPiece(getPieceCase(getCase(&(jeu->plateau), x-i, y+i))) != couleur)
        setCouleurCase(getCase(&(jeu->plateau), x-i, y+i), CBLEU);

    i = 1;

    while (caseValide(x+i, y+i) && getPieceCase(getCase(&(jeu->plateau), x+i, y+i)) == NULL)
    {
        setCouleurCase(getCase(&(jeu->plateau), x+i, y+i), CBLEU);
        i++;
    }
    if (caseValide(x+i, y+i) && getCouleurPiece(getPieceCase(getCase(&(jeu->plateau), x+i, y+i))) != couleur)
        setCouleurCase(getCase(&(jeu->plateau), x+i, y+i), CBLEU);
}

/* Accesseurs */

Joueur * getJoueurActif(Jeu * jeu)
{
    return jeu->joueurActif;
}

void selectPiece(Jeu * jeu, int posX, int posY)
{
    int i, j, a;
    Joueur * joueur = getJoueurActif(jeu);
    Couleur couleur = getCouleurJoueur(joueur);
    Piece * piece = getPieceCase(getCase(&(jeu->plateau), posX, posY));

    reinitCouleursEchiquier(&(jeu->plateau));

    if(piece != NULL && getCouleurJoueur(joueur) == getCouleurPiece(piece))
    {

        setCouleurCase(getCase(&(jeu->plateau), posX, posY), CBLEU);

        switch(piece->type)
        {

            case PION:

                if (couleur == BLANC)  a = -1;
                else    a = 1;

                if (caseValide(posX+a, posY) && getPieceCase(getCase(&(jeu->plateau), posX+a, posY)) == NULL)
                    setCouleurCase(getCase(&(jeu->plateau), posX+a, posY), CBLEU);
                if (caseValide(posX+a, posY-1) && getPieceCase(getCase(&(jeu->plateau), posX+a, posY-1)) != NULL && getCouleurPiece(getPieceCase(getCase(&(jeu->plateau), posX+a, posY-1))) != couleur)
                    setCouleurCase(getCase(&(jeu->plateau), posX+a, posY-1), CBLEU);
                if (caseValide(posX+a, posY+1) && getPieceCase(getCase(&(jeu->plateau), posX+a, posY+1)) != NULL && getCouleurPiece(getPieceCase(getCase(&(jeu->plateau), posX+a, posY+1))) != couleur)
                    setCouleurCase(getCase(&(jeu->plateau), posX+a, posY+1), CBLEU);
                if (((couleur == BLANC && posX == 6) || (couleur == NOIR && posX == 1)) && (getCouleurCase(getCase(&(jeu->plateau), posX+a, posY)) == CBLEU && getPieceCase(getCase(&(jeu->plateau), posX+2*a, posY)) == NULL))
                    setCouleurCase(getCase(&(jeu->plateau), posX+2*a, posY), CBLEU);

                break ;

            case TOUR:

                coloreLigne(jeu, posX, posY);
                coloreColonne(jeu, posX, posY);

                break ;

            case CAVALIER:

                if (caseValide(posX-2, posY-1) && (getPieceCase(getCase(&(jeu->plateau), posX-2, posY-1)) == NULL || getCouleurPiece(getPieceCase(getCase(&(jeu->plateau), posX-2, posY-1))) != couleur))
                    setCouleurCase(getCase(&(jeu->plateau), posX-2, posY-1), CBLEU);
                if (caseValide(posX-2, posY+1) && (getPieceCase(getCase(&(jeu->plateau), posX-2, posY+1)) == NULL || getCouleurPiece(getPieceCase(getCase(&(jeu->plateau), posX-2, posY+1))) != couleur))
                    setCouleurCase(getCase(&(jeu->plateau), posX-2, posY+1), CBLEU);
                if (caseValide(posX-1, posY-2) && (getPieceCase(getCase(&(jeu->plateau), posX-1, posY-2)) == NULL || getCouleurPiece(getPieceCase(getCase(&(jeu->plateau), posX-1, posY-2))) != couleur))
                    setCouleurCase(getCase(&(jeu->plateau), posX-1, posY-2), CBLEU);
                if (caseValide(posX-1, posY+2) && (getPieceCase(getCase(&(jeu->plateau), posX-1, posY+2)) == NULL || getCouleurPiece(getPieceCase(getCase(&(jeu->plateau), posX-1, posY+2))) != couleur))
                    setCouleurCase(getCase(&(jeu->plateau), posX-1, posY+2), CBLEU);
                if (caseValide(posX+1, posY-2) && (getPieceCase(getCase(&(jeu->plateau), posX+1, posY-2)) == NULL || getCouleurPiece(getPieceCase(getCase(&(jeu->plateau), posX+1, posY-2))) != couleur))
                    setCouleurCase(getCase(&(jeu->plateau), posX+1, posY-2), CBLEU);
                if (caseValide(posX+1, posY+2) && (getPieceCase(getCase(&(jeu->plateau), posX+1, posY+2)) == NULL || getCouleurPiece(getPieceCase(getCase(&(jeu->plateau), posX+1, posY+2))) != couleur))
                    setCouleurCase(getCase(&(jeu->plateau), posX+1, posY+2), CBLEU);
                if (caseValide(posX+2, posY-1) && (getPieceCase(getCase(&(jeu->plateau), posX+2, posY-1)) == NULL || getCouleurPiece(getPieceCase(getCase(&(jeu->plateau), posX+2, posY-1))) != couleur))
                    setCouleurCase(getCase(&(jeu->plateau), posX+2, posY-1), CBLEU);
                if (caseValide(posX+2, posY+1) && (getPieceCase(getCase(&(jeu->plateau), posX+2, posY+1)) == NULL || getCouleurPiece(getPieceCase(getCase(&(jeu->plateau), posX+2, posY+1))) != couleur))
                    setCouleurCase(getCase(&(jeu->plateau), posX+2, posY+1), CBLEU);

                break ;

            case FOU:

                coloreDiagonales(jeu, posX, posY);

                break ;

            case DAME:

                coloreLigne(jeu, posX, posY);
                coloreColonne(jeu, posX, posY);
                coloreDiagonales(jeu, posX, posY);

                break ;

            case ROI:

                for (i = posX-1 ; i<posX+2 ; i++)
                {
                    for (j = posY-1; j<posY+2; j++)
                    {
                        if (caseValide(i, j) && (getPieceCase(getCase(&(jeu->plateau), i, j)) == NULL || getCouleurPiece(getPieceCase(getCase(&(jeu->plateau), i, j))) != couleur))
                            setCouleurCase(getCase(&(jeu->plateau), i, j), CBLEU);
                    }
                }
                break ;

            default:
                printf("type invalide") ;
                return ;
        }
    }

}

/* Mutateurs */

void setJoueurActif(Jeu * jeu, Joueur* joueur)
{
    jeu->joueurActif = joueur;
}

void deplacerPiece(Plateau * plateau, Piece * piece, int posX, int posY)
{
    int i = 0, j = 0;

    while(getPieceCase(getCase(plateau, i, j)) != piece && i < 8)
    {
        while(getPieceCase(getCase(plateau, i, j)) != piece && j < 8)
        {
            j++;
        }
        i++;
    }
    setPieceCase(getCase(plateau, i, j), NULL);

    setPieceCase(getCase(plateau, posX, posY), piece);

    plateau->nbTours++;
}

void combatPieces(Joueur * joueurActif, Piece * pieceJ1, Piece * pieceJ2)
{
    int BONUS = 2;
    Piece * attaquant;
    Piece * defenseur;
    int vie;

    if(getCouleurJoueur(joueurActif) == getCouleurPiece(pieceJ1))
    {
        attaquant = pieceJ1;
        defenseur = pieceJ2;
    }
    else
    {
        attaquant = pieceJ2;
        defenseur = pieceJ1;
    }


    while(getPointsVie(attaquant) > 0 || getPointsVie(defenseur) > 0)
    {
        vie = getPointsVie(defenseur) - getPointsAttaque(attaquant)*BONUS;
        if(vie <= 0)
            setPointsVie(defenseur, 0);
        else
            setPointsVie(defenseur, vie);

        if(getPointsVie(defenseur) > 0)
        {
            vie = getPointsVie(attaquant) - getPointsAttaque(defenseur);
            if(vie <= 0)
                setPointsVie(attaquant, 0);
            else
                setPointsVie(attaquant, vie);
        }
    }
}
