#include "ttfonts.h"

void SFont_Create(SApp *App)
{
    App->Font = malloc(sizeof(SFont));
}

void SFont_Delete(SApp *App)
{
    SFont *self = App->Font;
    TTF_CloseFont(self->font16);
    TTF_CloseFont(self->font24);
    TTF_Quit();
    free(self);
}

void SFont_InitTTF(SFont *self, char *filename)
{
    TTF_Init();
    self->font24 = TTF_OpenFont(filename, 24);
    if (!self->font24) fprintf(stderr, "(EE) Loading 24-font %s failed!\n", filename);
    self->font16 = TTF_OpenFont(filename, 16);
    if (!self->font16) fprintf(stderr, "(EE) Loading 16-font %s failed!\n", filename);
    self->font48 = TTF_OpenFont(filename, 48);
    if (!self->font48) fprintf(stderr, "(EE) Loading 48-font %s failed!\n", filename);

}

void SFont_glEnable2D()
{
    int vPort[4];

    glDisable(GL_DEPTH_TEST);

    glGetIntegerv(GL_VIEWPORT, vPort);
  
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
  
    glOrtho(0, vPort[2], 0, vPort[3], -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}

void SFont_glDisable2D()
{
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();   
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glEnable(GL_DEPTH_TEST);
}

void SFont_RenderText(SFont *self, const char *text, SDL_Rect *location, SDL_Color *color, enum FontSize s)
{
    SDL_Surface *initial;
    SDL_Surface *intermediary;
    int w,h;
    GLuint texture;

    if (s == size24) initial = TTF_RenderUTF8_Solid(self->font24, text, *color);
    else if (s == size16) initial = TTF_RenderUTF8_Solid(self->font16, text, *color);
    else initial = TTF_RenderUTF8_Solid(self->font48, text, *color);

    w = SFont_nextpoweroftwo(initial->w);
    h = SFont_nextpoweroftwo(initial->h);
	
    intermediary = SDL_CreateRGBSurface(0, w, h, 32,
					0x00ff0000,
					0x0000ff00,
					0x000000ff,
					0xff000000);
    
    SDL_BlitSurface(initial, 0, intermediary, 0);
	
    /* Tell GL about our new texture */
    
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);	

    glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_BGRA, 
		 GL_UNSIGNED_BYTE, intermediary->pixels );
	
    /* Prepare to render our texture */
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glColor3f(1.0f, 1.0f, 1.0f);
	
    /* Draw a texture quad at location */
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(location->x    , location->y);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(location->x + w, location->y);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(location->x + w, location->y + h);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(location->x    , location->y + h);
    glEnd();
	
    /* Bad things happen if we delete the texture before it finishes */
    glFinish();
	
    /* return the deltas in the unused w,h part of the rect */
    location->w = initial->w;
    location->h = initial->h;

    /* Clean up */
    SDL_FreeSurface(initial);
    SDL_FreeSurface(intermediary);
    glDeleteTextures(1, &texture);
}

int SFont_nextpoweroftwo(int x)
{
    double logbase2 = log(x) / log(2);
    return round(pow(2,ceil(logbase2)));
}
