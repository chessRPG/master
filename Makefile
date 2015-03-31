CC = gcc -Wall -pedantic -ansi -c



all: ncurses

ncurses: obj/ncurses.o obj/afficheNCURSES.o obj/jeu.o obj/plateau.o obj/case.o obj/piece.o obj/joueur.o obj/couleur.o
	gcc obj/ncurses.o obj/afficheNCURSES.o obj/jeu.o obj/plateau.o obj/case.o obj/piece.o obj/joueur.o obj/couleur.o -lncurses -o bin/ncurses

obj/ncurses.o: src/main.c src/afficheNCURSES.h src/jeu.h src/plateau.h src/case.h src/piece.h src/joueur.h src/couleur.h
	$(CC) src/main.c -DNCURSES -o obj/ncurses.o

obj/afficheNCURSES.o: src/afficheNCURSES.c src/afficheNCURSES.h src/jeu.h src/plateau.h src/case.h src/piece.h src/joueur.h src/couleur.h
	$(CC) src/afficheNCURSES.c -o obj/afficheNCURSES.o

obj/jeu.o: src/jeu.c src/jeu.h src/plateau.h src/case.h src/piece.h src/joueur.h  src/couleur.h
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
