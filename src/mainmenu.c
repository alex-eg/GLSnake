#include "mainmenu.h"

void SMainMenu_Render(SApp *App)
{
    SMainMenu *self = App->MainMenu;

    SLabel_Render(self->MainFrame);
    /* SLabel_Render(self->Logo);
   
    SButton_Render(self->Start);
    SButton_Render(self->HighScores);
    SButton_Render(self->Exit);*/
}

void SMainMenu_Init(SApp *App)
{
    SMainMenu *self = App->MainMenu;

    SMainMenu_InitGraphics();
    SMainMenu_InitGUI(App);
    SMainMenu_InitSound(App);
}

void SMainMenu_InitGraphics(void)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
  
    glShadeModel(GL_SMOOTH);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glMatrixMode(GL_PROJECTION);
    glOrtho(0, CELLSIZE * MATRIXSIZE, 0, CELLSIZE * MATRIXSIZE, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void SMainMenu_InitGUI(SApp *App)
{
    SMainMenu *self = App->MainMenu;
    SLabel_Create(self->MainFrame, 0, 0, WIDTH, HEIGHT);
    SLabel_SetTexture(self->MainFrame, "./background.tga");
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
    App->State->Init = &SMainMenu_Init;
    App->State->Loop = &SMainMenu_Loop;
    App->State->Event = &SMainMenu_ProcessEvent;
    App->State->Render = &SMainMenu_Render;
    App->State->Cleanup = &SMainMenu_Delete;
}
