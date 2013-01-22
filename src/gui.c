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
    self->texID = 1;
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
    glDeleteTextures(1, &self->texID);
}

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
}
