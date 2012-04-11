/*--- HINT! Compile with "gcc -o snake main.c -lSDL -lGL" ---*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "InGame.h"

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

    printf("Entering loop...\n");
    while (Snake.Running) {
        while (SDL_PollEvent(&Event)) {
            Snake.State->Class->Event(Snake.State, &Event);
        }

        Snake.State->Class->Loop(Snake.State);
        Snake.State->Class->Render(Snake.State);
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
    App->State=NULL;
    SInGame *state = newSInGame(App);
    SSetState(App, state);
    App->Running = 1;
    return SdlRet;
}

void SCleanup(SApp *App)
{
    SDL_FreeSurface(App->SDisplay);
    Mix_CloseAudio();
    App->State->Class->Cleanup(App->State);
    SDL_Quit();
}

int SInitSdl(SApp *App)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return 1;

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

    if ((App->SDisplay = SDL_SetVideoMode(CELLSIZE*MATRIXSIZE, CELLSIZE*MATRIXSIZE, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL)) == NULL) return 2;
    
    return 0;
}

void SSetState(SApp *App, SInGame *state)
{
    if (App->State)
	App->State->Class->Cleanup(App->State);
    App->State = state;
    App->State->Class->Init(App->State);
};
