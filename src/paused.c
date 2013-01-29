#include "paused.h"
#include "ingame.h"

void SPaused_Init(SApp *App)
{
    SPaused *self = App->Paused;
    self->Position = 0;
    glBindTexture(GL_TEXTURE_2D, self->texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, 1024, 1024, 0);
    //glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, 512, 512);
    if (glGetError() != GL_NO_ERROR) printf("Errno %d on %d\n", glGetError(), __LINE__);
}

void SPaused_Loop(SApp *App)
{
    /* Stub! D: 
     Virtual function mechanism in C++ makes more sense now */
}

void SPaused_ProcessEvent(SApp *App, SDL_Event *Event)
{
    switch (Event->type) {
    case SDL_KEYDOWN : {
        SPaused_OnKeyDown(App, Event->key.keysym.sym,Event->key.keysym.mod,Event->key.keysym.unicode);
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

void SPaused_OnKeyDown(SApp *App, SDLKey sym, SDLMod mod, Uint16 unicode)
{
    switch (sym) {
    case SDLK_ESCAPE: { //ESC
	break;
    }
    case SDLK_UP: { //UP Arrow
        if (App->Paused->Position != 0) {
	    --App->Paused->Position;
        };
        break;
    }
    case SDLK_DOWN: { //DOWN Arrow
        if (App->Paused->Position != 1) {
	    ++App->Paused->Position;
        };
        break;
    }
    case SDLK_RETURN: { //ENTER
        if (App->Paused->Position == 0) {
	    SInGame_Switch(App);
        } else {
	    App->Running = 0;
	};
        break;
    }
    default: break;
    }
}

void SPaused_Render(SApp *App)
{
    SPaused *self = App->Paused;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    SDL_Rect position;
    SDL_Color color = { 255, 255, 255 };

    position.x = WIDTH / 2 - 100;
    position.y = HEIGHT / 2;

    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    SFont_glEnable2D();

    glBindTexture(GL_TEXTURE_2D, self->texture);

    glEnable(GL_TEXTURE_2D);

    glColor3f(1.5, 1.5, 1.5);
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

    SFont_RenderText(App->Font, "Continue", &position, &color, size48);
    position.y -= 64;
    SFont_RenderText(App->Font, "Exit", &position, &color, size48);

    position.x = WIDTH / 2 - 130;
    if (App->Paused->Position == 0)  {
	position.y = HEIGHT / 2;
	SFont_RenderText(App->Font, "*", &position, &color, size48);
    } else {
	position.y = HEIGHT / 2 - 64;
	SFont_RenderText(App->Font, "*", &position, &color, size48);
    }

    SFont_glDisable2D();
    SDL_GL_SwapBuffers();
}

void SPaused_Delete(SApp *App)
{
    SPaused *self = App->Paused;
    glDeleteTextures(1, &self->texture);    
    free(self);
    App->Paused = NULL;
}

void SPaused_Create(SApp *App)
{
    SPaused *self;
    App->Paused = self = (SPaused *) malloc(sizeof(SPaused));
    self->App = App;
    glGenTextures(1, &self->texture);
}

void SPaused_Switch(SApp *App)
{
    App->State.Init = &SPaused_Init;
    App->State.Loop = &SPaused_Loop;
    App->State.Event = &SPaused_ProcessEvent;
    App->State.Render = &SPaused_Render;
    App->State.Cleanup = &SPaused_Delete;
}

/*--- Fonts! ---*/

