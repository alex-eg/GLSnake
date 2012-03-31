#include <SDL/SDL.h>
#include <GL/gl.h>

#define CUBESIZE 15
#define CELLSIZE 36
#define MATRIXSIZE 20

struct SPoint{
    int x,y;
    struct SPoint *next;
};

typedef struct SPoint SPoint;

enum state {loading, menu, ingame, paused, highscores};
typedef enum state state;

typedef struct {
    int Running;
    SDL_Surface* SDisplay;
    int dx, dy;
    SPoint Food;
    SPoint *Head;
    int KeyPressed;
    state State;
    int Timer;
    int Speed;
} SApp;

/*--- EVENT PROCESSING --- */
void SOnKeyDown(SApp *, SDLKey, SDLMod, Uint16);
void SProcessEvent(SApp *, SDL_Event *);

/*--- GRAPHICS ---*/
void SRender(SApp *);

/*--- OpenGL Drawing ---*/
void SRect(int, int);
void SGrid(void);
