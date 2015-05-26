/**

@brief Module de l'intelligence artificielle
@author GONDRAS Pierre-Louis, GREYL Robin, SCHREYECK Tiffanie
@file src/ia.h
@version 1.0
@date 2015/05/22

*/

#ifndef _IA_H
#define _IA_H

#include <stdlib.h>
#include <time.h>

#include "jeu.h"

/**
@struct IApiece
@brief structure associée à une pièce contenant toutes ses spécificités
@param nbCasesControlees le nombre de cases sur lesquelles la pièce peut se déplacer (même si une pièce aliée est dessus)
@param casesControlees tableau de cases sur lesquelles la pièce peut se déplacer (même si une pièce aliée est dessus)
@param nbPiecesControlees nombre de pièces (alliées et ennemies) positionnées sur les cases sur lesquelles la pièce peut se déplacer
@param piecesControlees tableau contenant les adresses despièces (alliées et ennemies) positionnées sur les cases sur lesquelles la pièce peut se déplacer
@param nbDeplacementsPossibles le nombre de cases sur lesquelle la pieces peut se déplacer (vides ou occupées pas un ennemie)
@param deplacementsPossibles les cases sur lesquelle la pieces peut se déplacer (vides ou occupées pas un ennemie)
@see Piece
*/
typedef struct
{
    Piece * piece;

    int nbCasesControlees;
    Case * casesControlees[27];

    int nbPiecesControlees;
    Piece * piecesControlees[8];

    int nbDeplacementsPossibles;
    Case * deplacementsPossibles[27];
} IApiece ;

/**
@struct IAjeu
@brief structure contenant les IApieces de chaque joueur
@param iaPiecesJ1 tableau des IApieces du joueur 1
@param iaPiecesJ2 tableau des IApieces du joueur 2
*/
typedef struct
{
    IApiece iaPiecesJ1[16];
    IApiece iaPiecesJ2[16];
} IAjeu ;

/*  Fonction principale IA   */
/**
@brief fonction principale de l'ia
@param jeu pointeur vers Jeu
@return Aucun
*/
void ia (Jeu * jeu);



/*  Initialisation  */
/**
@brief initialise toutes les IAPieces
@param iaJeu pointeur vers IAjeu
@param jeu pointeur vers Jeu
@return Aucun
*/
void initIAjeu(IAjeu * iaJeu, Jeu * jeu);

/**
@brief initialise une IApiece
@param iaPiece pointeur vers IApiece
@param jeu pointeur vers Jeu
@param piece pointeur vers la piece à initialiser
@return Aucun
*/
void initIApiece(IApiece * iaPiece, Jeu * jeu, Piece * piece);
/**
@brief remet toutes les données d'une IApiece à NULL
@param iaPiece pointeur vers l'IApiece à reset
@return
*/
void resetIApiece(IApiece * iaPiece);



/*  Mutateurs  */
/**
@brief ajoute une case à l'ensemble des cases controlées par une pièce
@param iaPiece pointeur vers l'IApiece dont on veut ajouter la case
@param cell pointeur vers la case à rajouter
@return Aucun
*/
void setCaseControleeIApiece(IApiece * iaPiece, Case * cell);

/**
@brief ajoute une piece à l'ensemble des pieces controlées par une pièce
@param iaPiece pointeur vers l'IApiece dont on veut ajouter la piece
@param piece pointeur vers la piece à rajouter
@return Aucun
*/
void setPieceControleeIApiece(IApiece * iaPiece, Piece * piece);

/**
@brief ajoute une case à l'ensemble des cases vers laquelle une pièce peut se déplacer
@param iaPiece pointeur vers l'IApiece dont on veut ajouter la case
@param cell pointeur vers la case à rajouter
@return Aucun
*/
void setDeplacementPossibleIApiece(IApiece * iaPiece, Case * cell);



/*  Fonctions de l'IA   */
/**
@brief détermine les cases et les pieces contrôlèes par une piece si elle était à une position donnée
@param iaPiece pointeur vers l'IApiece dont on va chercher le contrôle
@param jeu pointeur vers le Jeu
@param x numero de la ligne
@param y numero de la colonne
@return Aucun
*/
void casesPiecesControleesIApiece(IApiece * iaPiece, Jeu * jeu, int x, int y);

/**
@brief détermine les pieces contrôlèes par une piece si elle était à une position donnée
@param iaPiece pointeur vers l'IApiece dont on va chercher le controle
@return Aucun
*/
void piecesControleesIApiece(IApiece * iaPiece);

/**
@brief détermine les déplacement squ'une piece pourrait faire si elle était à une position donnée
@param iaPiece pointeur vers l'IApiece dont on va chercher les informations
@param jeu pointeur vers le Jeu
@param x numero de la ligne
@param y numero de la colonne
@return Aucun
*/
void deplacementsPossiblesIApiece(IApiece * iaPiece, Jeu * jeu, int x, int y);


/**
@brief détermine si une piece est vulnérable si elle était à une position donnée
@param iaJeu pointeur vers IAjeu
@param jeu pointeur vers Jeu
@param piece pointeur vers une piece
@param x numero de la ligne
@param y numero de la colonne
@return vrai si la pièce est vulnérable, faux sinon
*/
bool pieceVulnerableIAjeu(IAjeu * iaJeu, Jeu * jeu, Piece * piece, int x, int y);

/**
@brief détermine si une pièce est protégée si elle était à une position donnée
@param iaJeu pointeur vers IAjeu
@param jeu pointeur vers Jeu
@param piece pointeur vers la pièce
@param x numero de la ligne
@param y numero de la colonne
@return vrai si la pièce est protégée, faux sinon
*/
bool pieceProtegeeIAjeu(IAjeu * iaJeu, Jeu * jeu, Piece * piece, int x, int y);

/**
@brief recherche si un joueur est vulnérable
@param iaJeu pointeur vers IAjeu
@param jeu pointeur vers Jeu
@param joueur pointeur vers le joueur
@return pointeur vers la pièce vulnérable
*/
Piece * joueurVulnerableIAjeu(IAjeu * iaJeu, Jeu * jeu, Joueur * joueur);


/**
@brief choisit une pièce aléatoirement parmi celles du joueur
@param iaJeu pointeur vers IAjeu
@param jeu pointeur vers Jeu
@param joueur pointeur vers le joueur
@param joueur pointeur vers le joueur
@return pointeur sur l'IApiece
*/
IApiece * IApieceRandom(IAjeu * iaJeu, Jeu * jeu, Joueur * joueur);

/**
@brief choisit une case aléatoirement sur laquelle la pièce peut se déplacer
@param iaJeu pointeur vers IAjeu
@param jeu pointeur vers Jeu
@return pointeur sur la case
*/
Case * deplacementRandom(IApiece * iaPiece, Jeu * jeu);

/**
@brief choisit un déplacement qui ne mettrait pas la pièce en danger
@param iaJeu pointeur vers IAjeu
@param iaPiece pointeur vers IApiece
@param jeu pointeur vers Jeu
@return pointeur sur la case
*/
Case * deplacementPrudent(IAjeu * iaJeu, IApiece * iaPiece, Jeu * jeu);



/**
@brief recherche l'IApiece d'une pièce donnée
@param iaJeu pointeur vers IAjeu
@param piece pointeur vers la pièce
@return pointeur vers l'IApiece
*/
IApiece * rechercheIApiece(IAjeu * iaJeu, Piece * piece);

/**
@brief recherche une pièce qui peut attaquer la pieceVulnerable
@param iaJeu pointeur sur IAjeu
@param piece pointeur sur la pièce vulnérable
@param jeu pointeur sur le jeu
@param joueur pointeur sur le joueur attaquant
@return pointeur sur l'IApiece de la pièce attaquante
*/
IApiece * rechercheIApieceAttaquante(IAjeu * iaJeu, Piece * pieceVulnerable, Jeu * jeu, Joueur * joueur);

#endif
