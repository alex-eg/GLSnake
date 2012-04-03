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
     /*-----------------------------APP---------------------------------------*/
    SInitApp(App);
    
    /*------------------------------SDL---------------------------------------*/
    int SdlRet = SInitSdl(App);

    /*------------------------------OGL---------------------------------------*/
    SInitGraphics();

    /*-----------------------------SOUND--------------------------------------*/
    SInitSound(App);

    return SdlRet;
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
