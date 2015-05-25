**************
** ChessRPG **
**************

Arborescence :
bin 	: executables
data	: fichiers utilisés par le programme
doc  	: documentation (générée avec Doxygen)
src	: fichier sources (.h & .c)

ChessRPG.cbp 	: projet CodeBlocks du programme
Makefile     	: génération des fichiers executables
_________________________________________________________________________

Commandes du Makefile :
make all 	: génère les executables ncurses et sdl
make ncurses 	: génère un executable utilisant ncurses pour l'interface
make sdl     	: génère un executable utilsiant sdl pour l'affichage
make clean	: supprime les fichiers objets générés à la compilation

Utilisable avec Linux

Les libraires SDL, SDL_ttf, SDL_image, et ncurses doivent être installées.
_________________________________________________________________________

La page d'accueil de la documentation se situe dans doc/html/index.html
