CC = cc
CFLAGS = -Wall -O2
LIBS = -lSDL -lGL -lSDL_mixer

OBJPATH = ./obj
BINPATH = ./bin

_OBJ = Main.o Sound.o Graphics.o Events.o
OBJ = $(patsubst %,$(OBJPATH)/%,$(_OBJ))

clean:
	\rm -f ./*~ ./$(OBJPATH)/*.o ./$(BINPATH)/*

love:
	echo 'Not war!'

all: events graphics snd main app

debug: CFLAGS = $(CFLAGS) -g all

events:
	$(CC) -c -o $(OBJPATH)/Events.o Events.c $(LIBS) $(CFLAGS)

graphics:
	$(CC) -c -o $(OBJPATH)/Graphics.o Graphics.c $(LIBS) $(CFLAGS)

snd:
	$(CC) -c -o $(OBJPATH)/Sound.o Sound.c $(LIBS) $(CFLAGS)

main:
	$(CC) -c -o $(OBJPATH)/Main.o main.c $(LIBS) $(CFLAGS)

app:
	$(CC) -o $(BINPATH)/Snake $(OBJ) $(LIBS) $(CFLAGS)