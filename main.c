/*--- HINT! Compile with "gcc -o snake main.c -lSDL -lGL" ---
      Disregard that ^, use the allmighty GNUMake!

 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "InGame.h"
#include "Paused.h"

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
            Snake.State->Event(&Snake, &Event);
        }
        Snake.State->Loop(&Snake);
        Snake.State->Render(&Snake);
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
    App->InGame = NULL;
    App->Paused = NULL;
    App->State = malloc(sizeof(vtable_State));

    SInGame_Create(App);
    SPaused_Create(App);
    SInGame_Switch(App);

    App->State->Init(App);
    App->Running = 1;
    return SdlRet;
}

void SCleanup(SApp *App)
{
    SDL_FreeSurface(App->SDisplay);
    Mix_CloseAudio();
    App->State->Cleanup(App);
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
