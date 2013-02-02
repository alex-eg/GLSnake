#include "gameover.h"

void SGameOver_Create(SApp *App)
{
    SGameOver *self = malloc(sizeof(SGameOver));
    App->GameOver = self;
    self->App = App;
    self->score = -1;
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
}

void SGameOver_Render(SApp *App)
{
    SGameOver *self = App->GameOver;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    SDL_Rect position;
    SDL_Color color = { 255, 127, 200 };
    position.x = WIDTH / 2 - 120;
    position.y = HEIGHT / 2 + 100;
    
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
    position.y -= 84;
    position.x -= 40;
    color.g = 255;
    color.b = 255;
    char s[64];
    sprintf(s, "Your score: \%d", self->score);
    SFont_RenderText(App->Font, s, &position, &color, size48);

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
    /*switch (sym) {
    case SDLK_ESCAPE: { //ESC
	break;
    }
    case SDLK_UP:  //UP Arrow
    case SDLK_DOWN: { //DOWN Arrow
	App->Paused->Position ^= 1; 
	break;
    }
    case SDLK_RETURN: { //ENTER
        if (App->Paused->Position == 0) {
	    SInGame_Switch(App);
        } else {
	    SMainMenu_Switch(App);
	    SMainMenu_InitGraphics();
	};
        break;
    }
    default: break;
    }*/
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
