#include "gameover.h"

void SGameOver_Create(SApp *App)
{
    SGameOver *self = malloc(sizeof(SGameOver));
    App->GameOver = self;
    self->App = App;
    self->score = -1;
    self->highscored = 0;
    self->symbols = 0;
    strcpy(self->name, "_");
}

void SGameOver_Init(SApp *App)
{
    SGameOver *self = App->GameOver;
    glBindTexture(GL_TEXTURE_2D, self->texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, 1024, 1024, 0);
}

void SGameOver_SetScore(SApp *App, int score)
{
    SGameOver *self = App->GameOver;
    self->score = score;
    if (self->score >= App->HighScores->table.first ||
	self->score >= App->HighScores->table.second ||
	self->score >= App->HighScores->table.third)
	self->highscored = 1;
}

void SGameOver_Render(SApp *App)
{
    SGameOver *self = App->GameOver;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    SDL_Rect position;
    SDL_Color color = { 200, 0, 255 };
    position.x = WIDTH / 2 - 120;
    position.y = HEIGHT / 2 + 200;
    
    SFont_glEnable2D();

    glBindTexture(GL_TEXTURE_2D, self->texture);

    glEnable(GL_TEXTURE_2D);

    glColor3f(.5, .5, .5);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0, 0.0);
    glVertex2f(0, 0);

    glTexCoord2f(WIDTH / 1024.0f, 0.0);
    glVertex2f(WIDTH, 0);

    glTexCoord2f(WIDTH / 1024.0f , HEIGHT / 1024.0f);
    glVertex2f(WIDTH, HEIGHT);

    glTexCoord2f(0.0, HEIGHT / 1024.0f);
    glVertex2f(0, HEIGHT);

    glEnd();

    glDisable(GL_TEXTURE_2D);   
    
    SFont_RenderText(App->Font, "Game Over!", &position, &color, size48);

    SHighScores_Render(App);

    position.y -= 380;
    position.x -= 40;
    color.g = 255;
    color.b = 255;
    color.r = 255;
    char s[64];
    sprintf(s, "Your score: \%d", self->score);
    SFont_RenderText(App->Font, s, &position, &color, size48);

    if (self->highscored) {
	position.y -= 48;
	position.x -= 108;
	sprintf(s, "Input name: %s", self->name);
	SFont_RenderText(App->Font, s, &position, &color, size48);
    } else {
	position.y -= 36;
	position.x -= 60;
	SFont_RenderText(App->Font, "Press Enter to exit to Main Menu", &position, &color, size24);
    }
    SDL_GL_SwapBuffers();
}

void SGameOver_ProcessEvent(SApp *App, SDL_Event *event)
{
    switch (event->type) {
    case SDL_KEYDOWN : {
        SGameOver_OnKeyDown(App, event->key.keysym.sym);
        break;
    }
    case SDL_QUIT : {
        App->Running = 0;
        break;
    }
    default:
        break;
    }
}

void SGameOver_OnKeyDown(SApp *App, SDLKey sym)
{
    SGameOver *self = App->GameOver;
    if (self->highscored) {
	if (sym >= SDLK_a && sym <= SDLK_z) { /* it's character, appending to name */
	    /* a has number 97 */
	    int start = SDLK_a - 'a'; /* sdl - ascii relative offset */
	    char c = sym - start;
	    if (self->symbols < 7) {
		int symbols = self->symbols;
		self->name[symbols] = c;
		self->name[symbols + 1] = (symbols < 6) ? '_' : '\0';
		self->name[symbols + 2] = '\0';
		self->symbols ++;
	    }
	}
	switch (sym) {
	case SDLK_RETURN: {
	    self->name[self->symbols] = '\0';
	    HighScoreTable *table = &App->HighScores->table;
	    if (self->score >= table->first) {
		table->third = table->second;
		memcpy(table->nameThird, table->nameSecond, 8);
		table->second = table->first;
		memcpy(table->nameSecond, table->nameFirst, 8);
		
		table->first = self->score;
		memcpy(table->nameFirst, self->name, 8);
	    } else if (self->score >= table->second) {
		table->third = table->second;
		memcpy(table->nameThird, table->nameSecond, 8);

		table->second = self->score;
		memcpy(self->name, table->nameSecond, 8);
	    } else {
		table->third = self->score;
		memcpy(self->name, table->nameThird, 8);
	    }
	    /* save name to highscores */
	    self->highscored = 0;
	    self->name[0] = '\0';
	    self->symbols = 0;
	    self->score = 0;
	    break;
	}
	case SDLK_ESCAPE: { 
	    self->name[0] = '\0';
	    self->symbols = 0;
	    self->score = 0;
	    SMainMenu_Switch(App);
	    break;
	}
	case SDLK_BACKSPACE: {
	    self->symbols--;
	    self->name[self->symbols] = '_';
	    self->name[self->symbols + 1] = '\0';
	    break;
	}
	default: break;
	}
    } else {	
	switch (sym) {
	case SDLK_RETURN:
	case SDLK_ESCAPE: { 
	    SMainMenu_Switch(App);
	    break;
	}
	default: break;
	}
    }
}


void SGameOver_Loop(SApp *App)
{

}

void SGameOver_Delete(SApp *App)
{

}

void SGameOver_Switch(SApp *App)
{
    App->State.Init = &SGameOver_Init;
    App->State.Loop = &SGameOver_Loop;
    App->State.Event = &SGameOver_ProcessEvent;
    App->State.Render = &SGameOver_Render;
    App->State.Cleanup = &SGameOver_Delete;
}
