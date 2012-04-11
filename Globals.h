#include <SDL/SDL.h>
#include <GL/gl.h>
#include <SDL/SDL_mixer.h>

#define CUBESIZE 30
#define CELLSIZE 36
#define MATRIXSIZE 20

typedef struct {
    void (* Init)(void *, void *);
    void (* Loop)(void *);
    void (* Event)(void *, SDL_Event *);
    void (* Render)(void *);
    void (* Cleanup)(void *);
} State_Class;

typedef struct {
    Mix_Chunk *Snd;
    int Chnl;
} Sound;

typedef struct {
    int Running;
    SDL_Surface* SDisplay;
    void *State;
} SApp;

/*--- State Setter  ---*/
void SSetState(SApp *, void *);
