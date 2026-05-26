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

void SHighScores_Create(SApp *App)
{
    SHighScores *self = malloc(sizeof(SHighScores));
    self->App = App;
    App->HighScores = self;
}

void SHighScores_Read(SApp *App, const char *filename)
{
    SHighScores *self = App->HighScores;
    FILE *f = fopen(filename, "rb");
    if (f) {
	/* File exists! */
	fread (&self->table, sizeof(HighScoreTable), 1, f);
	fclose(f);
    } else {
	/* File doesn't exist! */
	self->table.first = self->table.second = self->table.third = 0;
	strcpy(self->table.nameFirst, "<void>");
	strcpy(self->table.nameSecond, "<void>");
	strcpy(self->table.nameThird, "<void>");
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
