

all:
	gcc oyun.c -o space -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2

run:
	./space