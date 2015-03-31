#include "jeu.h"

/* Interne */
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

/* Accesseurs */

Joueur * getJoueurActif(Jeu * jeu)
{
    return jeu->joueurActif;
}

void selectPiece(Jeu * jeu, int posX, int posY)
{
    int i, j;
    Joueur * joueur = getJoueurActif(jeu);
    Piece * piece = getPieceCase(getCase(&(jeu->plateau), posX, posY));

    reinitCouleursEchiquier(&(jeu->plateau));

    if(piece != NULL && joueur->couleur == getCouleurPiece(piece))
    {

        setCouleurCase(getCase(&(jeu->plateau), posX, posY), CBLEU);

        switch(piece->type)
        {
            case PION:
                if(joueur == &(jeu->J1))
                {
                    if(posX-1 >= 0 && getPieceCase(getCase(&(jeu->plateau), posX-1, posY)) == NULL)
                        setCouleurCase(getCase(&(jeu->plateau), posX-1, posY), CBLEU);
                    if(posX == 6 && posX-2 >= 0 && getPieceCase(getCase(&(jeu->plateau), posX-2, posY)) == NULL)
                        setCouleurCase(getCase(&(jeu->plateau), posX-2, posY), CBLEU);
                }
                else
                {
                    if(posX+1 < 8 && getPieceCase(getCase(&(jeu->plateau), posX+1, posY)) == NULL)
                        setCouleurCase(getCase(&(jeu->plateau), posX+1, posY), CBLEU);
                    if(posX == 1 && posX+2 < 8 && getPieceCase(getCase(&(jeu->plateau), posX+2, posY)) == NULL)
                        setCouleurCase(getCase(&(jeu->plateau), posX+2, posY), CBLEU);
                }
                break ;
            case TOUR:
                /*for(i = 0 ; i < 8 ; i++)
                {
                    if (getPieceCase(getCase(&(jeu->plateau), i, posY)) == NULL)
                        setCouleurCase(getCase(&(jeu->plateau), i, posY), CBLEU);
                    if ()
                    setCouleurCase(getCase(&(jeu->plateau), posX, i), CBLEU);
                }*/
                break ;
            case CAVALIER:
                if(posX+2 < 8)
                {
                    if(posY+1 < 8 && getPieceCase(getCase(&(jeu->plateau), posX+2, posY-1)) == NULL)
                        setCouleurCase(getCase(&(jeu->plateau), posX+2, posY+1), CBLEU);
                    if(posY-1 >= 0 && getPieceCase(getCase(&(jeu->plateau), posX+2, posY-1)) == NULL)
                        setCouleurCase(getCase(&(jeu->plateau), posX+2, posY-1), CBLEU);
                }
                if(posX-2 >= 0)
                {
                    if(posY+1 < 8) setCouleurCase(getCase(&(jeu->plateau), posX-2, posY+1), CBLEU);
                    if(posY-1 >= 0) setCouleurCase(getCase(&(jeu->plateau), posX-2, posY-1), CBLEU);
                }
                if(posX+1 < 8)
                {
                    if(posY+2 < 0) setCouleurCase(getCase(&(jeu->plateau), posX+1, posY+2), CBLEU);
                    if(posY-2 >= 0) setCouleurCase(getCase(&(jeu->plateau), posX+1, posY-2), CBLEU);
                }
                if(posX-2 >= 0)
                {
                    if(posY+2 < 0) setCouleurCase(getCase(&(jeu->plateau), posX-1, posY+2), CBLEU);
                    if(posY-2 >= 0) setCouleurCase(getCase(&(jeu->plateau), posX-1, posY-2), CBLEU);
                }
                break ;
            case FOU:
                i = 0;
                while(posX+i < 8 && posY+i < 8 && getPieceCase(getCase(&(jeu->plateau), posX+i, posY+i)) == NULL)
                {
                    setCouleurCase(getCase(&(jeu->plateau), posX+i, posY+i), CBLEU);
                    i++;
                }

                i = 0;
                while(posX-i >= 0 && posY-i >= 0 && getPieceCase(getCase(&(jeu->plateau), posX-i, posY-i)) == NULL)
                {
                    setCouleurCase(getCase(&(jeu->plateau), posX-i, posY-i), CBLEU);
                    i++;
                }

                i = 0;
                while(posX+i < 8 && posY-i >= 0 && getPieceCase(getCase(&(jeu->plateau), posX+i, posY-i)) == NULL)
                {
                    setCouleurCase(getCase(&(jeu->plateau), posX+i, posY-i), CBLEU);
                    i++;
                }

                i = 0;
                while(posX-i >= 0 && posY+i < 8 && getPieceCase(getCase(&(jeu->plateau), posX-i, posY+i)) == NULL)
                {
                    setCouleurCase(getCase(&(jeu->plateau), posX-i, posY+i), CBLEU);
                    i++;
                }
                break ;
            case DAME:
                for(i = 0 ; i < 8 ; i++)
                {
                    setCouleurCase(getCase(&(jeu->plateau), i, posY), CBLEU);
                    setCouleurCase(getCase(&(jeu->plateau), posX, i), CBLEU);
                }
                i = 0;
                while(posX+i < 8 && posY+i < 8 && getPieceCase(getCase(&(jeu->plateau), posX+i, posY+i)) == NULL)
                {
                    setCouleurCase(getCase(&(jeu->plateau), posX+i, posY+i), CBLEU);
                    i++;
                }

                i = 0;
                while(posX-i >= 0 && posY-i >= 0 && getPieceCase(getCase(&(jeu->plateau), posX-i, posY-i)) == NULL)
                {
                    setCouleurCase(getCase(&(jeu->plateau), posX-i, posY-i), CBLEU);
                    i++;
                }

                i = 0;
                while(posX+i < 8 && posY-i >= 0 && getPieceCase(getCase(&(jeu->plateau), posX+i, posY-i)) == NULL)
                {
                    setCouleurCase(getCase(&(jeu->plateau), posX+i, posY-i), CBLEU);
                    i++;
                }

                i = 0;
                while(posX-i >= 0 && posY+i < 8 && getPieceCase(getCase(&(jeu->plateau), posX-i, posY+i)) == NULL)
                {
                    setCouleurCase(getCase(&(jeu->plateau), posX-i, posY+i), CBLEU);
                    i++;
                }
                break ;
            case ROI:
                for (i = posX-1 ; i<posX+2 ; i++)
                {
                    for (j = posY-1; j<posY+2; j++)
                    {
                        if (i<8 && i>=0 && j<8 && j>=0)
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
