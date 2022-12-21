#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "SDL_render.h"
#include "SDL_video.h"
#include "ingame.h"
#include "paused.h"
#include "mainmenu.h"
#include "ttfonts.h"
#include "gameover.h"

int SInit(SApp *);
void SCleanup(SApp *);
void SInitApp(SApp *);
int SInitSdl(SApp *);

int main(int argc, char** argv)
{
    srand(time(NULL));

    SDL_Event Event;
    SApp Snake;

    if (SInit(&Snake) != 0) {
        printf("Initialization failed, terminating...\n");
        exit(EXIT_FAILURE);
    }

    printf("OpenGL version: %s", glGetString(GL_VERSION));
    printf("Entering loop...\n");
    while (Snake.Running) {
        while (SDL_PollEvent(&Event)) {
            switch (Event.type) {
            case SDL_QUIT : {
                     Snake.Running = 0;
                     break;
                 }
            default:
                Snake.State.Event(&Snake, &Event);
            }
        }
        Snake.State.Loop(&Snake);
        Snake.State.Render(&Snake);
        SDL_Delay(50);
    }
    printf("Cleaning up... ");
    SCleanup(&Snake);
    printf("Good bye!\n");
    return 0;
}

int SInit(SApp *App)
{
    int SdlRet = SInitSdl(App);
    if (SdlRet != 0) {
        return SdlRet;
    }

    SFont_Create(App);
    SFont_InitTTF(App->Font, RESOURCE_DIR "/fonts/aesymatt.ttf");

    App->InGame = NULL;
    App->Paused = NULL;
    App->HighScores = NULL;
    App->MainMenu = NULL;
    App->GameOver = NULL;

    SHighScores_Create(App);
    SHighScores_Read(App, "./scores.dat");

    SGameOver_Create(App);
    SInGame_Create(App);
    SPaused_Create(App);
    SMainMenu_Create(App);

    SMainMenu_Switch(App);

    App->State.Init(App);
    App->Running = 1;
    return SdlRet;
}

void SCleanup(SApp *App)
{
    SHighScores_Save(App, "./scores.dat");
    SHighScores_Delete(App);
    SFont_Delete(App);
    // TODO: SDL_FreeSurface(App->SDisplay);
    Mix_CloseAudio();
    App->State.Cleanup(App);
    SDL_Quit();
}

int SInitSdl(SApp *App)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return 1;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,        1);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,            8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,          8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,           8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,          8);

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,          16);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,         32);

    SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,      8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,    8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,     8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,    8);

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  0);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  0);

    // TODO: Assert
    App->SWindow = SDL_CreateWindow("GLSnake",
                                    SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED,
                                    WIDTH, HEIGHT,
                                    SDL_GL_DOUBLEBUFFER | SDL_WINDOW_OPENGL);
     App->SRenderer = SDL_CreateRenderer(App->SWindow, -1, 0);
     SDL_GL_CreateContext(App->SWindow);

    glViewport(0, 0, WIDTH, HEIGHT);

    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    return 0;
}
