#include "InGame.h"

void SInGame_Init(SInGame *self)
{
    self->Head = malloc(sizeof(SPoint));
    self->Head->x = 0;
    self->Head->y = 0;
    self->Head->next = NULL;

    self->dx = 0;
    self->dy = 1;

    self->Food.x = rand()%MATRIXSIZE;
    self->Food.y = rand()%MATRIXSIZE;
    self->Food.next=NULL;

    self->KeyPressed = 0;

    self->Timer = 0;
    self->Speed = 3;
    SInGame_InitGraphics();
    SInGame_InitSound(self);
    
}

void SInGame_InitGraphics(void)
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

void SInGame_InitSound(SInGame *self)
{
    self->Music = NULL;

    int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16; /* 16-bit stereo */
    int audio_channels = 2;
    int audio_buffers = 512; 

    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) {
	printf("Unable to open audio!\n");
	exit(EXIT_FAILURE);
    }

    self->Music = Mix_LoadMUS("./sound/this.ogg");
    Mix_PlayMusic(self->Music, -1);
     
    self->Nyam.Snd = Mix_LoadWAV("./sound/nom.ogg");
    self->Nyam.Chnl = -1;
}

void SInGame_PlaySound(Sound *Snd) 
{
    if (Snd->Chnl < 0) Snd->Chnl = Mix_PlayChannel(Snd->Chnl, Snd->Snd, 0);
    Snd->Chnl = -1;
}

void SInGame_Render(SInGame *self)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (self->Head->next != NULL) {
        SPoint *curr = self->Head->next;
        do {
            glColor3f(0.0, 0.3, 0.8);
            SInGame_Cube(curr->x,curr->y, CUBESIZE);
            curr = curr->next;
        } while (curr != NULL);
    }
    glColor3f(0.7, 0.3, 0.1);
    SInGame_Cube(self->Food.x,self->Food.y, CUBESIZE+1);
    glColor3f(0.1, 0.5, 0.5);
    SInGame_Cube(self->Head->x,self->Head->y, CUBESIZE+2);
    SInGame_Grid();
    SDL_GL_SwapBuffers();
}

void SInGame_Cube(int x, int y, int size)
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
}

void SInGame_Grid(void)
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

void SInGame_Loop(SInGame *self)
{
    if (self->Timer > self->Speed) {
	self->Timer = 0;
	SInGame_ProcessNewState(self);
    } else self->Timer++;
}

void SInGame_ProcessNewState(SInGame *self) 
{
    int PrevX = self->Head->x;
    int PrevY = self->Head->y;

    self->Head->x+=self->dx;
    self->Head->y+=self->dy;

    self->KeyPressed = 0;
    self->Timer = 0;

    if (self->Head->x < 0) self->Head->x+=MATRIXSIZE;
    if (self->Head->y < 0) self->Head->y+=MATRIXSIZE;
    if (self->Head->x >= MATRIXSIZE) self->Head->x-=MATRIXSIZE;
    if (self->Head->y >= MATRIXSIZE) self->Head->y-=MATRIXSIZE;

    if ((self->Head->x == self->Food.x) && (self->Head->y == self->Food.y)) {
        self->Food.x = rand()%MATRIXSIZE;
        self->Food.y = rand()%MATRIXSIZE;
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
            int temp = curr->x;
            curr->x = PrevX;
            PrevX = temp;
            temp = curr->y;
            curr->y = PrevY;
            PrevY = temp;
        }
    }
}

void SInGame_ProcessEvent(SInGame *self, SDL_Event *Event)
{
    switch (Event->type) {
    case SDL_KEYDOWN : {
        SInGame_OnKeyDown(self, Event->key.keysym.sym,Event->key.keysym.mod,Event->key.keysym.unicode);
        break;
    }
    case SDL_QUIT : {
        self->App->Running = 0;
        break;
    }
    default:
        break;
    }
}

void SInGame_OnKeyDown(SInGame *self, SDLKey sym, SDLMod mod, Uint16 unicode)
{
    switch (sym) {
    case 282: { //F1
	self->dx=0;
	self->dy=0;
	break;
    }
	/*    case 27: { //ESC
	if (self->State==ingame) self->State=paused;
	else self->State=ingame;
        break;
	}*/
    case 119: { //W
        if ((self->dy == 0) && !self->KeyPressed) {
            self->dy = -1;
            self->dx = 0;
	    self->KeyPressed = 1;
        } else break;
        break;
    }
    case 97: { //A
        if ((self->dx == 0) && !self->KeyPressed) {
            self->dy = 0;
            self->dx = -1;
	    self->KeyPressed = 1;
        } else break;
        break;
    }
    case 115: { //S
        if ((self->dy == 0) && !self->KeyPressed) {
            self->dy = 1;
            self->dx = 0;
	    self->KeyPressed = 1;
        } else break;
        break;
    }
    case 100: { //D
        if ((self->dx == 0) && !self->KeyPressed) {
            self->dy = 0;
            self->dx = 1;
	    self->KeyPressed = 1;
        } else break;
        break;
    }
    case 270: { //Num+
	self->Speed--;
	break;
    }
    case 269: { ///Num-
	self->Speed++;
	break;
    }
    default: break;
    }
}

void SInGame_Cleanup(SInGame *self)
{
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

    free(self->Class);
    free(self);
}

SInGame *newSInGame(SApp *App)
{
    SInGame *self = malloc(sizeof(SInGame));
    self->Class = malloc(sizeof(State_Class));

    self->Class->Init = &SInGame_Init;
    self->Class->Loop = &SInGame_Loop;
    self->Class->Event = &SInGame_ProcessEvent;
    self->Class->Render = &SInGame_Render;
    self->Class->Cleanup = &SInGame_Cleanup;
    self->App = App;
    self->self=self;
    return self;
}
