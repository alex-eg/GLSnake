CC = clang
CFLAGS = -g -O2 -std=c99 -Wall -I$(INCPATH)
LIBS = -lSDL -lGL -lSDL_mixer -lSDL_ttf

OBJPATH = ./obj
BINPATH = ./bin
SRCPATH = ./src
INCPATH = ./include

MODULES = main ingame paused gui targa mainmenu

DEPS = $(INCPATH)/*.h
OBJ = $(MODULES:%=$(OBJPATH)/%.o)

all: $(BINPATH)/snake
	cp $< ./

$(OBJPATH)/%.o : $(SRCPATH)/%.c $(DEPS) | $(OBJPATH)
	$(CC) -c -o $@ $< $(CFLAGS) 

$(BINPATH)/snake: $(OBJ) | $(BINPATH)
	$(CC) $^ -o $@ $(LIBS) $(CFLAGS)

$(OBJPATH):	
	mkdir -p $(OBJPATH)

$(BINPATH):
	mkdir -p $(BINPATH)

clean:
	rm -f *~ $(OBJPATH)/*.o $(BINPATH)/* $(SRCPATH)/*~ $(INCPATH)/*~

count:
	printf "%d\t lines of sources\n %d\t lines of headers\n" `cat $(SRCPATH)/*.c | wc -l` `cat $(DEPS) | wc -l`

.PHONY: clean count
