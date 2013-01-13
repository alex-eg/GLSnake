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

    SPaused_InitTTF(App->Paused);
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
    SPaused *self = App->Paused;
    SPaused_glEnable2D();

    SDL_Rect position;
    SDL_Color color = { 255, 255, 255 };

    position.x = CELLSIZE*MATRIXSIZE/2-100;
    position.y = CELLSIZE*MATRIXSIZE/2;
    if (App->Paused->Position == 0)  {
	SPaused_RenderText(self, "--> Продолжить", &position, &color, size24);
	position.y -= 30;
	SPaused_RenderText(self, "    Выход", &position, &color, size24);
    } else {
	SPaused_RenderText(self, "    Продолжить", &position, &color, size24);
	position.y -= 30;
	SPaused_RenderText(self, "--> Выход", &position, &color, size24);
    }
    
    SPaused_glDisable2D();
    SDL_GL_SwapBuffers();
}

void SPaused_Delete(SApp *App)
{
    SPaused *self = App->Paused;
    TTF_CloseFont(self->font16);
    TTF_CloseFont(self->font24);
    TTF_Quit();
    free(self);
    App->Paused = NULL;
    
}

void SPaused_Create(SApp *App)
{
    SPaused *self;
    App->Paused = self = (SPaused *) malloc(sizeof(SPaused));
    self->App = App;
    self->font16 = self->font24 = NULL;
}

void SPaused_Switch(SApp *App)
{
    App->State->Init = &SPaused_Init;
    App->State->Loop = &SPaused_Loop;
    App->State->Event = &SPaused_ProcessEvent;
    App->State->Render = &SPaused_Render;
    App->State->Cleanup = &SPaused_Delete;
}

/*--- Fonts! ---*/
void SPaused_InitTTF(SPaused *self)
{
    TTF_Init();
    self->font24 = TTF_OpenFont("DejaVuSansMono.ttf", 24);
    if (!self->font24) fprintf(stderr, "(EE) Loading 24-font failed!\n");
    self->font16 = TTF_OpenFont("DejaVuSansMono.ttf", 16);
    if (!self->font16) fprintf(stderr, "(EE) Loading 16-font failed!\n");
}

void SPaused_glEnable2D()
{
    int vPort[4];
  
    glGetIntegerv(GL_VIEWPORT, vPort);
  
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
  
    glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}

void SPaused_glDisable2D()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();   
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void SPaused_RenderText(SPaused *self, const char *text, SDL_Rect *location, SDL_Color *color, enum FontSize s)
{
    SDL_Surface *initial;
    SDL_Surface *intermediary;
    int w,h;
    GLuint texture;

    if (s == size24)
	initial = TTF_RenderUTF8_Blended(self->font24, text, *color);
    else
	initial = TTF_RenderUTF8_Blended(self->font16, text, *color);

    w = SPaused_nextpoweroftwo(initial->w);
    h = SPaused_nextpoweroftwo(initial->h);
	
    intermediary = SDL_CreateRGBSurface(0, w, h, 32, 
					0x00ff0000, 
					0x0000ff00, 
					0x000000ff, 
					0xff000000);
    
    SDL_BlitSurface(initial, 0, intermediary, 0);
	
    /* Tell GL about our new texture */
    
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_BGRA, 
		 GL_UNSIGNED_BYTE, intermediary->pixels );
	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
    
    /* Prepare to render our texture */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glColor3f(1.0f, 1.0f, 1.0f);
	
    /* Draw a texture quad at location */
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 1.0f); 
    glVertex2f(location->x    , location->y);
    glTexCoord2f(1.0f, 1.0f); 
    glVertex2f(location->x + w, location->y);
    glTexCoord2f(1.0f, 0.0f); 
    glVertex2f(location->x + w, location->y + h);
    glTexCoord2f(0.0f, 0.0f); 
    glVertex2f(location->x    , location->y + h);
    glEnd();
	
    /* Bad things happen if we delete the texture before it finishes */
    glFinish();
	
    /* return the deltas in the unused w,h part of the rect */
    location->w = initial->w;
    location->h = initial->h;

    /* Clean up */
    SDL_FreeSurface(initial);
    SDL_FreeSurface(intermediary);
    glDeleteTextures(1, &texture);
}

int SPaused_nextpoweroftwo(int x)
{
    double logbase2 = log(x) / log(2);
    return round(pow(2,ceil(logbase2)));
}
