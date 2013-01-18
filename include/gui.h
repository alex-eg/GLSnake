#ifndef _S_GUI
#define _S_GUI

#include "globals.h"

#include <stdio.h>
#include <stdlib.h>

struct STexture {
    int width, height;
    char bitsPerPixel; 
    void *data; /* RGB data */
};
typedef struct STexture STexture;

struct SLabel {
    int x, y, width, height;
    STexture texture;
};
typedef struct SFrame SFrame;

struct SButton {
    int x, y, width, height;
    STexture texture;
    int selected;
    struct SButton *next, *prev;
};
typedef struct SButton SButton;
    
/*--- Textures! ---*/
int SLoadTexture(STexture *, char *filename);

#endif /* ifndef _S_GUI */
