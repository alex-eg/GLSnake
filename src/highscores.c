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

void SHighScores_Delete(SApp *App)
{
    free(App->HighScores);
    App->HighScores = NULL;
}

void SHighScores_Save(SApp *App, const char *filename)
{
    SHighScores *self = App->HighScores;
    FILE *f = fopen(filename, "wb+");
    fwrite(&self->table, sizeof(HighScoreTable), 1, f);
    fclose(f);
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
