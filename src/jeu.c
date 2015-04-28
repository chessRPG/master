#include "jeu.h"

/*  Création/Destruction    */

void initJeu(Jeu * jeu, char * piecesJ1, char * piecesJ2)
{
    Couleur C1, C2;

    initJoueur(&jeu->J1);
    initJoueur(&jeu->J2);
    setDonneesJoueurs(&jeu->J1, &jeu->J2, piecesJ1, piecesJ2);

    C1 = getCouleurJoueur(&jeu->J1);
    C2 = getCouleurJoueur(&jeu->J2);

    setJoueurActif(jeu, &jeu->J1);
    initPlateau(&jeu->plateau, C1, C2);
    reinitCouleursEchiquier(&jeu->plateau) ;
}

void detruireJeu(Jeu * jeu)
{
    jeu->joueurActif = NULL;
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

void rechercherPiece(Plateau * plateau, Piece * piece, int * x, int * y)
{
    int cpt = 0;
    while(caseValide(*x, *y) && getPieceCase(getCase(plateau, *x, *y)) != piece)
    {
        cpt++;

        *y = cpt%8;
        *x = cpt/8;
    }
}

/* Accesseurs */

Joueur * getJoueurActif(Jeu * jeu)
{
    return jeu->joueurActif;
}

Joueur * getJoueurInactif(Jeu * jeu)
{
    if(&(jeu->J1) == jeu->joueurActif) return &(jeu->J2) ;
    else return &(jeu->J1) ;
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
                if (((getJoueurActif(jeu) == &jeu->J1 && posX == 6) || (getJoueurActif(jeu) == &jeu->J2 && posX == 1)) && (getCouleurCase(getCase(&(jeu->plateau), posX+a, posY)) == CBLEU && getPieceCase(getCase(&(jeu->plateau), posX+2*a, posY)) == NULL))
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

void deplacerPiece(Plateau * plateau, Piece * piece, int posX, int posY, Couleur * couleurGagne)
{
    int i = 0, j = 0;

    rechercherPiece(plateau, piece, &i, &j);

    setPieceCase(getCase(plateau, i, j), NULL);

    if(getPieceCase(getCase(plateau, posX, posY)) != NULL)
        piece = combatPieces(piece, getPieceCase(getCase(plateau, posX, posY)), couleurGagne);

    setPieceCase(getCase(plateau, posX, posY), piece);
}

Piece* combatPieces(Piece * pieceAtt, Piece * pieceDef, Couleur * couleurGagne)
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
        if(pieceDef->type == ROI) *couleurGagne = getCouleurPiece(pieceAtt) ;
        detruirePiece(pieceDef) ;
        return pieceAtt ;
    }
    else
    {
        if(pieceAtt->type == ROI) *couleurGagne = getCouleurPiece(pieceDef) ;
        detruirePiece(pieceAtt) ;
        return pieceDef ;
    }
}
