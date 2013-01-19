#ifndef _S_MAINMENU
#define _S_MAINMENU

#include "globals.h"
#include "gui.h"

struct SMainMenu {
    SApp *App;

    SLabel *MainFrame;

    SButton *Start;
    SButton *HighScores;
    SButton *Exit;

    SLabel *Logo;
};
typedef struct SMainMenu SMainMenu;

/*--- INITIALIZATION ---*/
/* public         */ void SMainMenu_Init(SApp *);
/* static private */ void SMainMenu_InitGraphics(void);
/* static private */ void SMainMenu_InitGUI(SApp *);

/*--- LOGICS ---*/
/* public         */ void SMainMenu_Loop(SApp *);

/*--- EVENT PROCESSING --- */
/* private        */ void SMainMenu_OnKeyDown(SApp *, SDLKey, SDLMod, Uint16);
/* public         */ void SMainMenu_ProcessEvent(SApp *, SDL_Event *);

/*--- GRAPHICS ---*/
/* public         */ void SMainMenu_Render(SApp *);

/*--- OpenGL Drawing ---*/

/*--- Sound and music ---*/
/* private         */ void SMainMenu_InitSound(SApp *);
/* static          */ void SMainMenu_PlaySound(Sound *);
/* public          */ void SMainMenu_Cleanup(SApp *);

/* constructor     */ void SMainMenu_Create(SApp *);
/* destructor      */ void SMainMenu_Delete(SApp *);

/* switcher        */ void SMainMenu_Switch(SApp *);

#endif /* ifndef _S_MAINMENU */
