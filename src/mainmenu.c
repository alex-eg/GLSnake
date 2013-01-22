#include "mainmenu.h"

void SMainMenu_Render(SApp *App)
{
    SMainMenu *self = App->MainMenu;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    SLabel_Render(self->MainFrame);
    /* SLabel_Render(self->Logo);
   
    SButton_Render(self->Start);
    SButton_Render(self->HighScores);
    SButton_Render(self->Exit);*/
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

    glMatrixMode(GL_PROJECTION);
    glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);
    //glFrustum(-305, 305, 305, -305, 655, 805);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //    glTranslatef(0, 0, -20.0f);
}

void SMainMenu_InitGUI(SApp *App)
{
    SMainMenu *self = App->MainMenu;
    self->MainFrame = SLabel_Create();
    SLabel_Set(self->MainFrame, 0, 0, WIDTH, HEIGHT);
    #ifndef RESOURCE_DIR 
    #define RESOURCE_DIR "./"
    #endif
    SLabel_SetTexture(self->MainFrame, RESOURCE_DIR "/textures/background.tga");
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
    App->State.Init = &SMainMenu_Init;
    App->State.Loop = &SMainMenu_Loop;
    App->State.Event = &SMainMenu_ProcessEvent;
    App->State.Render = &SMainMenu_Render;
    App->State.Cleanup = &SMainMenu_Delete;
}
