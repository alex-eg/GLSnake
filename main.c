/*--- HINT! Compile with "gcc -o snake main.c -lSDL -lGL" ---*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Globals.h"

int SInit(SApp *);
void SLoop(SApp *);
void SCleanup(SApp *);

/*--- LOOP ---*/
void ProcessNewState(SApp *);

int main(int argc, char** argv)
{
    srand(time(NULL));

    SDL_Event Event;
    SApp Snake;

    if (SInit(&Snake) != 0) {
        printf("SDL init failed, terminating...\n");
        exit(EXIT_FAILURE);
    }

    printf("Entering loop...\n");
    while (Snake.Running) {
        while (SDL_PollEvent(&Event)) {
            SProcessEvent(&Snake, &Event);
        }

        SLoop(&Snake);
        SRender(&Snake);
        SDL_Delay(50);
    }
    printf("Cleaning up... ");
    SCleanup(&Snake);
    printf("Good bye!\n");
    return 0;
}

int SInit(SApp *App)
{
    /*------------------------------APP---------------------------------------*/

    App->Head = malloc(sizeof(SPoint));
    App->Head->x = 5;
    App->Head->y = 5;
    App->Head->next = NULL;

    App->dx = -1;
    App->dy = 0;

    App->Food.x = rand()%MATRIXSIZE;
    App->Food.y = rand()%MATRIXSIZE;
    App->Food.next=NULL;

    App->KeyPressed = 0;

    App->State = loading;
    App->Running = 1;
    App->Timer = 0;
    App->Speed = 3;
    App->State = ingame;
    
    /*------------------------------SDL---------------------------------------*/

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return 1;

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,            8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,          8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,           8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,          8);

    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,         32);

    SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,      8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,    8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,     8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,    8);

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  0);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  0);

    if ((App->SDisplay = SDL_SetVideoMode(CELLSIZE*MATRIXSIZE, CELLSIZE*MATRIXSIZE, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL)) == NULL) return 2;

    /*------------------------------OGL---------------------------------------*/

    glDisable(GL_DEPTH_TEST);

    glClearColor(0, 0, 0, 0);
    glOrtho(0, CELLSIZE*MATRIXSIZE, CELLSIZE*MATRIXSIZE, 0, -1, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /*-----------------------------SOUND--------------------------------------*/

    SInitSound(App);

    return 0;
}

void SLoop(SApp *App)
{
    if ((App->Timer++ >= App->Speed) && (App->State == ingame))
	ProcessNewState(App);
}

void SCleanup(SApp *App)
{
    SDL_FreeSurface(App->SDisplay);

    if (App->Head->next == NULL)
	free(App->Head);
    else if (App->Head->next->next == NULL) {
	free(App->Head->next);
	free(App->Head);
    } else {
	while (App->Head->next != NULL) {
	    SPoint *curr = App->Head;
	    SPoint *next = App->Head->next;
	    while (next->next != NULL) { 
		curr = next;
		next = curr->next;
	    }
	    free (next);
	    curr->next = NULL;
	}
	free(App->Head);
    }
    Mix_CloseAudio();
    SDL_Quit();
}

void ProcessNewState(SApp *App) 
{
    int PrevX = App->Head->x;
    int PrevY = App->Head->y;

    App->Head->x+=App->dx;
    App->Head->y+=App->dy;

    App->KeyPressed = 0;
    App->Timer = 0;

    if (App->Head->x < 0) App->Head->x+=MATRIXSIZE;
    if (App->Head->y < 0) App->Head->y+=MATRIXSIZE;
    if (App->Head->x >= MATRIXSIZE) App->Head->x-=MATRIXSIZE;
    if (App->Head->y >= MATRIXSIZE) App->Head->y-=MATRIXSIZE;

    if ((App->Head->x == App->Food.x) && (App->Head->y == App->Food.y)) {
        App->Food.x = rand()%MATRIXSIZE;
        App->Food.y = rand()%MATRIXSIZE;
        App->Food.next = NULL;

        SPoint *NewSegment = malloc(sizeof(SPoint));
        NewSegment->x = PrevX;
        NewSegment->y = PrevY;
        NewSegment->next = App->Head->next;
	App->Head->next = NewSegment;

	SPlaySound(&App->Nyam);
    } else {
        SPoint *curr = App->Head;
        while (curr->next != NULL) {
            curr = curr->next;
            int temp = curr->x;
            curr->x = PrevX;
            PrevX = temp;
            temp = curr->y;
            curr->y = PrevY;
            PrevY = temp;
        }
    }
}
