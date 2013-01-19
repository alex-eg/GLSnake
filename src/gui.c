#include "gui.h"

/* Textures are our gui decals

*/

int STexture_Load(STexture *self, char *filename)
{
    STGAFile textureFile;
    if (STGA_ReadFromFile(&textureFile, filename) != E_SUCCESS) exit(12);
    
    self->data = textureFile.image.imageData;
    self->width = textureFile.header.width;
    self->height = textureFile.header.height;
    self->bitsPerPixel = textureFile.header.pixelDepth;

    glGenTextures(1, &self->texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexImage2D (GL_TEXTURE_2D,
		  0,
		  GL_RGB,
		  self->width,
		  self->height,
		  0,
		  GL_BGR,
		  GL_UNSIGNED_BYTE,
		  self->data);
    return 0;
}

void STexture_Unload(STexture *self)
{
    free(self->data);
    glDeleteTextures(1, &self->texID);
}

void SLabel_Create(SLabel *self, int x, int y, int w, int h)
{
    self = malloc(sizeof(SLabel));
    self->x = x;
    self->y = y;
    self->width = w;
    self->height = h;
}

void SLabel_SetTexture(SLabel *self, char *filename)
{
    STexture_Load(self->texture, filename);
}

void SLabel_Render(SLabel *self)
{
    glBindTexture(GL_TEXTURE_2D, self->texture->texID);

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
    STexture_Unload(self->texture);
}
