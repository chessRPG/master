#include "ia.h"

void ia (Jeu * jeu)
{
    IAjeu iaJeu;

    int nbDepPos, x = 0, y = 0;
    IApiece * iaPieceAmie = NULL;
    IApiece * iaPieceAdverse = NULL;
    Piece * pieceVulnerable = NULL;
    Case * cell = NULL;

    initIAjeu(&iaJeu, jeu);
    srand(time(NULL));

    pieceVulnerable = joueurVulnerableIAjeu(&iaJeu, jeu, &jeu->J1);

    /*  Si le J1 est vulnérable */

    if (pieceVulnerable != NULL)
    {
        iaPieceAmie = rechercheIApieceAttaquante(&iaJeu, pieceVulnerable, jeu, &jeu->J2);

        deplacerPiece(jeu, iaPieceAmie->piece, pieceVulnerable->posX, pieceVulnerable->posY);
        return;
    }


    /*  Si le J1 n'est pas vulnérable   */

    else
    {

        pieceVulnerable = joueurVulnerableIAjeu(&iaJeu, jeu, &jeu->J2);

        /*  Si l'IA est vulnérable  */

        if (pieceVulnerable != NULL)
        {
            iaPieceAdverse = rechercheIApieceAttaquante(&iaJeu, pieceVulnerable, jeu, &jeu->J1);
            if (pieceVulnerableIAjeu(&iaJeu, jeu, iaPieceAdverse->piece, iaPieceAdverse->piece->posX, iaPieceAdverse->piece->posY))
            {
                iaPieceAmie = rechercheIApieceAttaquante(&iaJeu, iaPieceAdverse->piece, jeu, &jeu->J2);
                if (!pieceProtegeeIAjeu(&iaJeu, jeu, iaPieceAdverse->piece, iaPieceAdverse->piece->posX, iaPieceAdverse->piece->posY))
                {
                    deplacerPiece(jeu, iaPieceAmie->piece, iaPieceAdverse->piece->posX, iaPieceAdverse->piece->posY);
                    return;
                }
            }

            iaPieceAmie = rechercheIApiece(&iaJeu, pieceVulnerable);
            deplacementsPossiblesIApiece(iaPieceAmie, jeu, pieceVulnerable->posX, pieceVulnerable->posY);
            nbDepPos = iaPieceAmie->nbDeplacementsPossibles;

            if (nbDepPos == 0)
                iaPieceAmie = IApieceRandom(&iaJeu, jeu, &jeu->J2);

            cell = deplacementPrudent(&iaJeu, iaPieceAmie, jeu);
            if (cell != NULL)
            {
                getCoordCase(&jeu->plateau, cell, &x, &y);
                deplacerPiece(jeu, pieceVulnerable, x, y);
                return;
            }
            else
            {
                cell = deplacementRandom(iaPieceAmie, jeu);
                if (cell != NULL)
                {
                    getCoordCase(&jeu->plateau, cell, &x, &y);
                    deplacerPiece(jeu, iaPieceAmie->piece, x, y);
                    return;
                }
            }
        }

        /*  Si l'IA n'est pas vulnérable    */

        else
        {
            iaPieceAmie = IApieceRandom(&iaJeu, jeu, &jeu->J2);
            cell = deplacementPrudent(&iaJeu, iaPieceAmie, jeu);
            if (cell != NULL)
            {
                getCoordCase(&jeu->plateau, cell, &x, &y);
                deplacerPiece(jeu, iaPieceAmie->piece, x, y);
                return;
            }
            else
            {
                cell = deplacementRandom(iaPieceAmie, jeu);
                getCoordCase(&jeu->plateau, cell, &x, &y);
                deplacerPiece(jeu, iaPieceAmie->piece, x, y);
                return;
            }
        }
    }

}




/*  Fonctions d'initialisation  */

void initIAjeu(IAjeu * iaJeu, Jeu * jeu)
{
    int i;
    Piece * pieceJ1 = NULL;
    Piece * pieceJ2 = NULL;

    for (i=0; i<16; i++)
    {
        initIApiece(&iaJeu->iaPiecesJ1[i], jeu, NULL);
        initIApiece(&iaJeu->iaPiecesJ2[i], jeu, NULL);

        pieceJ1 = jeu->J1.ensPieces[i];
        if (estDansEnsPieces(pieceJ1, &jeu->J1) != -1)  initIApiece(&iaJeu->iaPiecesJ1[i], jeu, pieceJ1);

        pieceJ2 = jeu->J2.ensPieces[i];
        if (estDansEnsPieces(pieceJ2, &jeu->J2) != -1)  initIApiece(&iaJeu->iaPiecesJ2[i], jeu, pieceJ2);
    }
}

void initIApiece(IApiece * iaPiece, Jeu * jeu, Piece * piece)
{
    iaPiece->piece = piece;

    resetIApiece(iaPiece);
}

void resetIApiece(IApiece * iaPiece)
{
    int i;

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




/*  Mutateurs  */

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
    Piece * piece = iaPiece->piece;
    Case * caseInit = getCase(&jeu->plateau, piece->posX, piece->posY);
    Piece * pieceTemp = getPieceCase(getCase(&jeu->plateau, x, y));
    Case * caseTemp = getCase(&jeu->plateau, pieceTemp->posX, pieceTemp->posY);

    if (piece != NULL)
    {
        resetIApiece(iaPiece);
        setPieceCase(caseTemp, piece);

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

        setPieceCase(caseInit, piece);
        setPieceCase(caseTemp, pieceTemp);
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
    Piece * pieceAdverse = NULL;
    Piece * piece = iaPiece->piece;
    Case * caseInit = getCase(&jeu->plateau, piece->posX, piece->posY);
    Case * caseTemp = getCase(&jeu->plateau, x, y);
    Piece * pieceTemp = getPieceCase(caseTemp);
    Joueur * joueur = NULL;
    Couleur couleur;

    if (piece != NULL)
    {
        resetIApiece(iaPiece);
        setPieceCase(caseTemp, piece);
        casesPiecesControleesIApiece(iaPiece, jeu, x, y);

        joueur = &jeu->J2;
        couleur = getCouleurJoueur(joueur);
        nbCases = iaPiece->nbCasesControlees;

        if (piece->type == PION)
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
                pieceAdverse = getPieceCase(cell);
                if (pieceAdverse == NULL || getCouleurPiece(pieceAdverse) != couleur)
                    setDeplacementPossibleIApiece(iaPiece, cell);
            }
        }
        setPieceCase(caseInit, piece);
        setPieceCase(caseTemp, pieceTemp);
    }
}

bool pieceVulnerableIAjeu(IAjeu * iaJeu, Jeu * jeu, Piece * piece, int x, int y)
{
    Couleur couleur = piece->couleur;
    int nbPiecesControlees, i, j;
    IApiece * IApieceAdverse = NULL;
    Case * caseInit = getCase(&jeu->plateau, piece->posX, piece->posY);
    Case * caseTemp = getCase(&jeu->plateau, x, y);
    Piece * pieceTemp = getPieceCase(caseTemp);

    setPieceCase(caseTemp, piece);

    for (i=0; i<16; i++)
    {
        if (couleur == getCouleurJoueur(&jeu->J1))  IApieceAdverse = &iaJeu->iaPiecesJ2[i];
        else    IApieceAdverse = &iaJeu->iaPiecesJ1[i];

        if (IApieceAdverse->piece != NULL)
        {
            casesPiecesControleesIApiece(IApieceAdverse, jeu, IApieceAdverse->piece->posX, IApieceAdverse->piece->posY);
            nbPiecesControlees = IApieceAdverse->nbPiecesControlees;
            for (j=0; j<nbPiecesControlees; j++)
            {
                if (IApieceAdverse->piecesControlees[j]->posX == x && IApieceAdverse->piecesControlees[j]->posY == y)
                    return true;
            }
        }
    }

    setPieceCase(caseInit, piece);
    setPieceCase(caseTemp, pieceTemp);

    return false;
}

bool pieceProtegeeIAjeu(IAjeu * iaJeu, Jeu * jeu, Piece * piece, int x, int y)
{
    Couleur couleur = piece->couleur;
    int nbPiecesControlees, i, j;
    IApiece * IApieceAmie = NULL;
    Case * caseInit = getCase(&jeu->plateau, piece->posX, piece->posY);
    Case * caseTemp = getCase(&jeu->plateau, x, y);
    Piece * pieceTemp = getPieceCase(caseTemp);

    setPieceCase(caseTemp, piece);

    for (i=0; i<16; i++)
    {
        if (couleur == getCouleurJoueur(&jeu->J1))  IApieceAmie = &iaJeu->iaPiecesJ1[i];
        else    IApieceAmie = &iaJeu->iaPiecesJ2[i];

        if (IApieceAmie->piece != NULL)
        {
            casesPiecesControleesIApiece(IApieceAmie, jeu, IApieceAmie->piece->posX, IApieceAmie->piece->posY);
            nbPiecesControlees = IApieceAmie->nbPiecesControlees;
            for (j=0; j<nbPiecesControlees; j++)
                if (IApieceAmie->piecesControlees[j]->posX == x && IApieceAmie->piecesControlees[j]->posY == y)
                    return true;
        }
    }

    setPieceCase(caseInit, piece);
    setPieceCase(caseTemp, pieceTemp);

    return false;
}

Piece * joueurVulnerableIAjeu(IAjeu * iaJeu, Jeu * jeu, Joueur * joueur)
{
    Piece * piece;
    int i;

    /*  on vérifie si le roi est vulnérable    */
    if (joueur == &jeu->J1) piece = iaJeu->iaPiecesJ1[12].piece;
    else    piece = iaJeu->iaPiecesJ2[12].piece;
    if (piece != NULL && pieceVulnerableIAjeu(iaJeu, jeu, piece, piece->posX, piece->posY))
        return piece;

    /*  puis on vérifie pour la dame    */
    if (joueur == &jeu->J1) piece = iaJeu->iaPiecesJ1[11].piece;
    else    piece = iaJeu->iaPiecesJ2[11].piece;
    if (piece != NULL && pieceVulnerableIAjeu(iaJeu, jeu, piece, piece->posX, piece->posY))
        return piece;

    /*  les tours   */
    if (joueur == &jeu->J1) piece = iaJeu->iaPiecesJ1[8].piece;
    else    piece = iaJeu->iaPiecesJ2[8].piece;
    if (piece != NULL && pieceVulnerableIAjeu(iaJeu, jeu, piece, piece->posX, piece->posY))
        return piece;
    if (joueur == &jeu->J1) piece = iaJeu->iaPiecesJ1[15].piece;
    else    piece = iaJeu->iaPiecesJ2[15].piece;
    if (piece != NULL && pieceVulnerableIAjeu(iaJeu, jeu, piece, piece->posX, piece->posY))
        return piece;

    /*  les cavaliers   */
    if (joueur == &jeu->J1) piece = iaJeu->iaPiecesJ1[9].piece;
    else    piece = iaJeu->iaPiecesJ2[9].piece;
    if (piece != NULL && pieceVulnerableIAjeu(iaJeu, jeu, piece, piece->posX, piece->posY))
        return piece;
    if (joueur == &jeu->J1) piece = iaJeu->iaPiecesJ1[14].piece;
    else    piece = iaJeu->iaPiecesJ2[14].piece;
    if (piece != NULL && pieceVulnerableIAjeu(iaJeu, jeu, piece, piece->posX, piece->posY))
        return piece;

    /*  les fous   */
    if (joueur == &jeu->J1) piece = iaJeu->iaPiecesJ1[10].piece;
    else    piece = iaJeu->iaPiecesJ2[10].piece;
    if (piece != NULL && pieceVulnerableIAjeu(iaJeu, jeu, piece, piece->posX, piece->posY))
        return piece;
    if (joueur == &jeu->J1) piece = iaJeu->iaPiecesJ1[13].piece;
    else    piece = iaJeu->iaPiecesJ2[13].piece;
    if (piece != NULL && pieceVulnerableIAjeu(iaJeu, jeu, piece, piece->posX, piece->posY))
        return piece;

    /*  ... et les pions    */
    for (i=0; i<8; i++)
    {
        if (joueur == &jeu->J1) piece = iaJeu->iaPiecesJ1[i].piece;
        else    piece = iaJeu->iaPiecesJ2[i].piece ;
        if (piece != NULL && pieceVulnerableIAjeu(iaJeu, jeu, piece, piece->posX, piece->posY))
            return piece;
    }

    return NULL;
}

IApiece * rechercheIApiece(IAjeu * iaJeu, Piece * piece)
{
    int i;

    if (piece != NULL)
    {
        for (i=0; i<16; i++)
        {
            if (iaJeu->iaPiecesJ1[i].piece == piece)
                return &iaJeu->iaPiecesJ1[i];
            if (iaJeu->iaPiecesJ2[i].piece == piece)
                return &iaJeu->iaPiecesJ2[i];
        }
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
            numPiece = rand()%16;

            if (&jeu->J1 == joueur) iaPiece = &iaJeu->iaPiecesJ1[numPiece];
            else    iaPiece = &iaJeu->iaPiecesJ2[numPiece];

        } while (iaPiece->piece == NULL);

        deplacementsPossiblesIApiece(iaPiece, jeu, iaPiece->piece->posX, iaPiece->piece->posY);
        nbDeplacementsPossibles = iaPiece->nbDeplacementsPossibles;

    }while (nbDeplacementsPossibles == 0);

    return iaPiece;
}

Case * deplacementRandom(IApiece * iaPiece, Jeu * jeu)
{
    int numDeplacement = 0;
    Case * cell = NULL;

    if (iaPiece->piece != NULL)
    {
        deplacementsPossiblesIApiece(iaPiece, jeu, iaPiece->piece->posX, iaPiece->piece->posY);
        numDeplacement = rand()%(iaPiece->nbDeplacementsPossibles);
        cell = iaPiece->deplacementsPossibles[numDeplacement];
    }

    return cell;
}

Case * deplacementPrudent(IAjeu * iaJeu, IApiece * iaPiece, Jeu * jeu)
{
    int i = 0, x = 0, y = 0;
    Case * cell = NULL;
    Case * cellTemp = NULL;
    IApiece * iaPieceAdverse;

    if (iaPiece->piece != NULL)
    {
        if (iaPiece->piece->couleur == jeu->J1.couleur)  iaPieceAdverse = IApieceRandom(iaJeu, jeu, &jeu->J2);
        else    iaPieceAdverse = IApieceRandom(iaJeu, jeu, &jeu->J1);

        deplacementsPossiblesIApiece(iaPiece, jeu, iaPiece->piece->posX, iaPiece->piece->posY);
        while (i<iaPiece->nbDeplacementsPossibles)
        {
            cellTemp = iaPiece->deplacementsPossibles[i];
            getCoordCase(&jeu->plateau, cellTemp, &x, &y);
            if (!pieceProtegeeIAjeu(iaJeu, jeu, iaPieceAdverse->piece, x, y))
                    return cellTemp;
            i++;
        }
    }

    return cell;
}

IApiece * rechercheIApieceAttaquante(IAjeu * iaJeu, Piece * pieceVulnerable, Jeu * jeu, Joueur * joueur)
{
    int n, i, j;
    IApiece * iaPiece = NULL;

    /* on regarde si le roi peut attaquer   */
    if (joueur == &jeu->J1)  iaPiece = &iaJeu->iaPiecesJ1[12];
    else    iaPiece = &iaJeu->iaPiecesJ2[12];
    if (iaPiece->piece != NULL)
    {
        n = iaPiece->nbPiecesControlees;
        for (i=0; i<n; i++)
            if (iaPiece->piecesControlees[i] == pieceVulnerable)
                return iaPiece;
    }

    /*  la dame */
    if (joueur == &jeu->J1)  iaPiece = &iaJeu->iaPiecesJ1[11];
    else    iaPiece = &iaJeu->iaPiecesJ2[11];
    if (iaPiece->piece != NULL)
    {
        n = iaPiece->nbPiecesControlees;
        for (i=0; i<n; i++)
            if (iaPiece->piecesControlees[i] == pieceVulnerable)
                return iaPiece;
    }

    /*  les tours   */
    if (joueur == &jeu->J1)  iaPiece = &iaJeu->iaPiecesJ1[15];
    else    iaPiece = &iaJeu->iaPiecesJ2[15];
    if (iaPiece->piece != NULL)
    {
        n = iaPiece->nbPiecesControlees;
        for (i=0; i<n; i++)
            if (iaPiece->piecesControlees[i] == pieceVulnerable)
                return iaPiece;
    }
    if (joueur == &jeu->J1)  iaPiece = &iaJeu->iaPiecesJ1[8];
    else    iaPiece = &iaJeu->iaPiecesJ2[8];
    if (iaPiece->piece != NULL)
    {
        n = iaPiece->nbPiecesControlees;
        for (i=0; i<n; i++)
            if (iaPiece->piecesControlees[i] == pieceVulnerable)
                return iaPiece;
    }

    /*  les cavaliers   */
    if (joueur == &jeu->J1)  iaPiece = &iaJeu->iaPiecesJ1[14];
    else    iaPiece = &iaJeu->iaPiecesJ2[14];
    if (iaPiece->piece != NULL)
    {
        n = iaPiece->nbPiecesControlees;
        for (i=0; i<n; i++)
            if (iaPiece->piecesControlees[i] == pieceVulnerable)
                return iaPiece;
    }
    if (joueur == &jeu->J1)  iaPiece = &iaJeu->iaPiecesJ1[9];
    else    iaPiece = &iaJeu->iaPiecesJ2[9];
    if (iaPiece->piece != NULL)
    {
        n = iaPiece->nbPiecesControlees;
        for (i=0; i<n; i++)
            if (iaPiece->piecesControlees[i] == pieceVulnerable)
                return iaPiece;
    }

    /*  les fous    */
    if (joueur == &jeu->J1)  iaPiece = &iaJeu->iaPiecesJ1[13];
    else    iaPiece = &iaJeu->iaPiecesJ2[13];
    if (iaPiece->piece != NULL)
    {
        n = iaPiece->nbPiecesControlees;
        for (i=0; i<n; i++)
            if (iaPiece->piecesControlees[i] == pieceVulnerable)
                return iaPiece;
    }
    if (joueur == &jeu->J1)  iaPiece = &iaJeu->iaPiecesJ1[10];
    else    iaPiece = &iaJeu->iaPiecesJ2[10];
    if (iaPiece->piece != NULL)
    {
        n = iaPiece->nbPiecesControlees;
        for (i=0; i<n; i++)
            if (iaPiece->piecesControlees[i] == pieceVulnerable)
                return iaPiece;
    }

    /*  ... les pions   */
    for (j=0; j<8; j++)
    {
        if (joueur == &jeu->J1)  iaPiece = &iaJeu->iaPiecesJ1[j];
        else    iaPiece = &iaJeu->iaPiecesJ2[j];
        if (iaPiece->piece != NULL)
        {
            n = iaPiece->nbPiecesControlees;
            for (i=0; i<n; i++)
                if (iaPiece->piecesControlees[i] == pieceVulnerable)
                    return iaPiece;
        }
    }

    return NULL;
}

