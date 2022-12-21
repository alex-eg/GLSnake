#ifndef _S_GLOB
#define _S_GLOB

#include <SDL.h>
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include <SDL_mixer.h>

#define CUBESIZE 30
#define CELLSIZE 36
#define MATRIXSIZE 20
#define WIDTH 600
#define HEIGHT 600

#ifndef RESOURCE_DIR
#define RESOURCE_DIR "./"
#endif

struct SApp {
    int Running;

    struct StateMethods {
	void (* Init)(struct SApp *);
	void (* Loop)(struct SApp *);
	void (* Event)(struct SApp *, SDL_Event *);
	void (* Render)(struct SApp *);
	void (* Cleanup)(struct SApp *);
    } State;
    SDL_Window *SWindow;
    SDL_Renderer *SRenderer;

    struct SInGame *InGame;
    struct SPaused *Paused;
    struct SHighScores *HighScores;
    struct SMainMenu *MainMenu;
    struct SGameOver *GameOver;

    struct SFont *Font;
};
typedef struct SApp SApp;

/*-----------------------------------------------*/
typedef struct {
    Mix_Chunk *Snd;
    int Chnl;
} Sound;

#endif
