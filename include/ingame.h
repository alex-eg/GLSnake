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

#ifndef _S_INGAME
#define _S_INGAME

#include "globals.h"
#include "targa.h"

/*-----------------------------------------------*/
struct SPoint {
    int x, y;
    struct SPoint *next;
};
typedef struct SPoint SPoint;

/*-----------------------------------------------*/
struct SInGame {

    SApp *App;

    Mix_Music *Music;
    Sound Nyam;
    SPoint Food;
    SPoint *Head;
    int KeyPressed;
    int Timer;
    int dx, dy;
    int Speed;
    STGAFile textureFile;
    GLuint texture;

    unsigned char Field [MATRIXSIZE * MATRIXSIZE];

    int Score;
};
typedef struct SInGame SInGame;


/*--- INITIALIZATION ---*/
/* public         */ void SInGame_Init(SApp *);
/* static private */ void SInGame_InitGraphics(void);

/*--- LOGICS ---*/
/* public         */ void SInGame_Loop(SApp *);

/*--- EVENT PROCESSING --- */
/* private        */ void SInGame_OnKeyDown(SApp *, SDL_Keycode);
/* public         */ void SInGame_ProcessEvent(SApp *, SDL_Event *);
/* private        */ void SInGame_ProcessNewState(SApp *);

/*--- GRAPHICS ---*/
/* public         */ void SInGame_Render(SApp *);

/*--- OpenGL Drawing ---*/
/* static         */ void SInGame_Cube(SApp *, int, int, int);
/* static         */ void SInGame_Grid(void);

/*--- Sound and music ---*/
/* private         */ void SInGame_InitSound(SApp *);
/* static          */ void SInGame_PlaySound(Sound *);

/* deinitializator */ void SInGame_Clear(SApp *);

/* constructor     */ void SInGame_Create(SApp *);
/* destructor      */ void SInGame_Delete(SApp *);

/* switcher        */ void SInGame_Switch(SApp *);
#endif
