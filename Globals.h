#include <SDL/SDL.h>
#include <GL/gl.h>
#include <SDL/SDL_mixer.h>

#define CUBESIZE 30
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
    Mix_Chunk *Snd;
    int Chnl;
} Sound;

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
    //    Sound MainTheme;
    Mix_Music *Music;
    Sound Nyam;
} SApp;

/*--- INITIALIZATION ---*/
void SInitGraphics(void);
void SInitApp(SApp *);
int SInitSdl(SApp *);

/*--- EVENT PROCESSING --- */
void SOnKeyDown(SApp *, SDLKey, SDLMod, Uint16);
void SProcessEvent(SApp *, SDL_Event *);

/*--- GRAPHICS ---*/
void SRender(SApp *);

/*--- OpenGL Drawing ---*/
void SCube(int, int, int);
void SGrid(void);

/*--- Sound and music! ---*/
void SInitSound(SApp *);
void SPlaySound(Sound *);

