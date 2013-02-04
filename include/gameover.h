#ifndef _S_GAMEOVER
#define _S_GAMEOVER

#include "highscores.h"
#include "globals.h"
#include "ttfonts.h"
#include "mainmenu.h"

struct SGameOver {
    SApp *App;
    int score;
    GLuint texture;
    int highscored;
    char name[10];
    int symbols; /* Number of symbols in name */
};
typedef struct SGameOver SGameOver;

/*--- INITIALIZATION ---*/
/* public         */ void SGameOver_Init(SApp *);
/* public         */ void SGameOver_SetScore(SApp *, int);
/*--- LOGICS ---*/
/* public         */ void SGameOver_Loop(SApp *);

/*--- EVENT PROCESSING --- */
/* private        */ void SGameOver_OnKeyDown(SApp *, SDLKey);
/* public         */ void SGameOver_ProcessEvent(SApp *, SDL_Event *);
/* private        */ void SGameOver_ProcessNewState(SApp *);

/*--- GRAPHICS ---*/
/* public         */ void SGameOver_Render(SApp *);

/* constructor    */ void SGameOver_Create(SApp *);
/* destructor     */ void SGameOver_Delete(SApp *);
/* switcher       */ void SGameOver_Switch(SApp *);

#endif /* ifndef _S_GAMEOVER */
