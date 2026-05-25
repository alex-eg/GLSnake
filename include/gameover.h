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
/* private        */ void SGameOver_OnKeyDown(SApp *, SDL_Keycode);
/* public         */ void SGameOver_ProcessEvent(SApp *, SDL_Event *);
/* private        */ void SGameOver_ProcessNewState(SApp *);

/*--- GRAPHICS ---*/
/* public         */ void SGameOver_Render(SApp *);

/* constructor    */ void SGameOver_Create(SApp *);
/* destructor     */ void SGameOver_Delete(SApp *);
/* switcher       */ void SGameOver_Switch(SApp *);

#endif /* ifndef _S_GAMEOVER */
