CC = cc
CFLAGS = -Wall -O2
LIBS = -lSDL -lGL

OBJPATH = ./obj
BINPATH = ./bin

clean:
	rm -rf ./*~ ./$(OBJPATH)/*.o ./$(BINPATH)/*

love:
	echo 'Not war!'

all: events graphics main app

debug: CFLAGS = $(CFLAGS) -g all

events:
	$(CC) -c -o $(OBJPATH)/Events.o Events.c $(LIBS) $(CFLAGS)

graphics:
	$(CC) -c -o $(OBJPATH)/Graphics.o Graphics.c $(LIBS) $(CFLAGS)

main:
	$(CC) -c -o $(OBJPATH)/Main.o main.c $(LIBS) $(CFLAGS) -I$(OBJPATH)

app:
	$(CC) -o $(BINPATH)/Snake $(OBJPATH)/Main.o $(OBJPATH)/Graphics.o $(OBJPATH)/Events.o $(LIBS) $(CFLAGS)