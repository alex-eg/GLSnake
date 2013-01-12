#ifndef _S_GUI
#define _S_GUI

#include "globals.h"

#include <stdio.h>
#include <stdlib.h>

struct STexture{
    int width, height;
    void *data; /* RGB data */
};

typedef struct STexture STexture;

/*--- Textures! ---*/
int SLoadTexture(STexture *, char *filename);
void SDrawTexture(STexture *);

#endif /* ifndef _S_GUI */
