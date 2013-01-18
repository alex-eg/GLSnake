#include "gui.h"

/* Textures are our gui decals

 */
int SLoadTexture(STexture *self, char *filename)
{
    self->data = NULL;
    self->width = -1;
    self->height = -1;
    return 0;
}
