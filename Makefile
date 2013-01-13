CC = cc
CFLAGS = -Wall -g -pg -O2 -std=c99
LIBS = -lSDL -lGL -lSDL_mixer -lSDL_ttf

OBJPATH = ./obj
BINPATH = ./bin

_OBJ = main.o ingame.o paused.o gui.o targa.o
OBJ = $(patsubst %,$(OBJPATH)/%,$(_OBJ))

clean:
	rm -f ./*~ ./$(OBJPATH)/*.o ./$(BINPATH)/*

all: targa gui dir ingame paused main app

dir:
	mkdir -p ./obj
	mkdir -p ./bin

gui: gui.c
	$(CC) -c -o $(OBJPATH)/gui.o gui.c $(LIBS) $(CFLAGS)

targa: targa.c
	$(CC) -c -o $(OBJPATH)/$@.o $@.c $(LIBS) $(CFLAGS) -DTGA_COMPILE

paused: paused.c
	$(CC) -c -o $(OBJPATH)/paused.o paused.c $(LIBS) $(CFLAGS)

ingame:
	$(CC) -c -o $(OBJPATH)/$@.o $@.c $(LIBS) $(CFLAGS)

main:
	$(CC) -c -o $(OBJPATH)/main.o main.c $(LIBS) $(CFLAGS)

app:
	$(CC) -o $(BINPATH)/snake $(OBJ) $(LIBS) $(CFLAGS)

.PHONY: clean
