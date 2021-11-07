CFLAGS = -g -std=gnu11 -Wall

minesweeper: main.o game.o minesweeper_ai.o
	gcc $(CFLAGS) -o minesweeper $^

main.o: main.c
	gcc $(CFLAGS) -c $<

game.o: game.c
	gcc $(CFLAGS) -c $<

minesweeper_ai.o: minesweeper_ai.c
	gcc $(CFLAGS) -c $<