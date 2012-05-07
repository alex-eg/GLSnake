#include "Paused.h"
#include "InGame.h"

void SPaused_Init(SApp *App)
{
    App->Paused->Position = 0;
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
    App->State->Init = &SPaused_Init;
    App->State->Loop = &SPaused_Loop;
    App->State->Event = &SPaused_ProcessEvent;
    App->State->Render = &SPaused_Render;
    App->State->Cleanup = &SPaused_Delete;
}
