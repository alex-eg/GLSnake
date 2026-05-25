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

#ifndef _S_TTFONTS
#define _S_TTFONTS

#include "globals.h"
#include <SDL_ttf.h>
#include <math.h>

enum FontSize {size24, size16, size48};

struct SFont {
    TTF_Font *font24;
    TTF_Font *font16;
    TTF_Font *font48;
};
typedef struct SFont SFont;

/*--- Fonts! ---*/
void SFont_Create(SApp *);
void SFont_Delete(SApp *);

void SFont_InitTTF (SFont *, char *filename);
void SFont_glEnable2D (void);
void SFont_glDisable2D (void);
void SFont_RenderText (SFont *, const char *, SDL_Rect *, SDL_Color *, enum FontSize);
int SFont_nextpoweroftwo (int);

#endif /* ifndef _S_TTFONTS */
