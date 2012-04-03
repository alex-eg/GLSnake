#include "Globals.h"

void SInitApp(SApp* App)
{
    App->Head = malloc(sizeof(SPoint));
    App->Head->x = 0;
    App->Head->y = 0;
    App->Head->next = NULL;

    App->dx = 0;
    App->dy = 1;

    App->Food.x = rand()%MATRIXSIZE;
    App->Food.y = rand()%MATRIXSIZE;
    App->Food.next=NULL;

    App->KeyPressed = 0;

    App->State = loading;
    App->Running = 1;
    App->Timer = 0;
    App->Speed = 3;
    App->State = ingame;
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

void SInitGraphics(void)
{
    GLfloat light_position[] = { 0.0, 0.0, 3.0, 0.0 };
    GLfloat amb[]  = { 0.0, 0.3, 0.3, 0.7 };

    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv( GL_LIGHT0, GL_AMBIENT , amb  );
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
 
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    
    glMatrixMode(GL_PROJECTION);
    glFrustum(-305, 305, 305, -305, 655, 805);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-CELLSIZE*MATRIXSIZE/2, -CELLSIZE*MATRIXSIZE/2, -804.0f);
}
