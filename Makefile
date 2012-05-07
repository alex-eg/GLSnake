CC = cc
CFLAGS = -Wall -O2 -g -pg
LIBS = -lSDL -lGL -lSDL_mixer

OBJPATH = ./obj
BINPATH = ./bin

_OBJ = Main.o InGame.o Paused.o
OBJ = $(patsubst %,$(OBJPATH)/%,$(_OBJ))

clean:
	rm -f ./*~ ./$(OBJPATH)/*.o ./$(BINPATH)/*

all: dir ingame paused main app

dir:
	mkdir -p ./obj
	mkdir -p ./bin

paused:
	$(CC) -c -o $(OBJPATH)/Paused.o Paused.c $(LIBS) $(CFLAGS)

ingame:
	$(CC) -c -o $(OBJPATH)/InGame.o InGame.c $(LIBS) $(CFLAGS)

main:
	$(CC) -c -o $(OBJPATH)/Main.o main.c $(LIBS) $(CFLAGS)

app:
	$(CC) -o $(BINPATH)/Snake $(OBJ) $(LIBS) $(CFLAGS)
