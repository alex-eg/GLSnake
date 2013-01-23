#include "mainmenu.h"

void SMainMenu_Render(SApp *App)
{
    SMainMenu *self = App->MainMenu;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    SButton_Render(self->Start);
    SButton_Render(self->Exit);
    SButton_Render(self->HighScores);

    SLabel_Render(self->Logo);
    SLabel_Render(self->MainFrame);
         
    SDL_GL_SwapBuffers();
}

void SMainMenu_Init(SApp *App)
{
    SMainMenu_InitGraphics();
    SMainMenu_InitSound(App);
    SMainMenu_InitGUI(App);
}

void SMainMenu_InitGraphics(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_PROJECTION);
    glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void SMainMenu_InitGUI(SApp *App)
{
    #ifndef RESOURCE_DIR 
    #define RESOURCE_DIR "./"
    #endif

    SMainMenu *self = App->MainMenu;

    self->MainFrame = SLabel_Create();
    SLabel_Set(self->MainFrame, 0, 0, WIDTH, HEIGHT);
    SLabel_SetTexture(self->MainFrame, RESOURCE_DIR "/textures/background.tga");

    self->Logo = SLabel_Create();
    SLabel_Set(self->Logo, (WIDTH - 400) / 2 - 10, 100, 400, 380);
    SLabel_SetTexture(self->Logo, RESOURCE_DIR "/textures/logo.tga");

    self->Start = SButton_Create();
    SButton_Set(self->Start, (WIDTH - 140) / 2, 380, 140, 30);
    SButton_SetTexture(self->Start, RESOURCE_DIR "/textures/start.tga");
    SButton_Swap(self->Start);

    self->HighScores = SButton_Create();
    SButton_Set(self->HighScores, (WIDTH - 140) / 2, 430, 140, 30);
    SButton_SetTexture(self->HighScores, RESOURCE_DIR "/textures/scores.tga");

    self->Exit = SButton_Create();
    SButton_Set(self->Exit, (WIDTH - 140) / 2, 480, 140, 30);
    SButton_SetTexture(self->Exit, RESOURCE_DIR "/textures/exit.tga");

    SButton_Link(self->Start, self->HighScores);
    SButton_Link(self->HighScores, self->Exit);
    SButton_Link(self->Exit, self->Start);

    self->selection = self->Start;
}

void SMainMenu_InitSound(SApp *App)
{

}

void SMainMenu_Loop(SApp *App)
{
    /* stub! */
}

void SMainMenu_ProcessEvent(SApp *App, SDL_Event *Event)
{
    switch (Event->type) {
    case SDL_KEYDOWN : {
        SMainMenu_OnKeyDown(App, Event->key.keysym.sym, Event->key.keysym.mod, Event->key.keysym.unicode);
        break;
    }
    case SDL_QUIT : {
        App->Running = 0;
        break;
    }
    default: break;
    }
}

void SMainMenu_OnKeyDown(SApp *App, SDLKey sym, SDLMod mod, Uint16 unicode)
{
    SMainMenu *self = App->MainMenu;
    switch(sym) {
    case SDLK_UP: {
	SButton_Swap(self->selection);
	self->selection = self->selection->prev;
	SButton_Swap(self->selection);
	break;
    }
    case SDLK_DOWN: {
	SButton_Swap(self->selection);
	self->selection = self->selection->next;
	SButton_Swap(self->selection);
	break;
    }
    default: break;
    }
}

void SMainMenu_Delete(SApp *App)
{
    SMainMenu *self = App->MainMenu;
    SLabel_Delete(self->MainFrame);
    /*
    SLabel_Delete(self->Logo);
    ...
     */
}

void SMainMenu_Create(SApp *App)
{
    SMainMenu *self;
    App->MainMenu = self = (SMainMenu *) malloc(sizeof(SMainMenu));
    self->App = App;
}

void SMainMenu_Switch(SApp *App)
{
    App->State.Init = &SMainMenu_Init;
    App->State.Loop = &SMainMenu_Loop;
    App->State.Event = &SMainMenu_ProcessEvent;
    App->State.Render = &SMainMenu_Render;
    App->State.Cleanup = &SMainMenu_Delete;
}
