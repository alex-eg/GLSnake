#ifndef _S_GLOB
#define _S_GLOB

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <SDL/SDL_mixer.h>

#define CUBESIZE 100
#define CELLSIZE 106
#define MATRIXSIZE 5

typedef struct {
    int Running;

    struct vtable_State *State;
    SDL_Surface *SDisplay;
    struct SInGame *InGame;
    struct SPaused *Paused;
} SApp;


/*-----------------------------------------------*/
struct vtable_State{
    void (* Init)(SApp *);
    void (* Loop)(SApp *);
    void (* Event)(SApp *, SDL_Event *);
    void (* Render)(SApp *);
    void (* Cleanup)(SApp *);
};
typedef struct vtable_State vtable_State;
#endif
