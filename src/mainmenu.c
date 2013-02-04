#include "mainmenu.h"

void SMainMenu_Render(SApp *App)
{
    SMainMenu *self = App->MainMenu;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    SFont_glEnable2D();
    SLabel_Render(self->MainFrame);
    if (self->ifhighscores) {
	SFont_glDisable2D();
	SHighScores_Render(App);
    } else {
	SLabel_Render(self->Logo);
         
	SButton_Render(self->Start);
	SButton_Render(self->Exit);
	SButton_Render(self->HighScores);
	SFont_glDisable2D();
    }
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
    glLoadIdentity();
    glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void SMainMenu_InitGUI(SApp *App)
{
    SMainMenu *self = App->MainMenu;

    self->MainFrame = SLabel_Create();
    SLabel_Set(self->MainFrame, 0, 0, WIDTH, HEIGHT);
    SLabel_SetTexture(self->MainFrame, RESOURCE_DIR "/textures/background.tga");

    self->Logo = SLabel_Create();
    SLabel_Set(self->Logo, WIDTH / 2 - 210, 120, 400, 380);
    SLabel_SetTexture(self->Logo, RESOURCE_DIR "/textures/logo.tga");

    self->Start = SButton_Create(App);
    SButton_Set(self->Start, WIDTH / 2 - 76, 180, 140, 30);
    SButton_SetText(self->Start, "Start");
    SButton_Swap(self->Start);
    SButton_SetCallback(self->Start, SMainMenu_StartGame);

    self->HighScores = SButton_Create(App);
    SButton_Set(self->HighScores, WIDTH / 2 - 140, 130, 140, 30);
    SButton_SetText(self->HighScores, "High Scores");
    SButton_SetCallback(self->HighScores, SMainMenu_ShowHighScores);
 
    self->Exit = SButton_Create(App);
    SButton_Set(self->Exit, WIDTH / 2 - 64, 80, 140, 30);
    SButton_SetText(self->Exit, "Exit");
    SButton_SetCallback(self->Exit, SMainMenu_ExitApp);

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
    if (self->ifhighscores) { 
	self->ifhighscores = 0; 
	return;
    }
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
    case SDLK_RETURN: {
	SButton_Call(self->selection, App);
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
    self->ifhighscores = 0;
}

void SMainMenu_Switch(SApp *App)
{
    App->State.Init = &SMainMenu_Init;
    App->State.Loop = &SMainMenu_Loop;
    App->State.Event = &SMainMenu_ProcessEvent;
    App->State.Render = &SMainMenu_Render;
    App->State.Cleanup = &SMainMenu_Delete;
}

/*--=== Callbacks ===--*/
void SMainMenu_StartGame(SApp *App) 
{
    SInGame_Switch(App);
    App->State.Init(App);
}

void SMainMenu_ExitApp(SApp *App)
{
    App->Running = 0;
}

void SMainMenu_ShowHighScores(SApp *App)
{
    App->MainMenu->ifhighscores = 1;
}
