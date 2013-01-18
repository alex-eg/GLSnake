CC = clang
CFLAGS = -g -O2 -std=c99 -Wall -I$(INCPATH)
LIBS = -lSDL -lGL -lSDL_mixer -lSDL_ttf

OBJPATH = ./obj
BINPATH = ./bin
SRCPATH = ./src
INCPATH = ./include

MODULES = main ingame paused gui targa

DEPS = $(INCPATH)/*.h
OBJ = $(MODULES:%=$(OBJPATH)/%.o)

all: snake
	cp $(BINPATH)/$< ./

$(OBJPATH)/%.o : $(SRCPATH)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) 

snake: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(BINPATH)/$@ $(LIBS) $(CFLAGS)

dir:
	mkdir -p ./obj
	mkdir -p ./bin

clean:
	rm -f *~ $(OBJPATH)/*.o $(BINPATH)/* $(SRCPATH)/*~ $(INCPATH)/*~

.PHONY: clean
