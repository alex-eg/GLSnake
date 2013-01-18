#include "mainmenu.h"

void SMainMenu_Render(SApp *App)
{
    SMainMenu *self = App->SMainMenu;

    SGui_RenderLabel(self->MainFrame);
    SGui_RenderLabel(self->Logo);
   
    SGui_RenderButton(self->Start);
    SGui_RenderButton(self->HighScores);
    SGui_RenderButton(self->Exit);
}

void SMainMenu_Init(SApp *App)
{
    SMainMenu *self = App->SMainMenu;

    SMainMenu_InitGraphics(App);
    SMainMenu_InitSound(App);
}

void SMainMenu_InitGraphics(SApp *App)
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
  
    glShadeModel(GL_SMOOTH);

    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glOrtho(0, CELLSIZE * MATRIXSIZE, 0, CELLSIZE * MATRIXSIZE, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
};
