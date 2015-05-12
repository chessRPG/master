 #include <string.h>

  /* reverse:  reverse string s in place */
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

/**

@brief Module de gestion des joueurs
@author GONDRAS Pierre-Louis, GREYL Robin, SCHREYECK Tiffanie
@file src/jeu.c
@version 1.0
@date 2014/04/21

*/

#include "jeu.h"

/*  Création/Destruction    */

/**
@brief initialise les joueurs, le plateau, et donne la main au joueur 1
@param jeu adresse du Jeu à initialiser
@param piecesJ1 chemin d'accès des pièces du Joueur 1
@param piecesJ2 chemin d'accès des pièces du Joueur 2
@return Aucun
*/

void initJeu(Jeu * jeu, char * piecesJ1, char * piecesJ2, char * log)
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

    sprintf(log, "Debut de la partie !") ;
}

/**
@brief remet le joueur actif à NULL et détruit le plateau
@param jeu adresse du Jeu à détruire
@return Aucun
*/

void detruireJeu(Jeu * jeu)
{
    jeu->joueurActif = NULL;
    viderPlateau(&jeu->plateau);
}

/* Interne */

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

/* Accesseurs */

/**
@brief renvoie l'adresse du joueur actif
@param jeu adresse du Jeu courant
@return adresse du Joueur actif
*/

Joueur * getJoueurActif(Jeu * jeu)
{
    return jeu->joueurActif;
}

/**
@brief renvoie l'adresse du joueur inactif
@param jeu adresse du Jeu courant
@return adresse du Joueur inactif
*/

Joueur * getJoueurInactif(Jeu * jeu)
{
    if(&(jeu->J1) == jeu->joueurActif) return &(jeu->J2) ;
    else return &(jeu->J1) ;
}

/**
@brief selectionne une pièce et affiche les cases où elle peut se rendre
@param jeu adresse du Jeu courant
@param posX ordonnée de la Piece sélectionnée
@param posY abscisse de la Piece sélectionnée
@return Aucun
*/

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

/* Mutateurs */

/**
@brief modifie l'adresse contenue dans joueurActif
@param jeu adresse du Jeu courant
@param joueur adresse du Joueur qui devient le joueur actif
@return Aucun
*/

void setJoueurActif(Jeu * jeu, Joueur* joueur)
{
    jeu->joueurActif = joueur;
}
/* fonctions de jeu */

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
@brief déplace la pièce sélectionnée à la position (y,x) et déclenche un combat si la case est occupée
@param plateau adresse du Plateau de jeu
@param piece adresse de la Piece à déplacer
@param posX abscisse de la Case d'arrivée
@param posY ordonnée de la Case d'arrivée
@param couleurGagne adresse de la couleur gagnante si un combat se déclenche
@see combatPieces
@return Aucun
*/

void deplacerPiece(Plateau * plateau, Piece * piece, int posX, int posY, Couleur * couleurGagne, char * log, Jeu * jeu)
{
    int i = 0, j = 0;

    rechercherPiece(plateau, piece, &i, &j);

    logDeplacement(log, piece, i, j, posX, posY) ;

    setPieceCase(getCase(plateau, i, j), NULL);

    if(getPieceCase(getCase(plateau, posX, posY)) != NULL)
        piece = combatPieces(piece, getPieceCase(getCase(plateau, posX, posY)), couleurGagne, log, jeu);

    setPieceCase(getCase(plateau, posX, posY), piece);
}

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

void initLogCombat(char * log, Piece * pieceAtt, Piece * pieceDef, Jeu * jeu)
{
    log[0] = '\0' ;
    logNomPiece(log, pieceAtt, jeu) ;
    strcat(log, " attaque ") ;
    logNomPiece(log, pieceDef, jeu) ;
    strcat(log, ".\n") ;
}

void logCombat(char * log, Piece * vainqueur, Piece * perdant, Jeu * jeu)
{
    char buffer[8] ;
    logNomPiece(log, vainqueur, jeu) ;
    strcat(log, " gagne contre ") ;
    logNomPiece(log, perdant, jeu) ;
    strcat(log, ". Il lui reste ") ;
    itoa(getPointsVie(vainqueur), buffer) ;
    strcat(log, buffer) ;
    strcat(log, "PV.") ;
}


/**
@brief fait combattre les deux pièces passées en paramètre et détruit la pièce perdante
@param pieceAtt adresse de la Piece attaquante
@param pieceDef adresse de la Piece en défense
@param couleurGagne contient la Couleur de la Piece qui a gagné le combat à la fin de la fonction
@return adresse de la Piece qui gagne le combat
*/

Piece* combatPieces(Piece * pieceAtt, Piece * pieceDef, Couleur * couleurGagne, char * log, Jeu * jeu)
{
    int BONUS = 1;
    int vie;

    initLogCombat(log, pieceAtt, pieceDef, jeu) ;

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
        logCombat(log, pieceAtt, pieceDef, jeu) ;
        if(pieceDef->type == ROI) *couleurGagne = getCouleurPiece(pieceAtt) ;
        detruirePiece(pieceDef) ;
        return pieceAtt ;
    }
    else
    {
        logCombat(log, pieceDef, pieceAtt, jeu) ;
        if(pieceAtt->type == ROI) *couleurGagne = getCouleurPiece(pieceDef) ;
        detruirePiece(pieceAtt) ;
        return pieceDef ;
    }
}
