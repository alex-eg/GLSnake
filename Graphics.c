#include "Globals.h"

void SRender(SApp *App)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (App->Head->next != NULL) {
        SPoint *curr = App->Head->next;
        do {
            glColor3f(0.0, 0.3, 0.8);
            SCube(curr->x,curr->y, CUBESIZE);
            curr = curr->next;
        } while (curr != NULL);
    }
    glColor3f(0.7, 0.3, 0.1);
    SCube(App->Food.x,App->Food.y, CUBESIZE+1);
    glColor3f(0.1, 0.5, 0.5);
    SCube(App->Head->x,App->Head->y, CUBESIZE+2);
    SGrid();
    SDL_GL_SwapBuffers();
}

void SCube(int x, int y, int size)
{
    int xc, yc;
    xc=CELLSIZE*x+(CELLSIZE-size)/2;
    yc=CELLSIZE*y+(CELLSIZE-size)/2;
    
    glPushMatrix();
    glTranslatef(xc, yc, 0);
    glBegin(GL_QUADS);
        
    /* BOTTOM */
    glNormal3d(0,0,-1);
    glVertex3d(        0,         0, 0); 
    glVertex3d(     size,         0, 0);
    glVertex3d(     size,      size, 0);
    glVertex3d(        0,      size, 0);

    /* REAR */
    glNormal3d(0,-1,0);
    glVertex3d(       0, 0,        0);
    glVertex3d(    size, 0,        0);
    glVertex3d(    size, 0,     size);
    glVertex3d(       0, 0,     size);

    /* RIGHT */
    glNormal3d(1,0,0);
    glVertex3d(    size,        0,        0);
    glVertex3d(    size,     size,        0);
    glVertex3d(    size,     size,     size);
    glVertex3d(    size,        0,     size);

    /* FRONT */
    glNormal3d(0,1,0);
    glVertex3d(       0,     size,        0);
    glVertex3d(    size,     size,        0);
    glVertex3d(    size,     size,     size);
    glVertex3d(       0,     size,     size);

    /* LEFT */
    glNormal3d(-1,0,0);
    glVertex3d(       0,        0,        0);
    glVertex3d(       0,     size,        0);
    glVertex3d(       0,     size,     size);
    glVertex3d(       0,        0,     size);

    /* TOP */
    glNormal3d(0,0,1);
    glVertex3d(       0,        0,     size);
    glVertex3d(       0,     size,     size);
    glVertex3d(    size,     size,     size);
    glVertex3d(    size,        0,     size);

    glEnd();
    glPopMatrix();
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
