CC ?= clang
ADD_CFLAGS ?=
ADD_LFLAGS ?=

SDL2_CFLAGS ?= $(shell pkg-config --cflags sdl2 SDL2_mixer SDL2_ttf)
SDL2_LIBS ?= $(shell pkg-config --libs sdl2 SDL2_mixer SDL2_ttf)

PLATFORM := $(shell uname -s)
ifeq ($(PLATFORM),Darwin)
  GL_LIBS = -framework OpenGL
else
  GL_LIBS = -lGL
endif

CFLAGS = -g -std=c99 -Wall -I$(INCPATH) -DRESOURCE_DIR=\"$(RESPATH)\" \
	$(SDL2_CFLAGS) $(ADD_CFLAGS)
LIBS = $(SDL2_LIBS) $(GL_LIBS) -lm $(ADD_LFLAGS)

OBJPATH = ./obj
BINPATH = ./bin
SRCPATH = ./src
INCPATH = ./include
RESPATH = ./resources

MODULES = main ingame paused gui targa mainmenu ttfonts gameover highscores

DEPS = $(INCPATH)/*.h Makefile
OBJ = $(MODULES:%=$(OBJPATH)/%.o)

all: $(BINPATH)/snake
	cp $< ./

$(OBJPATH)/%.o : $(SRCPATH)/%.c $(DEPS) | $(OBJPATH)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BINPATH)/snake: $(OBJ) | $(BINPATH)
	$(CC) $^ -o $@ $(LIBS)

$(OBJPATH):
	mkdir -p $(OBJPATH)

$(BINPATH):
	mkdir -p $(BINPATH)

clean:
	rm -f *~ $(OBJPATH)/*.o $(BINPATH)/* $(SRCPATH)/*~ $(INCPATH)/*~

count:
	printf "%d\t lines of sources\n %d\t lines of headers\n" `cat $(SRCPATH)/*.c | wc -l` `cat $(INCPATH)/*.h | wc -l`

.PHONY: all clean count
