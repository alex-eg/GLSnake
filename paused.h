#ifndef _S_PAUSED
#define _S_PAUSED

#include "Globals.h"
#include <SDL/SDL_ttf.h>
#include <math.h>

enum FontSize {size24, size16};

struct SPaused {
    SApp *App;
    int Position;
    TTF_Font *font24;
    TTF_Font *font16;
    SDL_Surface *snapshot;
};
typedef struct SPaused SPaused;


/*--- INITIALIZATION ---*/
/* public         */ void SPaused_Init(SApp *);
/* static private */ void SPaused_InitGraphics(void);

/*--- LOGICS ---*/
/* public         */ void SPaused_Loop(SApp *);

/*--- EVENT PROCESSING --- */
/* private        */ void SPaused_OnKeyDown(SApp *, SDLKey, SDLMod, Uint16);
/* public         */ void SPaused_ProcessEvent(SApp *, SDL_Event *);
/* private        */ void SPaused_ProcessNewState(SApp *);

/*--- GRAPHICS ---*/
/* public         */ void SPaused_Render(SApp *);

/*--- OpenGL Drawing ---*/
/* static         */ void SPaused_Cube(int, int, int);
/* static         */ void SPaused_Grid(void);

/*--- Sound and music! ---*/
/* private         */ void SPaused_InitSound(SApp *);
/* static          */ /*void SPaused_PlaySound(Sound *);*/
/* public          */ void SPaused_Cleanup(SApp *);

/*--- Fonts! ---*/
void SPaused_InitTTF(SPaused *);
void SPaused_glEnable2D(void);
void SPaused_glDisable2D(void);
void SPaused_RenderText(SPaused *, const char *, SDL_Rect *, SDL_Color *, enum FontSize);
int SPaused_nextpoweroftwo(int);

/* constructor     */ void SPaused_Create(SApp *);
/* destructor      */ void SPaused_Delete(SApp *);

/* switcher        */ void SPaused_Switch(SApp *);

#endif
