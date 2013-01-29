#include "paused.h"
#include "ingame.h"

void SPaused_Init(SApp *App)
{
    App->Paused->Position = 0;
    /* App->Paused->snapshot = SDL_CreateRGBSurface(0,  */
    /* 						 CELLSIZE*MATRIXSIZE,  */
    /* 						 CELLSIZE*MATRIXSIZE,  */
    /* 						 32,  */
    /* 						 0x00ff0000,  */
    /* 						 0x0000ff00,  */
    /* 						 0x000000ff,  */
    /* 						 0xff000000); */
    
    /* SDL_BlitSurface(App->SDisplay, 0, App->Paused->snapshot, 0); */

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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    SFont_glEnable2D();

    SDL_Rect position;
    SDL_Color color = { 255, 255, 255 };

    position.x = WIDTH / 2 - 100;
    position.y = HEIGHT / 2;

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
    free(self);
    App->Paused = NULL;
    
}

void SPaused_Create(SApp *App)
{
    SPaused *self;
    App->Paused = self = (SPaused *) malloc(sizeof(SPaused));
    self->App = App;
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

