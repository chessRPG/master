#include "ia.h"

void ia (Jeu * jeu)
{
    IAjeu iaJeu;

    int numPiece, numDep, nbDepPos;
    Piece * piece;
    Case * cell;
    int x = 0, y = 0;

    initIAjeu(&iaJeu, jeu);

    srand(time(NULL));
    do
    {
        numPiece = rand()%16+16;
        piece = iaJeu.iaPiece[numPiece].piece;
        deplacementsPossiblesIApiece(&iaJeu.iaPiece[numPiece], jeu, piece->posX, piece->posY);
        nbDepPos = iaJeu.iaPiece[numPiece].nbDeplacementsPossibles;

    } while (piece == NULL || nbDepPos == 0);

    numDep = rand()%(iaJeu.iaPiece[numPiece].nbDeplacementsPossibles);

    cell = iaJeu.iaPiece[numPiece].deplacementsPossibles[numDep];
    getCoordCase(&jeu->plateau, cell, &x, &y);

    deplacerPiece(jeu, piece, x, y);
}

/*  Fonctions d'initialisation  */

void initIApiece(IApiece * iaPiece, Piece * piece)
{
    int i;

    iaPiece->piece = piece;

    iaPiece->nbCasesControlees = 0;
    iaPiece->nbPiecesControlees = 0;
    iaPiece->nbDeplacementsPossibles = 0;

    for (i=0; i<27; i++)
        iaPiece->casesControlees[i] = NULL;

    for (i=0; i<8; i++)
        iaPiece->piecesControlees[i] = NULL;

    for (i=0; i<27; i++)
        iaPiece->deplacementsPossibles[i] = NULL;
}

void initIAjeu(IAjeu * iaJeu, Jeu * jeu)
{
    int i;
    Piece * piece;

    int n = getNbPiecesJoueur(&jeu->J1) + getNbPiecesJoueur(&jeu->J2);
    iaJeu->nbPiecesJeu = n;

    for (i=0; i<32; i++)
    {
        if (i<16)   piece = jeu->J1.ensPieces[i];
        else        piece = jeu->J2.ensPieces[i-16];

        initIApiece(&iaJeu->iaPiece[i], piece);
    }
}


/*  Accesseurs  */

void setNbCasesControleesIApiece(IApiece * ia, int n)
{
    ia->nbCasesControlees = n;
}

void setNbPiecesControleesIApiece(IApiece * iaPiece, int n)
{
    iaPiece->nbPiecesControlees = n;
}

void setNbDeplacementsPossiblesIApiece(IApiece * iaPiece, int n)
{
    iaPiece->nbDeplacementsPossibles = n;
}


void setCaseControleeIApiece(IApiece * iaPiece, Case * cell)
{
    int n = iaPiece->nbCasesControlees;
    iaPiece->casesControlees[n] = cell;
    setNbCasesControleesIApiece(iaPiece, n+1);
}

void setPieceControleeIApiece(IApiece * iaPiece, Piece * piece)
{
    int n = iaPiece->nbPiecesControlees;
    iaPiece->piecesControlees[n] = piece;
    setNbPiecesControleesIApiece(iaPiece, n+1);
}

void setDeplacementPossibleIApiece(IApiece * iaPiece, Case * cell)
{
    int n = iaPiece->nbDeplacementsPossibles;
    iaPiece->deplacementsPossibles[n] = cell;
    setNbDeplacementsPossiblesIApiece(iaPiece, n+1);
}


/*  Foctions de gestion de l'IA    */

void coloreCasesControleesIApiece(IApiece * iaPiece)
{
    int i;
    int n = iaPiece->nbCasesControlees;
    Case * cell;

    for (i=0; i<n; i++)
    {
        cell = iaPiece->casesControlees[i];
        setCouleurCase(cell, CBLEU);
    }
}

void colorePiecesControlees(IApiece * iaPiece, Jeu * jeu)
{
    int i;
    int n = iaPiece->nbPiecesControlees;
    Case * cell;
    Piece * piece;

    for (i=0; i<n; i++)
    {
        piece = iaPiece->piecesControlees[i];
        cell = getCase(&jeu->plateau, piece->posX, piece->posY);
        setCouleurCase(cell, CBLEU);
    }
}

void coloreDeplacementsPossiblesIApiece(IApiece * iaPiece)
{
    int i;
    int n = iaPiece->nbDeplacementsPossibles;
    Case * cell;

    for (i=0; i<n; i++)
    {
        cell = iaPiece->deplacementsPossibles[i];
        setCouleurCase(cell, CBLEU);
    }
}

void casesControleesLigneColonneIApiece(IApiece * iaPiece, Jeu *jeu, int x, int y)
{
    int i = 1;
    while (caseValide(x-i, y) && getPieceCase(getCase(&(jeu->plateau), x-i, y)) == NULL)
    {
        setCaseControleeIApiece(iaPiece, getCase(&(jeu->plateau), x-i, y));
        i++;
    }
    if (caseValide(x-i, y))
        setCaseControleeIApiece(iaPiece, getCase(&(jeu->plateau), x-i, y));

    i = 1;
    while (caseValide(x+i, y) && getPieceCase(getCase(&(jeu->plateau), x+i, y)) == NULL)
    {
        setCaseControleeIApiece(iaPiece, getCase(&(jeu->plateau), x+i, y));
        i++;
    }
    if (caseValide(x+i, y))
        setCaseControleeIApiece(iaPiece, getCase(&(jeu->plateau), x+i, y));

    i = 1;
    while (caseValide(x, y-i) && getPieceCase(getCase(&(jeu->plateau), x, y-i)) == NULL)
    {
        setCaseControleeIApiece(iaPiece, getCase(&(jeu->plateau), x, y-i));
        i++;
    }
    if (caseValide(x, y-i))
        setCaseControleeIApiece(iaPiece, getCase(&(jeu->plateau), x, y-i));

    i = 1;
    while (caseValide(x, y+i) && getPieceCase(getCase(&(jeu->plateau), x, y+i)) == NULL)
    {
        setCaseControleeIApiece(iaPiece, getCase(&(jeu->plateau), x, y+i));
        i++;
    }
    if (caseValide(x, y+i))
        setCaseControleeIApiece(iaPiece, getCase(&(jeu->plateau), x, y+i));
}

void casesControleesDiagonalesIApiece(IApiece * iaPiece, Jeu * jeu, int x, int y)
{
    int i = 1;
    while (caseValide(x-i, y-i) && getPieceCase(getCase(&jeu->plateau, x-i, y-i)) == NULL)
    {
        setCaseControleeIApiece(iaPiece, getCase(&jeu->plateau, x-i, y-i));
        i++;
    }
    if (caseValide(x-i, y-i))
        setCaseControleeIApiece(iaPiece, getCase(&jeu->plateau, x-i, y-i));

    i = 1;
    while (caseValide(x-i, y+i) && getPieceCase(getCase(&jeu->plateau, x-i, y+i)) == NULL)
    {
        setCaseControleeIApiece(iaPiece, getCase(&jeu->plateau, x-i, y+i));
        i++;
    }
    if (caseValide(x-i, y+i))
        setCaseControleeIApiece(iaPiece, getCase(&jeu->plateau, x-i, y+i));

    i = 1;
    while (caseValide(x+i, y-i) && getPieceCase(getCase(&jeu->plateau, x+i, y-i)) == NULL)
    {
        setCaseControleeIApiece(iaPiece, getCase(&jeu->plateau, x+i, y-i));
        i++;
    }
    if (caseValide(x+i, y-i))
        setCaseControleeIApiece(iaPiece, getCase(&jeu->plateau, x+i, y-i));

    i = 1;
    while (caseValide(x+i, y+i) && getPieceCase(getCase(&jeu->plateau, x+i, y+i)) == NULL)
    {
        setCaseControleeIApiece(iaPiece, getCase(&jeu->plateau, x+i, y+i));
        i++;
    }
    if (caseValide(x+i, y+i))
        setCaseControleeIApiece(iaPiece, getCase(&jeu->plateau, x+i, y+i));
}

void casesPiecesControleesIApiece(IApiece * iaPiece, Jeu * jeu, int x, int y)
{
    int a, i, j;
    Piece * piece = iaPiece->piece;

    switch(piece->type)
    {
        case PION:
            if (getCouleurPiece(piece) == getCouleurJoueur(&jeu->J1))  a = -1;
            else    a = 1;

            if (caseValide(x+a, y-1))
                setCaseControleeIApiece(iaPiece, getCase(&jeu->plateau, x+a, y-1));
            if (caseValide(x+a, y+1))
                setCaseControleeIApiece(iaPiece, getCase(&(jeu->plateau), x+a, y+1));
            break;

        case TOUR:
            casesControleesLigneColonneIApiece(iaPiece, jeu, x, y);
            break;

        case CAVALIER:
            if (caseValide(x-2, y-1))
                setCaseControleeIApiece(iaPiece, getCase(&(jeu->plateau), x-2, y-1));
            if (caseValide(x-2, y+1))
                setCaseControleeIApiece(iaPiece, getCase(&(jeu->plateau), x-2, y+1));
            if (caseValide(x-1, y-2))
                setCaseControleeIApiece(iaPiece, getCase(&(jeu->plateau), x-1, y-2));
            if (caseValide(x-1, y+2))
                setCaseControleeIApiece(iaPiece, getCase(&(jeu->plateau), x-1, y+2));
            if (caseValide(x+1, y-2))
                setCaseControleeIApiece(iaPiece, getCase(&(jeu->plateau), x+1, y-2));
            if (caseValide(x+1, y+2))
                setCaseControleeIApiece(iaPiece, getCase(&(jeu->plateau), x+1, y+2));
            if (caseValide(x+2, y-1))
                setCaseControleeIApiece(iaPiece, getCase(&(jeu->plateau), x+2, y-1));
            if (caseValide(x+2, y+1))
                setCaseControleeIApiece(iaPiece, getCase(&(jeu->plateau), x+2, y+1));
            break;

        case FOU:
            casesControleesDiagonalesIApiece(iaPiece, jeu, x, y);
            break;

        case DAME:
            casesControleesLigneColonneIApiece(iaPiece, jeu, x, y);
            casesControleesDiagonalesIApiece(iaPiece, jeu, x, y);
            break;

        case ROI:
            for (i = x-1 ; i<x+2 ; i++)
            {
                for (j = y-1; j<y+2; j++)
                {
                    if (caseValide(i, j))
                        setCaseControleeIApiece(iaPiece, getCase(&(jeu->plateau), i, j));
                }
            }
            break;

        default:
            break;
    }

    piecesControleesIApiece(iaPiece, x, y);
}

void piecesControleesIApiece(IApiece * iaPiece, int x, int y)
{
    int i;
    int n = iaPiece->nbCasesControlees;
    Case * cell;

    for (i=0; i<n; i++)
    {
        cell = iaPiece->casesControlees[i];
        if (cell->piece != NULL)
            setPieceControleeIApiece(iaPiece, cell->piece);
    }
}

void deplacementsPossiblesIApiece(IApiece * iaPiece, Jeu * jeu, int x, int y)
{
    int i, nbCases;
    Case * cell;
    Piece * piece;
    Joueur * joueur = &jeu->J2;
    Couleur couleur = getCouleurJoueur(joueur);

    casesPiecesControleesIApiece(iaPiece, jeu, x, y);
    nbCases = iaPiece->nbCasesControlees;

    if (iaPiece->piece->type == PION)
    {
        if (caseValide(x+1, y) && getPieceCase(getCase(&(jeu->plateau), x+1, y)) == NULL)
        {
            setDeplacementPossibleIApiece(iaPiece, getCase(&(jeu->plateau), x+1, y));
            if (x == 1 && caseValide(x+2, y) && getPieceCase(getCase(&(jeu->plateau), x+2, y)) == NULL)
                setDeplacementPossibleIApiece(iaPiece, getCase(&(jeu->plateau), x+2, y));
        }
        if (caseValide(x+1, y-1) && getPieceCase(getCase(&(jeu->plateau), x+1, y-1)) != NULL && getCouleurPiece(getPieceCase(getCase(&(jeu->plateau), x+1, y-1))) != couleur)
            setDeplacementPossibleIApiece(iaPiece, getCase(&(jeu->plateau), x+1, y-1));
        if (caseValide(x+1, y+1) && getPieceCase(getCase(&(jeu->plateau), x+1, y+1)) != NULL && getCouleurPiece(getPieceCase(getCase(&(jeu->plateau), x+1, y+1))) != couleur)
            setDeplacementPossibleIApiece(iaPiece, getCase(&(jeu->plateau), x+1, y+1));
    }
    else
    {
        for (i=0; i<nbCases; i++)
        {
            cell = iaPiece->casesControlees[i];
            piece = getPieceCase(cell);
            if (piece == NULL || getCouleurPiece(piece) != couleur)
                setDeplacementPossibleIApiece(iaPiece, cell);
        }
    }
}
