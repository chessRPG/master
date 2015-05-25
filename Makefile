CC = gcc -Wall -pedantic -ansi -c
OBJ = src/ia.o obj/jeu.o obj/plateau.o obj/case.o obj/piece.o obj/joueur.o obj/couleur.o
H = src/ia.h src/jeu.h src/plateau.h src/case.h src/piece.h src/joueur.h src/couleur.h

all: sdl ncurses

sdl: obj/sdl.o obj/afficheSDL.o $(OBJ)
	gcc obj/sdl.o obj/afficheSDL.o $(OBJ) -lSDL -lSDL_ttf -lSDL_image -o bin/ChessRPG_sdl

ncurses: obj/ncurses.o obj/afficheNCURSES.o $(OBJ)
	gcc obj/ncurses.o obj/afficheNCURSES.o $(OBJ) -lncurses -o bin/ChessRPG_ncurses

obj/sdl.o: src/main.c src/afficheSDL.h $(H)
	$(CC) src/main.c -DJEU_SDL -o obj/sdl.o

obj/afficheSDL.o: src/afficheSDL.c src/afficheSDL.h $(H)
	$(CC) src/afficheSDL.c -o obj/afficheSDL.o

obj/ncurses.o: src/main.c src/afficheNCURSES.h $(H)
	$(CC) src/main.c -DJEU_NCURSES -o obj/ncurses.o

obj/afficheNCURSES.o: src/afficheNCURSES.c src/afficheNCURSES.h $(H)
	$(CC) src/afficheNCURSES.c -o obj/afficheNCURSES.o

obj/ia.o: src/ia.c src/ia.h src/jeu.h src/plateau.h src/case.h src/piece.h src/joueur.h src/couleur.h
	$(CC) src/ia.c -o obj/ia.o
	
obj/jeu.o: src/jeu.c src/jeu.h src/plateau.h src/case.h src/piece.h src/joueur.h src/couleur.h
	$(CC) src/jeu.c -o obj/jeu.o

obj/plateau.o: src/plateau.c src/plateau.h src/case.h src/piece.h src/couleur.h
	$(CC) src/plateau.c -o obj/plateau.o

obj/case.o: src/case.c src/case.h src/piece.h src/couleur.h
	$(CC) src/case.c -o obj/case.o

obj/piece.o: src/piece.c src/piece.h src/couleur.h
	$(CC) src/piece.c -o obj/piece.o

obj/joueur.o: src/joueur.c src/joueur.h src/couleur.h
	$(CC) src/joueur.c -o obj/joueur.o

obj/couleur.o: src/couleur.c src/couleur.h
	$(CC) src/couleur.c -o obj/couleur.o

clean:
	rm -rf obj/*.o
