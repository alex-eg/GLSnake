#include "gui.h"

/* Textures are our gui decals

*/

int STexture_Load(STexture *self, char *filename)
{
    STGAFile textureFile;
    int res;
    if ((res = STGA_ReadFromFile(&textureFile, filename))) printf("%s\n", STGA_GetErrorDescription(res));

    if (textureFile.header.width != textureFile.header.height) {
	printf("Texture dimensions don't match!\n");
	exit(1);
    }
    self->size = textureFile.header.width;
    self->bitsPerPixel = textureFile.header.pixelDepth;

    glGenTextures(1, &self->texID);
    glBindTexture(GL_TEXTURE_2D, self->texID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D(GL_TEXTURE_2D,
		 0,
		 GL_RGB,
		 self->size,
		 self->size,
		 0,
		 GL_BGR,
		 GL_UNSIGNED_BYTE,
		 textureFile.image.imageData);
    STGA_Delete(&textureFile);
    return 0;
}

void STexture_Unload(STexture *self)
{
    if (glIsTexture(self->texID)) glDeleteTextures(1, &self->texID);
}

/* SLABEL */

SLabel * SLabel_Create(void)
{
    SLabel *self = malloc(sizeof(SLabel));
    SLabel_Set(self, 0, 0, 10, 10);
    return self;
}

void SLabel_Set(SLabel *self, int x, int y, int w, int h)
{
    self->x = x;
    self->y = y;
    self->width = w;
    self->height = h;
}

void SLabel_SetTexture(SLabel *self, char *filename)
{
    STexture_Load(&self->texture, filename);
}

void SLabel_Render(SLabel *self)
{
    glBindTexture(GL_TEXTURE_2D, self->texture.texID);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0,     0.0);
    glVertex2f  (self->x, self->y);
    glTexCoord2f(1.0,     0.0);
    glVertex2f  (self->x + self->width, self->y);
    glTexCoord2f(1.0,     1.0);
    glVertex2f  (self->x + self->width, self->y + self->height);
    glTexCoord2f(0.0,     1.0);
    glVertex2f  (self->x, self->y + self->height);

    glEnd();
}

void SLabel_Delete(SLabel *self)
{
    STexture_Unload(&self->texture);
    free(self);
}

/* SBUTTON */

SButton * SButton_Create(void)
{
    SButton *self = malloc(sizeof(SButton));
    SButton_Set(self, 0, 0, 10, 10);
    SButton_SetCallback(self, SButton_DefaultCallback);
    return self;
}

void SButton_Delete(SButton *self)
{
    STexture_Unload(&self->texture);
}

void SButton_Set(SButton *self, int x, int y, int w, int h)
{
    self->x = x;
    self->y = y;
    self->width = w;
    self->height = h;
    self->next = NULL;
    self->prev = NULL;
    self->selected = 0;
}

void SButton_SetTexture(SButton *self, char *filename)
{
    STexture_Load(&self->texture, filename);
}

void SButton_Render(SButton *self)
{
    glBindTexture(GL_TEXTURE_2D, self->texture.texID);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0,     0.0);
    glVertex2f  (self->x, self->y);
    glTexCoord2f(1.0,     0.0);
    glVertex2f  (self->x + self->width, self->y);
    glTexCoord2f(1.0,     1.0);
    glVertex2f  (self->x + self->width, self->y + self->height);
    glTexCoord2f(0.0,     1.0);
    glVertex2f  (self->x, self->y + self->height);

    glEnd();


    if (!self->selected) return;
    glDisable(GL_TEXTURE_2D);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLES);
    glVertex2f(self->x - 30, self->y);
    glVertex2f(self->x - 2 , self->y + self->height / 2);
    glVertex2f(self->x - 30, self->y + self->height);
    glEnd();

    glEnable(GL_TEXTURE_2D);
}

int SButton_Swap(SButton *self)
{
    self->selected ^= 1;
    return self->selected;
}

void SButton_Link(SButton *prev, SButton *next)
{
    prev->next = next;
    next->prev = prev;
}

void SButton_SetCallback(SButton *self, void (*p)(SApp *))
{
    self->callback = p;
}

void SButton_Call(SButton *self, SApp *App)
{
    self->callback(App);
}

void SButton_DefaultCallback(SApp *App)
{
    printf("Hello, I'm default callback function\n");
}
