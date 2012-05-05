CC = cc
CFLAGS = -Wall -O2 -g -pg
LIBS = -lSDL -lGL -lSDL_mixer

OBJPATH = ./obj
BINPATH = ./bin

_OBJ = Main.o InGame.o
OBJ = $(patsubst %,$(OBJPATH)/%,$(_OBJ))

clean:
	rm -f ./*~ ./$(OBJPATH)/*.o ./$(BINPATH)/*

all: dir ingame main app

dir:
	mkdir -p ./obj
	mkdir -p ./bin

ingame:
	$(CC) -c -o $(OBJPATH)/InGame.o InGame.c $(LIBS) $(CFLAGS)

main:
	$(CC) -c -o $(OBJPATH)/Main.o main.c $(LIBS) $(CFLAGS)

app:
	$(CC) -o $(BINPATH)/Snake $(OBJ) $(LIBS) $(CFLAGS)
