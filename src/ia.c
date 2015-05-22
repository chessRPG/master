#include "ia.h"

void ia (Jeu * jeu, Couleur * couleurGagne)
{
    int nbTours = getNbTours(&jeu->plateau);
    Piece * piece = getPieceCase(getCase(&jeu->plateau, 1, 4));

    if (nbTours == 0)
        deplacerPiece(jeu, piece, 2, 4, couleurGagne);

    if (nbTours == 1)
    {
        piece = getPieceCase(getCase(&jeu->plateau, 2, 4));
        deplacerPiece(jeu, piece, 3, 4, couleurGagne);
    }

}
