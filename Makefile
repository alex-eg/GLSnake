CC = cc
CFLAGS = -Wall -g -pg -O2
LIBS = -lSDL -lGL -lSDL_mixer -lSDL_ttf

OBJPATH = ./obj
BINPATH = ./bin

_OBJ = main.o inGame.o paused.o
OBJ = $(patsubst %,$(OBJPATH)/%,$(_OBJ))

clean:
	rm -f ./*~ ./$(OBJPATH)/*.o ./$(BINPATH)/*

all: dir ingame paused main app

dir:
	mkdir -p ./obj
	mkdir -p ./bin

paused: paused.c
	$(CC) -c -o $(OBJPATH)/paused.o paused.c $(LIBS) $(CFLAGS)

ingame:
	$(CC) -c -o $(OBJPATH)/inGame.o inGame.c $(LIBS) $(CFLAGS)

main:
	$(CC) -c -o $(OBJPATH)/main.o main.c $(LIBS) $(CFLAGS)

app:
	$(CC) -o $(BINPATH)/snake $(OBJ) $(LIBS) $(CFLAGS)

.PHONY: clean
