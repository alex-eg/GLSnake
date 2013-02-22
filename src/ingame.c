#include "gameover.h"
#include "ingame.h"
#include "paused.h"
#include "gui.h"

STexture te;

void SInGame_Init(SApp *App)
{
    SInGame_Clear(App);
    
    SInGame *self = App->InGame;

    for (int i = 0; i < MATRIXSIZE * MATRIXSIZE; i++) self->Field[i] = 0;

    self->Score = 0;

    self->Head = malloc(sizeof(SPoint));
    self->Head->x = 0;
    self->Head->y = 0;

    self->Field [self->Head->x * MATRIXSIZE + self->Head->y] = 1;
    
    self->Head->next = NULL;

    self->dx = 0;
    self->dy = 1;

    self->Food.x = rand() % MATRIXSIZE;
    self->Food.y = rand() % MATRIXSIZE;
    self->Food.next = NULL;
    self->Field [self->Food.x * MATRIXSIZE + self->Food.y] = 2;

    self->KeyPressed = 0;

    self->Timer = 0;
    self->Speed = 1;

    SInGame_InitGraphics();
    SInGame_InitSound(App);
}

void SInGame_InitGraphics(void)
{
    glDisable(GL_TEXTURE_2D);

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
    glLoadIdentity();
    glFrustum(-305, 305, 305, -305, 655, 805);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-CELLSIZE*MATRIXSIZE/2, -CELLSIZE*MATRIXSIZE/2, -804.0f);
}

void SInGame_InitSound(SApp *App)
{
    App->InGame->Music = NULL;

    int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16SYS; /* 16-bit stereo */
    int audio_channels = 2;
    int audio_buffers = 512; 

    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)!=0) {
	printf("Unable to open audio: %s\n", Mix_GetError());
	exit(EXIT_FAILURE);
    }

    
    App->InGame->Music = Mix_LoadMUS(RESOURCE_DIR "/sound/this.ogg");
    if (App->InGame->Music == NULL) printf("Unable to load sound: %s\n", Mix_GetError());
    Mix_PlayMusic(App->InGame->Music, -1);
     
    App->InGame->Nyam.Snd = Mix_LoadWAV(RESOURCE_DIR "/sound/nom.ogg");
    if (App->InGame->Nyam.Snd == NULL) printf("Unable to load sound: %s\n", Mix_GetError());
    App->InGame->Nyam.Chnl = -1;
}

void SInGame_PlaySound(Sound *Snd) 
{
    if (Snd->Chnl < 0) Snd->Chnl = Mix_PlayChannel(Snd->Chnl, Snd->Snd, 0);
    Snd->Chnl = -1;
}

void SInGame_Render(SApp *App)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (App->InGame->Head->next != NULL) {
        SPoint *curr = App->InGame->Head->next;
        do {
	  glColor3f(0.0, 0.3, 0.8);
	  SInGame_Cube(App, curr->x,curr->y, CUBESIZE);
	  curr = curr->next;
        } while (curr != NULL);
    }
    glColor3f(0.7, 0.3, 0.1);
    SInGame_Cube(App, App->InGame->Food.x,App->InGame->Food.y, CUBESIZE+1);
    glColor3f(0.1, 0.5, 0.5);
    SInGame_Cube(App, App->InGame->Head->x,App->InGame->Head->y, CUBESIZE+2);
    SInGame_Grid();
    SDL_GL_SwapBuffers();
}

void SInGame_Cube(SApp *App, int x, int y, int size)
{
    int xc, yc;
    xc=CELLSIZE*x+(CELLSIZE-size)/2;
    yc=CELLSIZE*y+(CELLSIZE-size)/2;
    
    glPushMatrix();
    glTranslatef(xc, yc, 0);

    glBegin(GL_QUADS);
        
    /* BOTTOM */
    glNormal3d(0,0,-1);
    glVertex3d(        0,         0, 0); 
    glVertex3d(     size,         0, 0);
    glVertex3d(     size,      size, 0);
    glVertex3d(        0,      size, 0);

    /* REAR */
    glNormal3d(0,-1,0);
    glVertex3d(       0, 0,        0);
    glVertex3d(    size, 0,        0);
    glVertex3d(    size, 0,     size);
    glVertex3d(       0, 0,     size);

    /* RIGHT */
    glNormal3d(1,0,0);
    glVertex3d(    size,        0,        0);
    glVertex3d(    size,     size,        0);
    glVertex3d(    size,     size,     size);
    glVertex3d(    size,        0,     size);

    /* FRONT */
    glNormal3d(0,1,0);
    glVertex3d(       0,     size,        0);
    glVertex3d(    size,     size,        0);
    glVertex3d(    size,     size,     size);
    glVertex3d(       0,     size,     size);

    /* LEFT */
    glNormal3d(-1,0,0);
    glVertex3d(       0,        0,        0);
    glVertex3d(       0,     size,        0);
    glVertex3d(       0,     size,     size);
    glVertex3d(       0,        0,     size);

    /* TOP */
    glNormal3d(0,0,1);
    glVertex3d(       0,        0,     size);
    glVertex3d(       0,     size,     size);
    glVertex3d(    size,     size,     size);
    glVertex3d(    size,        0,     size);

    glEnd();
    glPopMatrix();

    glFinish();
}

void SInGame_Grid(void)
{
    int i=0;
    glColor3f(0.3, 0.0 ,0.0);
    for (; i <= MATRIXSIZE; i++) {
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

void SInGame_Loop(SApp *App)
{
    if (App->InGame->Timer > App->InGame->Speed) {
	App->InGame->Timer = 0;
	SInGame_ProcessNewState(App);
    } else App->InGame->Timer++;
}

void SInGame_ProcessNewState(SApp *App) 
{
    SInGame *self = App->InGame;

    int PrevX = self->Head->x;
    int PrevY = self->Head->y;

    int HeadX = PrevX;
    int HeadY = PrevY;
        
    self->Head->x += self->dx;
    self->Head->y += self->dy;

    self->Field [HeadX * MATRIXSIZE + HeadY] = 0;

    self->KeyPressed = 0;
    self->Timer = 0;

    if (self->Head->x < 0) self->Head->x += MATRIXSIZE;
    if (self->Head->y < 0) self->Head->y += MATRIXSIZE;
    if (self->Head->x >= MATRIXSIZE) self->Head->x -= MATRIXSIZE;
    if (self->Head->y >= MATRIXSIZE) self->Head->y -= MATRIXSIZE;

    if ((self->Head->x == self->Food.x) && (self->Head->y == self->Food.y)) {
	self->Score++;
	self->Food.x = rand() % MATRIXSIZE;
	self->Food.y = rand() % MATRIXSIZE;
	while (self->Field [self->Food.x * MATRIXSIZE + self->Food.y] == 1) {
	    self->Food.x = rand() % MATRIXSIZE;
	    self->Food.y = rand() % MATRIXSIZE;
	}
		
	self->Field [self->Food.x * MATRIXSIZE + self->Food.y] = 2;

        self->Food.next = NULL;

        SPoint *NewSegment = malloc(sizeof(SPoint));
        NewSegment->x = PrevX;
        NewSegment->y = PrevY;
        NewSegment->next = self->Head->next;
	self->Head->next = NewSegment;

	SInGame_PlaySound(&self->Nyam);
    } else {
        SPoint *curr = self->Head;
        while (curr->next != NULL) {
            curr = curr->next;

	    self->Field [curr->x * MATRIXSIZE + curr->y] = 0;

            int temp; 
	    temp = curr->x;
            curr->x = PrevX;
            PrevX = temp;
           
	    temp = curr->y;
            curr->y = PrevY;
            PrevY = temp;

	    self->Field [curr->x * MATRIXSIZE + curr->y] = 1;
        }
    }
    int gameOver = 0;
    if (self->Field [self->Head->x * MATRIXSIZE + self->Head->y] == 1) gameOver = 1;
    
    if (gameOver) {
	SGameOver_Init(App);
	SGameOver_SetScore(App, self->Score);
	SGameOver_Switch(App);
    }
}

void SInGame_ProcessEvent(SApp *App, SDL_Event *Event)
{
    switch (Event->type) {
    case SDL_KEYDOWN : {
        SInGame_OnKeyDown(App, Event->key.keysym.sym);
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

void SInGame_OnKeyDown(SApp *App, SDLKey sym)
{
    switch (sym) {
    case SDLK_F1: { //F1
	App->InGame->dx=0;
	App->InGame->dy=0;
	break;
    }
    case SDLK_ESCAPE: { //ESC
	SPaused_Switch(App);
	App->State.Init(App);
	break;
    }
    case SDLK_UP: { //UP Arrow
        if ((App->InGame->dy == 0) && !App->InGame->KeyPressed) {
            App->InGame->dy = -1;
            App->InGame->dx = 0;
	    App->InGame->KeyPressed = 1;
        };
        break;
    }
    case SDLK_LEFT: { //LEFT Arrow
        if ((App->InGame->dx == 0) && !App->InGame->KeyPressed) {
            App->InGame->dy = 0;
            App->InGame->dx = -1;
	    App->InGame->KeyPressed = 1;
        };
        break;
    }
    case SDLK_DOWN: { //DOWN Arrow
        if ((App->InGame->dy == 0) && !App->InGame->KeyPressed) {
            App->InGame->dy = 1;
            App->InGame->dx = 0;
	    App->InGame->KeyPressed = 1;
        };
        break;
    }
    case SDLK_RIGHT: { //RIGHT Arrow
        if ((App->InGame->dx == 0) && !App->InGame->KeyPressed) {
            App->InGame->dy = 0;
            App->InGame->dx = 1;
	    App->InGame->KeyPressed = 1;
        };
        break;
    }
    case SDLK_KP_PLUS: { //Num+
	App->InGame->Speed--;
	break;
    }
    case SDLK_KP_MINUS: { //Num-
	App->InGame->Speed++;
	break;
    }
    default: break;
    }
}

void SInGame_Clear(SApp *App)
{
    SInGame *self = App->InGame;
    if (self->Head == NULL) return;
    if (self->Head->next == NULL)
	free(self->Head);
    else if (self->Head->next->next == NULL) {
	free(self->Head->next);
	free(self->Head);
    } else {
	while (self->Head->next != NULL) {
	    SPoint *curr = self->Head;
	    SPoint *next = self->Head->next;
	    while (next->next != NULL) { 
		curr = next;
		next = curr->next;
	    }
	    free (next);
	    curr->next = NULL;
	}
	free(self->Head);
    }
}

void SInGame_Delete(SApp *App)
{
    SInGame_Clear(App);
    free(App->InGame);
    App->InGame = NULL;
}

void SInGame_Create(SApp *App)
{
    SInGame *self;
    App->InGame = self = (SInGame *) malloc(sizeof(SInGame));
    self->App = App;
    self->Head = NULL;
}

void SInGame_Switch(SApp *App)
{
    App->State.Init = &SInGame_Init;
    App->State.Loop = &SInGame_Loop;
    App->State.Event = &SInGame_ProcessEvent;
    App->State.Render = &SInGame_Render;
    App->State.Cleanup = &SInGame_Delete;
}
