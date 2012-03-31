/*--- HINT! Compile with "gcc -o snake main.c -lSDL -lGL" ---*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include <SDL/SDL.h>
#include <GL/gl.h>

#define CUBESIZE 15
#define CELLSIZE 36
#define MATRIXSIZE 20

struct SPoint{
    int x,y;
    struct SPoint *next;
};

typedef struct SPoint SPoint;

enum state {loading, menu, ingame, paused, highscores};
typedef enum state state;

typedef struct {
    int Running;
    SDL_Surface* SDisplay;
    int dx, dy;
    SPoint Food;
    SPoint *Head;
    int KeyPressed;
    state State;
    int Timer;
    int Speed;
} SApp;

int SInit(SApp *);
void SProcessEvent(SApp *, SDL_Event *);
void SLoop(SApp *);
void SRender(SApp *);
void SCleanup(SApp *);
void SOnKeyDown(SApp *, SDLKey, SDLMod, Uint16);

/*--- LOOP ---*/
void ProcessNewState(SApp *);

/*--- GRAPHICS ---*/
void SRect(int, int);
void SGrid(void);

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
        SDL_Delay(10);
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
    return 0;
}

void SProcessEvent(SApp *App, SDL_Event *Event)
{
    switch (Event->type) {
    case SDL_KEYDOWN : {
        SOnKeyDown(App, Event->key.keysym.sym,Event->key.keysym.mod,Event->key.keysym.unicode);
        break;
    }
    case SDL_QUIT : {
        App->Running = 0;
        break;
    }
    default:
        break;
    }
}

void SLoop(SApp *App)
{
    if ((App->Timer++ >= App->Speed) && (App->State == ingame))
	ProcessNewState(App);
}

void SRender(SApp *App)
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (App->Head->next != NULL) {
        SPoint *curr = App->Head->next;
        do {
            glColor3f(0.0, 0.3, 0.8);
            SRect(curr->x,curr->y);
            curr = curr->next;
        } while (curr != NULL);
    }
    glColor3f(0.7, 0.3, 0.1);
    SRect(App->Food.x,App->Food.y);
    glColor3f(0.1, 0.5, 0.5);
    SRect(App->Head->x,App->Head->y);
    SGrid();
    SDL_GL_SwapBuffers();
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
}

void SOnKeyDown(SApp *App, SDLKey sym, SDLMod mod, Uint16 unicode)
{
    switch (sym) {
    case 282: { //F1
	App->dx=0;
	App->dy=0;
	break;
    }
    case 27: { //ESC
	if (App->State==ingame) App->State=paused;
	else App->State=ingame;
        break;
    }
    case 119: { //W
        if ((App->dy == 0) && !App->KeyPressed) {
            App->dy = -1;
            App->dx = 0;
	    App->KeyPressed = 1;
        } else break;
        break;
    }
    case 97: { //A
        if ((App->dx == 0) && !App->KeyPressed) {
            App->dy = 0;
            App->dx = -1;
	    App->KeyPressed = 1;
        } else break;
        break;
    }
    case 115: { //S
        if ((App->dy == 0) && !App->KeyPressed) {
            App->dy = 1;
            App->dx = 0;
	    App->KeyPressed = 1;
        } else break;
        break;
    }
    case 100: { //D
        if ((App->dx == 0) && !App->KeyPressed) {
            App->dy = 0;
            App->dx = 1;
	    App->KeyPressed = 1;
        } else break;
        break;
    }
    case 270: { //Num+
	App->Speed--;
	break;
    }
    case 269: { ///Num-
	App->Speed++;
	break;
    }
    default: break;
    }
}

void SRect(int x, int y)
{
    int xc, yc;
    xc=CELLSIZE*x+CELLSIZE/2;
    yc=CELLSIZE*y+CELLSIZE/2;

    glBegin(GL_QUADS);

    glVertex2f(xc-CUBESIZE, yc-CUBESIZE);
    glVertex2f(xc+CUBESIZE, yc-CUBESIZE);
    glVertex2f(xc+CUBESIZE, yc+CUBESIZE);
    glVertex2f(xc-CUBESIZE, yc+CUBESIZE);

    glEnd();
}

void SGrid(void)
{
    int i=0;
    glColor3f(0.3, 0.0 ,0.0);
    for (; i<=MATRIXSIZE; i++) {
        glBegin(GL_LINES);
        glVertex2f(CELLSIZE*i,0);
        glVertex2f(CELLSIZE*i,CELLSIZE*MATRIXSIZE);

        glEnd();

        glBegin(GL_LINES);

        glVertex2f(0,CELLSIZE*i);
        glVertex2f(CELLSIZE*MATRIXSIZE,CELLSIZE*i);

        glEnd();
    }
}

void ProcessNewState(SApp *App) {

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
