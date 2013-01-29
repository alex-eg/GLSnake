#ifndef _S_TTFONTS
#define _S_TTFONTS

#include "globals.h"
#include <SDL/SDL_ttf.h>
#include <math.h>

enum FontSize {size24, size16, size48};

struct SFont {
    TTF_Font *font24;
    TTF_Font *font16;
    TTF_Font *font48;
};
typedef struct SFont SFont;

/*--- Fonts! ---*/
void SFont_InitTTF (SFont *, char *filename);
void SFont_glEnable2D (void);
void SFont_glDisable2D (void);
void SFont_RenderText (SFont *, const char *, SDL_Rect *, SDL_Color *, enum FontSize);
int SFont_nextpoweroftwo (int);

#endif /* ifndef _S_TTFONTS */
