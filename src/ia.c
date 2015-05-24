#include "ia.h"

void ia (Jeu * jeu)
{
    IAjeu iaJeu;

    int nbDepPos;
    IApiece * iaPiece = NULL;
    Piece * piece = NULL;

    initIAjeu(&iaJeu, jeu);

    srand(time(NULL));

    piece = joueurVulnerableIAjeu(&iaJeu, jeu, &jeu->J2);

    if (piece != NULL)
    {
        iaPiece = rechercheIApiece(&iaJeu, jeu, piece);
        deplacementsPossiblesIApiece(iaPiece, jeu, piece->posX, piece->posY);
        nbDepPos = iaPiece->nbDeplacementsPossibles;

        if (nbDepPos == 0)
        {
            iaPiece = IApieceRandom(&iaJeu, jeu, &jeu->J2);
            deplacementRandom(iaPiece, jeu);
        }
        else
        {
           deplacementRandom(iaPiece, jeu);
        }
    }

    if (piece == NULL)
    {
        iaPiece = IApieceRandom(&iaJeu, jeu, &jeu->J2);
        deplacementRandom(iaPiece, jeu);
    }

}


/*  Fonctions d'initialisation  */

void initIApiece(IApiece * iaPiece, Jeu * jeu, Piece * piece)
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

    if (piece != NULL)
        casesPiecesControleesIApiece(iaPiece, jeu, piece->posX, piece->posY);
}

void initIAjeu(IAjeu * iaJeu, Jeu * jeu)
{
    int i;
    Piece * piece = NULL;

    int n = getNbPiecesJoueur(&jeu->J1) + getNbPiecesJoueur(&jeu->J2);
    iaJeu->nbPiecesJeu = n;

    for (i=0; i<32; i++)
    {
        if (i<16)   piece = jeu->J1.ensPieces[i];
        else        piece = jeu->J2.ensPieces[i-16];

        initIApiece(&iaJeu->iaPieces[i], jeu, piece);
    }
}


/*  Accesseurs  */

void setNbCasesControleesIApiece(IApiece * iaPiece, int n)
{
    if (iaPiece->piece != NULL) iaPiece->nbCasesControlees = n;
}

void setNbPiecesControleesIApiece(IApiece * iaPiece, int n)
{
    if (iaPiece->piece != NULL) iaPiece->nbPiecesControlees = n;
}

void setNbDeplacementsPossiblesIApiece(IApiece * iaPiece, int n)
{
    if (iaPiece->piece != NULL) iaPiece->nbDeplacementsPossibles = n;
}


void setCaseControleeIApiece(IApiece * iaPiece, Case * cell)
{
    int n;
    if (iaPiece->piece != NULL)
    {
        n = iaPiece->nbCasesControlees;
        iaPiece->casesControlees[n] = cell;
        setNbCasesControleesIApiece(iaPiece, n+1);
    }
}

void setPieceControleeIApiece(IApiece * iaPiece, Piece * piece)
{
    int n;
    if (iaPiece->piece != NULL)
    {
        n = iaPiece->nbPiecesControlees;
        iaPiece->piecesControlees[n] = piece;
        setNbPiecesControleesIApiece(iaPiece, n+1);
    }
}

void setDeplacementPossibleIApiece(IApiece * iaPiece, Case * cell)
{
    int n;
    if (iaPiece->piece != NULL)
    {
        n = iaPiece->nbDeplacementsPossibles;
        iaPiece->deplacementsPossibles[n] = cell;
        setNbDeplacementsPossiblesIApiece(iaPiece, n+1);
    }
}


/*  Foctions de gestion de l'IA    */

void coloreCasesControleesIApiece(IApiece * iaPiece)
{
    int i, n;
    Case * cell = NULL;

    if (iaPiece->piece != NULL)
    {
        n = iaPiece->nbCasesControlees;

        for (i=0; i<n; i++)
        {
            cell = iaPiece->casesControlees[i];
            setCouleurCase(cell, CBLEU);
        }
    }
}

void colorePiecesControlees(IApiece * iaPiece, Jeu * jeu)
{
    int i, n;
    Case * cell = NULL;
    Piece * piece = NULL;

    if (iaPiece->piece != NULL)
    {
        n = iaPiece->nbPiecesControlees;

        for (i=0; i<n; i++)
        {
            piece = iaPiece->piecesControlees[i];
            cell = getCase(&jeu->plateau, piece->posX, piece->posY);
            setCouleurCase(cell, CBLEU);
        }
    }
}

void coloreDeplacementsPossiblesIApiece(IApiece * iaPiece)
{
    int i, n;

    if (iaPiece->piece != NULL)
    {
        n = iaPiece->nbDeplacementsPossibles;
        Case * cell = NULL;

        for (i=0; i<n; i++)
        {
            cell = iaPiece->deplacementsPossibles[i];
            setCouleurCase(cell, CBLEU);
        }
    }
}

void casesControleesLigneColonneIApiece(IApiece * iaPiece, Jeu *jeu, int x, int y)
{
    int i = 1;

    if (iaPiece->piece != NULL)
    {
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
}

void casesControleesDiagonalesIApiece(IApiece * iaPiece, Jeu * jeu, int x, int y)
{
    int i = 1;

    if (iaPiece->piece != NULL)
    {
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
}

void casesPiecesControleesIApiece(IApiece * iaPiece, Jeu * jeu, int x, int y)
{
    int a, i, j;
    Piece * piece = NULL;

    if (iaPiece->piece != NULL)
    {
        piece = iaPiece->piece;

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

        piecesControleesIApiece(iaPiece);
    }
}

void piecesControleesIApiece(IApiece * iaPiece)
{
    int i;
    int n = iaPiece->nbCasesControlees;
    Case * cell = NULL;

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
    Case * cell = NULL;
    Piece * piece = NULL;
    Joueur * joueur = NULL;
    Couleur couleur;

    if (iaPiece->piece != NULL)
    {
        joueur = &jeu->J2;
        couleur = getCouleurJoueur(joueur);
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
}

bool pieceVulnerableIAjeu(IAjeu * iaJeu, Jeu * jeu, Piece * piece, int x, int y)
{
    Couleur couleur = piece->couleur;
    int nbPiecesControlees, i, j;
    IApiece * IApieceAdverse = NULL;

    if (couleur == getCouleurJoueur(&jeu->J1))
    {
        for (i=16; i<32; i++)
        {
            IApieceAdverse = &iaJeu->iaPieces[i];
            if (IApieceAdverse->piece != NULL)
            {
                nbPiecesControlees = IApieceAdverse->nbPiecesControlees;
                for (j=0; j<nbPiecesControlees; j++)
                {
                    if (IApieceAdverse->piecesControlees[j]->posX == x && IApieceAdverse->piecesControlees[j]->posY == y)
                        return true;
                }
            }
        }
    }
    else
    {
        for (i=0; i<16; i++)
        {
            IApieceAdverse = &iaJeu->iaPieces[i];
            if (IApieceAdverse->piece != NULL)
            {
                nbPiecesControlees = IApieceAdverse->nbPiecesControlees;
                for (j=0; j<nbPiecesControlees; j++)
                    if (IApieceAdverse->piecesControlees[j]->posX == x && IApieceAdverse->piecesControlees[j]->posY == y)
                        return true;
            }
        }
    }
    return false;
}

bool pieceProtegeeIAjeu(IAjeu * iaJeu, Jeu * jeu, Piece * piece, int x, int y)
{
    Couleur couleur = piece->couleur;
    int nbPiecesControlees, i, j;
    IApiece * IApieceAmie = NULL;

    if (couleur == getCouleurJoueur(&jeu->J1))
    {
        for (i=0; i<16; i++)
        {
            IApieceAmie = &iaJeu->iaPieces[i];
            if (IApieceAmie->piece != NULL)
            {
                nbPiecesControlees = IApieceAmie->nbPiecesControlees;
                for (j=0; j<nbPiecesControlees; j++)
                    if (IApieceAmie->piecesControlees[j]->posX == x && IApieceAmie->piecesControlees[j]->posY == y)
                        return true;
            }
        }
    }
    else
    {
        for (i=16; i<32; i++)
        {
            IApieceAmie = &iaJeu->iaPieces[i];
            if (IApieceAmie->piece != NULL)
            {
                nbPiecesControlees = IApieceAmie->nbPiecesControlees;
                for (j=0; j<nbPiecesControlees; j++)
                    if (IApieceAmie->piecesControlees[j]->posX == x && IApieceAmie->piecesControlees[j]->posY == y)
                        return true;
            }
        }
    }
    return false;
}

Piece * joueurVulnerableIAjeu(IAjeu * iaJeu, Jeu * jeu, Joueur * joueur)
{
    Piece * piece = NULL;
    int i;

    /*  on vérifie si le roi est vulnérable    */
    piece = joueur->ensPieces[12];
    if (piece != NULL && pieceVulnerableIAjeu(iaJeu, jeu, piece, piece->posX, piece->posY))
        return piece;

    /*  puis on vérifie pour la dame    */
    piece = joueur->ensPieces[11];
    if (piece != NULL && pieceVulnerableIAjeu(iaJeu, jeu, piece, piece->posX, piece->posY))
        return piece;

    /*  les tours   */
    piece = joueur->ensPieces[8];
    if (piece != NULL && pieceVulnerableIAjeu(iaJeu, jeu, piece, piece->posX, piece->posY))
        return piece;
    piece = joueur->ensPieces[15];
    if (piece != NULL && pieceVulnerableIAjeu(iaJeu, jeu, piece, piece->posX, piece->posY))
        return piece;

    /*  les cavaliers   */
    piece = joueur->ensPieces[9];
    if (piece != NULL && pieceVulnerableIAjeu(iaJeu, jeu, piece, piece->posX, piece->posY))
        return piece;
    piece = joueur->ensPieces[14];
    if (piece != NULL && pieceVulnerableIAjeu(iaJeu, jeu, piece, piece->posX, piece->posY))
        return piece;

    /*  les fous   */
    piece = joueur->ensPieces[10];
    if (piece != NULL && pieceVulnerableIAjeu(iaJeu, jeu, piece, piece->posX, piece->posY))
        return piece;
    piece = joueur->ensPieces[13];
    if (piece != NULL && pieceVulnerableIAjeu(iaJeu, jeu, piece, piece->posX, piece->posY))
        return piece;

    /*  ... et les pions    */
    for (i=0; i<8; i++)
    {
        piece = joueur->ensPieces[i];
        if (piece != NULL && pieceVulnerableIAjeu(iaJeu, jeu, piece, piece->posX, piece->posY))
            return piece;
    }

    return NULL;
}

IApiece * rechercheIApiece(IAjeu * iaJeu, Jeu * jeu, Piece * piece)
{
    int indice;

    if (piece != NULL)
    {
        indice = estDansEnsPieces(piece, &jeu->J1);
        if (indice != -1)
            return &iaJeu->iaPieces[indice];

        indice = estDansEnsPieces(piece, &jeu->J2);
        if (indice != -1)
            return &iaJeu->iaPieces[16+indice];
    }
    return NULL;
}

IApiece * IApieceRandom(IAjeu * iaJeu, Jeu * jeu, Joueur * joueur)
{
    int numPiece = 0, nbDeplacementsPossibles = 0;
    IApiece * iaPiece = NULL;

    do
    {
        do
        {
            if (&jeu->J1 == joueur) numPiece = rand()%16;
            else numPiece = rand()%16+16;

            iaPiece = &iaJeu->iaPieces[numPiece];

        } while (iaPiece->piece == NULL);

        deplacementsPossiblesIApiece(iaPiece, jeu, iaPiece->piece->posX, iaPiece->piece->posY);
        nbDeplacementsPossibles = iaPiece->nbDeplacementsPossibles;

    }while (nbDeplacementsPossibles == 0);

    return iaPiece;
}

void deplacementRandom(IApiece * iaPiece, Jeu * jeu)
{
    int numDeplacement = 0, x = 0, y = 0;
    Case * cell = NULL;

    if (iaPiece->piece != NULL)
    {
        numDeplacement = rand()%(iaPiece->nbDeplacementsPossibles);

        cell = iaPiece->deplacementsPossibles[numDeplacement];
        getCoordCase(&jeu->plateau, cell, &x, &y);

        deplacerPiece(jeu, iaPiece->piece, x, y);
    }
}





