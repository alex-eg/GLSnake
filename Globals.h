#include <SDL/SDL.h>
#include <GL/gl.h>
#include <SDL/SDL_mixer.h>

#define CUBESIZE 30
#define CELLSIZE 36
#define MATRIXSIZE 20

typedef struct {
    void (* Init)(void *);
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
    SDL_Surface *SDisplay;
    struct SInGame *State;
} SApp;

struct SPoint {
    int x,y;
    struct SPoint *next;
};
typedef struct SPoint SPoint;

struct SInGame {
    State_Class *Class;

    struct SInGame *self;
    Mix_Music *Music;
    Sound Nyam;
    SPoint Food;
    SPoint *Head;
    int KeyPressed;
    int Timer;
    int dx, dy;
    int Speed;
    SApp *App;
};
typedef struct SInGame SInGame;

/*--- State Setter  ---*/
void SSetState(SApp *, SInGame *);
