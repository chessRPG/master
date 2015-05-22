/**

@brief Module de gestion du jeu, module principal du programme
@author GONDRAS Pierre-Louis, GREYL Robin, SCHREYECK Tiffanie
@file src/jeu.c
@version 1.0
@date 2015/05/22

*/

#include "jeu.h"

/* Interne : coloriage des cases quand une pièce est sélectionnée */

/**
@brief colorie en bleu toutes les cases que la pièce peut atteindre sur la ligne de la case (y,x)
@param jeu adresse du Jeu à modifier
@param x ordonnée de la case
@param y abscisse de la case
@return Aucun
*/

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

/**
@brief colorie en bleu toutes les cases que la pièce peut atteindre sur la colonne  de la case (y,x)
@param jeu adresse du Jeu à modifier
@param x ordonnée de la case
@param y abscisse de la case
@return Aucun
*/

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

/**
@brief colorie en bleu toutes les cases que la pièce peut atteindre sur les diagonales de la case (y,x)
@param jeu adresse du Jeu à modifier
@param x ordonnée de la case
@param y abscisse de la case
@return Aucun
*/

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

/**
@brief donne la position (y,x) de la pièce recherchée
@param plateau adresse du Plateau sur lequel on recherche la pièce
@param piece adresse de la Piece dont on veut la position
@param x pointe sur l'ordonnée de la pièce recherchée
@param y pointe sur l'abscisse de la pièce recherchée
@return Aucun
*/

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

int estDansEnsPieces(Piece * piece, Joueur * joueur)
{
    int indice = 0;

    for(indice=0; indice<joueur->nbPieces; indice++)
    {
        if (&joueur->ensPieces[indice] == piece)
            return indice;
    }

   return -1;
}

/* autre : modifications sur les chaines de caractères */

 void reverse(char s[])
 {
     int i, j;
     char c;

     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }

 void itoa(int n, char s[])
 {
     int i, sign;

     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
 }


/* accesseurs */

Joueur * getJoueurActif(Jeu * jeu)
{
    return jeu->joueurActif;
}

Joueur * getJoueurInactif(Jeu * jeu)
{
    if(&(jeu->J1) == jeu->joueurActif) return &(jeu->J2) ;
    else return &(jeu->J1) ;
}

/* Mutateurs */

void setJoueurActif(Jeu * jeu, Joueur* joueur)
{
    jeu->joueurActif = joueur;
}

void setTypeJeu(Jeu * jeu, TypeJeu type)
{
    jeu->typeJeu = type;
}

/* Création/Destruction */

void initJeu(Jeu * jeu, char * nom1, char * nom2, Couleur C1, Couleur C2)
{
    int i, j;
    Piece * piece;

    initJoueur(&jeu->J1);
    initJoueur(&jeu->J2);
    setDonneesJoueurs(&jeu->J1, &jeu->J2, nom1, nom2, C1, C2);

    setJoueurActif(jeu, &jeu->J1);
    initPlateau(&jeu->plateau, C1, C2);
    reinitCouleursEchiquier(&jeu->plateau) ;

    for (i=0; i<2; i++)
        for (j=0; j<8; j++)
        {
            piece = getPieceCase(getCase(&jeu->plateau, i, j));
            setPositionPiece(piece, i, j);
            setPieceJoueur(&jeu->J2, piece);
        }

    for (i=6; i<8; i++)
        for (j=0; j<8; j++)
        {
            piece = getPieceCase(getCase(&jeu->plateau, i, j));
            setPositionPiece(piece, i, j);
            setPieceJoueur(&jeu->J1, piece);
        }

    sprintf(jeu->log, "Debut de la partie !") ;
}

void detruireJeu(Jeu * jeu)
{
    jeu->joueurActif = NULL;
    viderPlateau(&jeu->plateau);
}


/* fonctions de création des logs */

/**
@brief crée un log lors du déplacement d'une pièce
@param log chaine de caractères où écrire
@param piece adresse de la Piece qui se déplace
@param i abcisse d'origine de la pièce
@param j ordonnée d'origine de la pièce
@param posX abcisse d'arrivée de la pièce
@param posY ordonnée d'arrivée de la pièce
@return Aucun
*/

void logDeplacement(char * log, Piece * piece, int i, int j, int posX, int posY)
{

    char buffer[8] ;
    switch(getTypePiece(piece))
    {
    case PION:
        sprintf(log, "Le pion en ") ;
        break ;
    case TOUR:
        sprintf(log, "La tour en ") ;
        break ;
    case CAVALIER:
        sprintf(log, "Le cavalier en ") ;
        break ;
    case FOU:
        sprintf(log, "Le fou en ") ;
        break ;
    case DAME:
        sprintf(log, "La dame en ") ;
        break ;
    case ROI:
        sprintf(log, "Le roi en ") ;
        break ;
    }

    itoa(j, buffer) ;
    buffer[0] = buffer[0] + 'A' - '0';
    strcat(log, buffer) ;
    itoa(8-i, buffer) ;
    strcat(log, buffer) ;
    strcat(log, " se deplace en ") ;
    itoa(posY, buffer) ;
    buffer[0] = buffer[0] + 'A' - '0';
    strcat(log, buffer) ;
    itoa(8-posX, buffer) ;
    strcat(log, buffer) ;
}

/**
@brief écrit le type de la pièce et le joueur qui la possède
@param log chaine de caractères où écrire
@param piece adresse de la Piece dont on veut le type dans le log
@param jeu adresse du Jeu (nécessaire pour connaitre le nom du joueur actif)
@return Aucun
*/

void logNomPiece(char * log, Piece * piece, Jeu * jeu)
{
    switch(getTypePiece(piece))
    {
    case PION:
        strcat(log, "le pion de ") ;
        break ;
    case TOUR:
        strcat(log, "la tour de ") ;
        break ;
    case CAVALIER:
        strcat(log, "le cavalier de ") ;
        break ;
    case FOU:
        strcat(log, "le fou de ") ;
        break ;
    case DAME:
        strcat(log, "la dame de ") ;
        break ;
    case ROI:
        strcat(log, "le roi de ") ;
        break ;
    }

    if(getCouleurPiece(piece) == getCouleurJoueur(&(jeu->J1)))
    {
        strcat(log, getNomJoueur(&(jeu->J1))) ;
    }
    else
    {
        strcat(log, getNomJoueur(&(jeu->J2))) ;
    }
}

/**
@brief crée la première ligne du log de combat
@param log chaine de caractères où écrire
@param pieceAtt adresse de la Piece attaquante
@param pieceDef adresse de la Piece en défense
@param jeu adresse du Jeu (nécessaire pour appeler logNomPiece)
@see logNomPiece
@return Aucun
*/

void initLogCombat(char * log, Piece * pieceAtt, Piece * pieceDef, Jeu * jeu)
{
    log[0] = '\0' ;
    logNomPiece(log, pieceAtt, jeu) ;
    strcat(log, " attaque ") ;
    logNomPiece(log, pieceDef, jeu) ;
    strcat(log, ".,") ;
}

/**
@brief ajoute les pièces gagnante et perdante dans le log
@param log chaine de caractère où écrire
@param vainqueur adresse de la Piece qui a gagné le combat
@param perdant adresse de la Piece qui a perdu
@param jeu adresse du Jeu
@return Aucun
*/

void logCombat(char * log, Piece * vainqueur, Piece * perdant, Jeu * jeu)
{
    char buffer[8] ;
    logNomPiece(log, vainqueur, jeu) ;
    strcat(log, " gagne,contre ") ;
    logNomPiece(log, perdant, jeu) ;
    strcat(log, ". Il lui reste ") ;
    itoa(getPointsVie(vainqueur), buffer) ;
    strcat(log, buffer) ;
    strcat(log, "PV.,") ;
}


/* fonctions de jeu */

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
                if (((joueur == &jeu->J1 && posX == 6) || (joueur == &jeu->J2 && posX == 1)) && (getCouleurCase(getCase(&(jeu->plateau), posX+a, posY)) == CBLEU && getPieceCase(getCase(&(jeu->plateau), posX+2*a, posY)) == NULL))
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

void deplacerPiece(Jeu * jeu, Piece * piece, int posFinX, int posFinY, Couleur * couleurGagne)
{
    Plateau * plateau = &(jeu->plateau) ;
    int posInitX = piece->posX;
    int posInitY = piece->posY;

    logDeplacement(jeu->log, piece, posInitX, posInitY, posFinX, posFinY) ;

    setPieceCase(getCase(plateau, posInitX, posInitY), NULL);

    if(getPieceCase(getCase(plateau, posFinX, posFinY)) != NULL)
        piece = combatPieces(jeu, piece, getPieceCase(getCase(plateau, posFinX, posFinY)), couleurGagne);

    setPieceCase(getCase(plateau, posFinX, posFinY), piece);
    piece->posX = posFinX;
    piece->posY = posFinY;

    jeu->plateau.nbTours++;
}

Piece* combatPieces(Jeu * jeu, Piece * pieceAtt, Piece * pieceDef, Couleur * couleurGagne)
{
    int BONUS = 1;
    int vie;

    initLogCombat(jeu->log, pieceAtt, pieceDef, jeu) ;

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
        logCombat(jeu->log, pieceAtt, pieceDef, jeu) ;

        if(pieceDef->type == ROI) *couleurGagne = getCouleurPiece(pieceAtt) ;
        detruirePiece(pieceDef) ;

        if (estDansEnsPieces(pieceDef, &jeu->J1))   jeu->J1.nbPieces--;
        else if (estDansEnsPieces(pieceDef, &jeu->J2))   jeu->J2.nbPieces--;

        return pieceAtt ;
    }
    else
    {
        logCombat(jeu->log, pieceDef, pieceAtt, jeu) ;

        if(pieceAtt->type == ROI) *couleurGagne = getCouleurPiece(pieceDef) ;
        detruirePiece(pieceAtt) ;

        if (estDansEnsPieces(pieceAtt, &jeu->J1))   jeu->J1.nbPieces--;
        else if (estDansEnsPieces(pieceAtt, &jeu->J2))   jeu->J2.nbPieces--;

        return pieceDef ;
    }
}
