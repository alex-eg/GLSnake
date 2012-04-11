#include "Globals.h"

struct SPoint{
    int x,y;
    struct SPoint *next;
};
typedef struct SPoint SPoint;

struct {
    State_Class *Class;

    Mix_Music *Music;
    Sound Nyam;
    SPoint Food;
    SPoint *Head;
    int KeyPressed;
    int Timer;
    int dx, dy;
    int Speed;
    SApp *App;
} SInGame;
typedef struct SInGame SInGame;

/*--- INITIALIZATION ---*/
/* public         */ void SInGame_Init(SInGame *);
/* static private */ void SInGame_InitGraphics(void);

/*--- LOGICS ---*/
/* public         */ void SInGame_Loop(SInGame *);

/*--- EVENT PROCESSING --- */
/* private        */ void SInGame_OnKeyDown(SInGame *, SDLKey, SDLMod, Uint16);
/* public         */ void SInGame_ProcessEvent(SInGame *, SDL_Event *);

/*--- GRAPHICS ---*/
/*public          */ void SInGame_Render(SInGame *);

/*--- OpenGL Drawing ---*/
/* static         */ void SInGame_Cube(int, int, int);
/* static         */ void SInGame_Grid(void);

/*--- Sound and music! ---*/
/* private         */ void SInGame_InitSound(SInGame *);
/* static          */ void SInGame_PlaySound(Sound *);
/* public          */ void SInGame_Cleanup(SInGame *);

/* constructor     */ SInGame *newSInGame(SApp *);
