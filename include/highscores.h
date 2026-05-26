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

#ifndef _S_HIGHSCORES
#define _S_HIGHSCORES

#include "globals.h"
#include "ttfonts.h"

#include <stdio.h>

struct HighScoreTable {
    int first, second, third;
    char nameFirst[8], nameSecond[8], nameThird[8];
};
typedef struct HighScoreTable HighScoreTable;

struct SHighScores {
    SApp *App;
    struct HighScoreTable table;
    char *scores_path;
};
typedef struct SHighScores SHighScores;

void SHighScores_Create(SApp *);
void SHighScores_Delete(SApp *);
void SHighScores_Render(SApp *);

#endif /* ifndef _S_HIGHSCORES */
