CC = clang
CFLAGS = -g -O2 -std=c99 -Wall
LIBS = -lSDL -lGL -lSDL_mixer -lSDL_ttf

OBJPATH = ./obj
BINPATH = ./bin

_OBJ = main.o ingame.o paused.o gui.o targa.o
OBJ = $(patsubst %,$(OBJPATH)/%,$(_OBJ))

all: targa gui dir ingame paused main app

dir:
	mkdir -p ./obj
	mkdir -p ./bin

gui: gui.c
	$(CC) -c -o $(OBJPATH)/gui.o gui.c $(CFLAGS)

targa: targa.c
	$(CC) -c -o $(OBJPATH)/$@.o $@.c $(CFLAGS) -DTGA_COMPILE

paused: paused.c
	$(CC) -c -o $(OBJPATH)/paused.o paused.c $(CFLAGS)

ingame:
	$(CC) -c -o $(OBJPATH)/$@.o $@.c $(CFLAGS)

main:
	$(CC) -c -o $(OBJPATH)/main.o main.c $(CFLAGS)

app:
	$(CC) -o $(BINPATH)/snake $(OBJ) $(CFLAGS) $(LIBS)

clean:
	rm -f ./*~ ./$(OBJPATH)/*.o ./$(BINPATH)/*

.PHONY: clean
