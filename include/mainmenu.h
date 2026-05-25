/* This file is part of GLSnake.

GLSnake is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation, either version 3 of the License, or (at your
option) any later version.

GLSnake is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with GLSnake. If not, see <https://www.gnu.org/licenses/>. */

#ifndef _S_MAINMENU
#define _S_MAINMENU

#include "globals.h"
#include "gui.h"
#include "ingame.h"
#include "highscores.h"

struct SMainMenu {
    SApp *App;
    SButton *selection;

    SLabel *MainFrame;

    SButton *Start;
    SButton *HighScores;
    SButton *Exit;

    SLabel *Logo;
    int ifhighscores;
};
typedef struct SMainMenu SMainMenu;

/*--- INITIALIZATION ---*/
/* public         */ void SMainMenu_Init(SApp *);
/* static private */ void SMainMenu_InitGraphics(void);
/* static private */ void SMainMenu_InitGUI(SApp *);

/*--- LOGICS ---*/
/* public         */ void SMainMenu_Loop(SApp *);

/*--- EVENT PROCESSING --- */
/* private        */ void SMainMenu_OnKeyDown(SApp *, SDL_KeyCode, SDL_Keymod);
/* public         */ void SMainMenu_ProcessEvent(SApp *, SDL_Event *);

/*--- GRAPHICS ---*/
/* public         */ void SMainMenu_Render(SApp *);

/*--- OpenGL Drawing ---*/
/*--- Callbacks ---*/
void SMainMenu_StartGame(SApp *App);
void SMainMenu_ExitApp(SApp *App);
void SMainMenu_ShowHighScores(SApp *App);

/*--- Sound and music ---*/
/* private         */ void SMainMenu_InitSound(SApp *);
/* static          */ void SMainMenu_PlaySound(Sound *);
/* public          */ void SMainMenu_Cleanup(SApp *);

/* constructor     */ void SMainMenu_Create(SApp *);
/* destructor      */ void SMainMenu_Delete(SApp *);

/* switcher        */ void SMainMenu_Switch(SApp *);

#endif /* ifndef _S_MAINMENU */
