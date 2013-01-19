#ifndef _S_GUI
#define _S_GUI

#include "globals.h"
#include "targa.h"

#include <stdio.h>
#include <stdlib.h>

#include <GL/gl.h>

struct STexture {
    int width, height;
    char bitsPerPixel; 
    void *data; /* RGB data */
    GLuint texID;
};
typedef struct STexture STexture;

struct SLabel {
    int x, y, width, height;
    STexture *texture;
};
typedef struct SLabel SLabel;

struct SButton {
    int x, y, width, height;
    STexture *texture;
    int selected;
    struct SButton *next, *prev;
};
typedef struct SButton SButton;
    
/*--- Textures! ---*/
int STexture_Load(STexture *, char *filename);
void STexture_Unload(STexture *);

/*--- Widgets! ---*/
void SButton_Create(SButton *self);
void SButton_Delete(SButton *self);

void SLabel_Create(SLabel *self, int x, int y, int w, int h);
void SLabel_Delete(SLabel *self);
void SLabel_SetTexture(SLabel *self, char *filename);
void SLabel_Render(SLabel *self);

#endif /* ifndef _S_GUI */
