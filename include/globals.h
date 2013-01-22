#ifndef _S_GLOB
#define _S_GLOB

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <SDL/SDL_mixer.h>

#define CUBESIZE 30
#define CELLSIZE 36
#define MATRIXSIZE 20
#define WIDTH 600
#define HEIGHT 600

struct SApp {
    int Running;

    struct StateMethods {
	void (* Init)(struct SApp *);
	void (* Loop)(struct SApp *);
	void (* Event)(struct SApp *, SDL_Event *);
	void (* Render)(struct SApp *);
	void (* Cleanup)(struct SApp *);
    } State;
    SDL_Surface *SDisplay;
    struct SInGame *InGame;
    struct SPaused *Paused;
    struct SHighScore *HighScore;
    struct SMainMenu *MainMenu;
};
typedef struct SApp SApp;

/*-----------------------------------------------*/
typedef struct {
    Mix_Chunk *Snd;
    int Chnl;
} Sound;

#endif
