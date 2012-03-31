#include "Events.h"

void SProcessEvent(SApp *App, SDL_Event *Event)
{
    switch (Event->type) {
    case SDL_KEYDOWN : {
        SOnKeyDown(App, Event->key.keysym.sym,Event->key.keysym.mod,Event->key.keysym.unicode);
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

void SOnKeyDown(SApp *App, SDLKey sym, SDLMod mod, Uint16 unicode)
{
    switch (sym) {
    case 282: { //F1
	App->dx=0;
	App->dy=0;
	break;
    }
    case 27: { //ESC
	if (App->State==ingame) App->State=paused;
	else App->State=ingame;
        break;
    }
    case 119: { //W
        if ((App->dy == 0) && !App->KeyPressed) {
            App->dy = -1;
            App->dx = 0;
	    App->KeyPressed = 1;
        } else break;
        break;
    }
    case 97: { //A
        if ((App->dx == 0) && !App->KeyPressed) {
            App->dy = 0;
            App->dx = -1;
	    App->KeyPressed = 1;
        } else break;
        break;
    }
    case 115: { //S
        if ((App->dy == 0) && !App->KeyPressed) {
            App->dy = 1;
            App->dx = 0;
	    App->KeyPressed = 1;
        } else break;
        break;
    }
    case 100: { //D
        if ((App->dx == 0) && !App->KeyPressed) {
            App->dy = 0;
            App->dx = 1;
	    App->KeyPressed = 1;
        } else break;
        break;
    }
    case 270: { //Num+
	App->Speed--;
	break;
    }
    case 269: { ///Num-
	App->Speed++;
	break;
    }
    default: break;
    }
}
