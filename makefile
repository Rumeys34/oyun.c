
CC = gcc
# Mac Homebrew yollarını doğrudan ekliyoruz
CFLAGS = -Wall -Wextra -std=c11 $(shell sdl2-config --cflags) -I/opt/homebrew/include
LIBS = $(shell sdl2-config --libs) -lSDL2_image -lSDL2_mixer -L/opt/homebrew/lib

SRC = oyun.c
OBJ = $(SRC:.c=.o)
EXE = oyun

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXE)

run: all
	./$(EXE)

