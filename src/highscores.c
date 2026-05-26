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

#include "highscores.h"

#include <SDL_filesystem.h>
#include <stdlib.h>
#include <string.h>

/*
NOTE: That parts of a pref path are important and must be consistent
      across the codebase. If you'll need to store something else -
      move those defines to globals.h for further reusage.
*/
#define SCORES_ORG "glsnake"
#define SCORES_APP "GLSnake"
#define SCORES_FILE "scores.dat"

static char *get_scores_path(void)
{
    char *base = SDL_GetPrefPath(SCORES_ORG, SCORES_APP);
    if (base == NULL) {
        return NULL;
    }

    size_t len = strlen(base) + strlen(SCORES_FILE) + 1;
    char *path = malloc(len);
    if (path != NULL) {
        snprintf(path, len, "%s%s", base, SCORES_FILE);
    }
    SDL_free(base);
    return path;
}

static void SHighScores_Init(SHighScores *self)
{
    self->table.first = 7;
    strcpy(self->table.nameFirst, "ktt9");

    self->table.second = 3;
    strcpy(self->table.nameSecond, "docker");

    self->table.third = 0;
    strcpy(self->table.nameThird, "<void>");
}

void SHighScores_Create(SApp *App)
{
    SHighScores *self = malloc(sizeof(SHighScores));
    self->App = App;
    self->scores_path = get_scores_path();
    App->HighScores = self;

    if (self->scores_path == NULL) {
        fprintf(stderr, "Failed to construct path for saving high scores");
        SHighScores_Init(self);
        return;
    }

    FILE *f = fopen(self->scores_path, "rb");
    if (f) {
        /* File exists! */
        fread(&self->table, sizeof(HighScoreTable), 1, f);
        fclose(f);
    } else {
        /* File doesn't exist! */
        SHighScores_Init(self);
    }
}

void SHighScores_Read(SApp *App)
{
    SHighScores *self = App->HighScores;
    FILE *f = fopen(self->scores_path, "rb");
    if (f) {
        fread(&self->table, sizeof(HighScoreTable), 1, f);
        fclose(f);
    } else {
        SHighScores_Init(self);
    }
}


void SHighScores_Save(SApp *App)
{
    SHighScores *self = App->HighScores;

    FILE *f = fopen(self->scores_path, "wb");
    if (f == NULL) {
        fprintf(stderr, "Failed to save high scores to %s\n", self->scores_path);
        return;
    }
    fwrite(&self->table, sizeof(HighScoreTable), 1, f);
    fclose(f);
}

void SHighScores_Delete(SApp *App)
{
    SHighScores *self = App->HighScores;

    if (self->scores_path != NULL) {
        SHighScores_Save(App);
        free(self->scores_path);
    }

    free(self);
    App->HighScores = NULL;
}

void SHighScores_Render(SApp *App)
{
    SHighScores *self = App->HighScores;

    SFont_glEnable2D();
    SDL_Rect position;
    SDL_Color color = { 255, 255, 255 };
    position.x = WIDTH / 2 - 136;
    position.y = 400;
    SFont_RenderText(App->Font, "High Scores", &position, &color, size48);
    char s[64];

    sprintf(s, "%s", self->table.nameFirst);
    position.y -= 64;
    SFont_RenderText(App->Font, s, &position, &color, size24);
    sprintf(s, "%d", self->table.first);
    position.x += 256;
    SFont_RenderText(App->Font, s, &position, &color, size24);

    sprintf(s, "%s", self->table.nameSecond);
    position.x -= 256;
    position.y -= 36;
    SFont_RenderText(App->Font, s, &position, &color, size24);
    sprintf(s, "%d", self->table.second);
    position.x += 256;
    SFont_RenderText(App->Font, s, &position, &color, size24);

    sprintf(s, "%s", self->table.nameThird);
    position.x -= 256;
    position.y -= 36;
    SFont_RenderText(App->Font, s, &position, &color, size24);
    sprintf(s, "%d", self->table.third);
    position.x += 256;
    SFont_RenderText(App->Font, s, &position, &color, size24);

    SFont_glDisable2D();
}
