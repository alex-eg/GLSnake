#include "Graphics.h"

void SRender(SApp *App)
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (App->Head->next != NULL) {
        SPoint *curr = App->Head->next;
        do {
            glColor3f(0.0, 0.3, 0.8);
            SRect(curr->x,curr->y);
            curr = curr->next;
        } while (curr != NULL);
    }
    glColor3f(0.7, 0.3, 0.1);
    SRect(App->Food.x,App->Food.y);
    glColor3f(0.1, 0.5, 0.5);
    SRect(App->Head->x,App->Head->y);
    SGrid();
    SDL_GL_SwapBuffers();
}

void SRect(int x, int y)
{
    int xc, yc;
    xc=CELLSIZE*x+CELLSIZE/2;
    yc=CELLSIZE*y+CELLSIZE/2;

    glBegin(GL_QUADS);

    glVertex2f(xc-CUBESIZE, yc-CUBESIZE);
    glVertex2f(xc+CUBESIZE, yc-CUBESIZE);
    glVertex2f(xc+CUBESIZE, yc+CUBESIZE);
    glVertex2f(xc-CUBESIZE, yc+CUBESIZE);

    glEnd();
}

void SGrid(void)
{
    int i=0;
    glColor3f(0.3, 0.0 ,0.0);
    for (; i<=MATRIXSIZE; i++) {
        glBegin(GL_LINES);
        glVertex2f(CELLSIZE*i,0);
        glVertex2f(CELLSIZE*i,CELLSIZE*MATRIXSIZE);

        glEnd();

        glBegin(GL_LINES);

        glVertex2f(0,CELLSIZE*i);
        glVertex2f(CELLSIZE*MATRIXSIZE,CELLSIZE*i);

        glEnd();
    }
}
