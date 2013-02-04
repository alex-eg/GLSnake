#ifndef _S_HIGHSCORES
#define _S_HIGHSCORES

#include "globals.h"
#include "ttfonts.h"

#include <stdio.h>

struct HighScoreTable {
    int first, second, third;
    char nameFirst[8], nameSecond[8], nameThird[8];
};
typedef struct HighScoreTable HighScoreTable;

struct SHighScores {
    SApp *App;
    struct HighScoreTable table;
};
typedef struct SHighScores SHighScores;

void SHighScores_Read(SApp *, const char *filename);
void SHighScores_Create(SApp *);
void SHighScores_Delete(SApp *);
void SHighScores_Save(SApp *, const char *filename);

void SHighScores_Render(SApp *);

#endif /* ifndef _S_HIGHSCORES */
