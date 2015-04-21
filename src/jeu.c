#include "jeu.h"

/*  Création/Destruction    */

void initJeu(Jeu * jeu, Couleur C1, Couleur C2)
{
    initPlateau(&jeu->plateau, C1, C2);
    initJoueur(&jeu->J1, C1);
    initJoueur(&jeu->J2, C2);
    setJoueurActif(jeu, &jeu->J1);
}

void detruireJeu(Jeu * jeu)
{
    viderPlateau(&jeu->plateau);
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
        setCouleurCase(getCase(&(jeu->plateau), x, y+i), CBLEU);
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

    if(piece != NULL && couleur == getCouleurPiece(piece))
    {

        setCouleurCase(getCase(&(jeu->plateau), posX, posY), CBLEU);

        switch(piece->type)
        {

            case PION:

                if (couleur == getCouleurJoueur(&jeu->J1))  a = -1;
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

void deplacerPiece(Plateau * plateau, Piece * piece, int posX, int posY, int* victoireAtt, int* victoireDef)
{
    int i = 0, j = 0, cpt = 0;

    while(caseValide(i, j) && getPieceCase(getCase(plateau, i, j)) != piece)
    {
        cpt++;

        j = cpt%8;
        i = cpt/8;
    }
    setPieceCase(getCase(plateau, i, j), NULL);

    if(getPieceCase(getCase(plateau, posX, posY)) != NULL)
        piece = combatPieces(piece, getPieceCase(getCase(plateau, posX, posY)), victoireAtt, victoireDef);

    setPieceCase(getCase(plateau, posX, posY), piece);
}

int verifieVictoire(Piece* piece)
{
    if((piece->type == ROI) && (piece->pointsVie <= 0)) return 1 ;
    else return 0 ;
}

Piece* combatPieces(Piece * pieceAtt, Piece * pieceDef, int * victoireAtt, int * victoireDef)
{
    int BONUS = 1;
    int vie;

    while(getPointsVie(pieceAtt) > 0 && getPointsVie(pieceDef) > 0)
    {
        vie = getPointsVie(pieceDef) - getPointsAttaque(pieceAtt)*BONUS;
        if(vie <= 0)
            setPointsVie(pieceDef, 0);
        else
            setPointsVie(pieceDef, vie);

        if(getPointsVie(pieceDef) > 0)
        {
            vie = getPointsVie(pieceAtt) - getPointsAttaque(pieceDef);
            if(vie <= 0)
                setPointsVie(pieceAtt, 0);
            else
                setPointsVie(pieceAtt, vie);
        }
    }

    if(getPointsVie(pieceAtt) > 0)
    {
        victoireAtt = *verifieVictoire(pieceDef) ;
        detruirePiece(pieceDef) ;
        return pieceAtt ;
    }
    else
    {
        victoireDef = *verifieVictoire(pieceAtt) ;
        detruirePiece(pieceAtt) ;
        return pieceDef ;
    }
}
