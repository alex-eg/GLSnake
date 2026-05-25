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

#ifndef _S_PAUSED
#define _S_PAUSED

#include "SDL_keycode.h"
#include "globals.h"
#include "ttfonts.h"
#include "gui.h"
#include "mainmenu.h"

struct SPaused {
    SApp *App;
    int Position;
    GLuint texture;
};
typedef struct SPaused SPaused;


/*--- INITIALIZATION ---*/
/* public         */ void SPaused_Init(SApp *);
/* static private */ void SPaused_InitGraphics(void);

/*--- LOGICS ---*/
/* public         */ void SPaused_Loop(SApp *);

/*--- EVENT PROCESSING --- */
/* private        */ void SPaused_OnKeyDown(SApp *, SDL_Keycode);
/* public         */ void SPaused_ProcessEvent(SApp *, SDL_Event *);
/* private        */ void SPaused_ProcessNewState(SApp *);

/*--- GRAPHICS ---*/
/* public         */ void SPaused_Render(SApp *);

/*--- OpenGL Drawing ---*/
/* static         */ void SPaused_Cube(int, int, int);
/* static         */ void SPaused_Grid(void);

/*--- Sound and music! ---*/
/* private         */ void SPaused_InitSound(SApp *);
/* public          */ void SPaused_Cleanup(SApp *);

/* constructor     */ void SPaused_Create(SApp *);
/* destructor      */ void SPaused_Delete(SApp *);

/* switcher        */ void SPaused_Switch(SApp *);

#endif
