#include <SDL/SDL.h>
#include <math.h>

#define GL_GLEXT_PROTOTYPES
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdbool.h>

const char * VertexShaderSource = "uniform float time; /* in milliseconds */  \
                             void main()				\
                             {						\
                                 vec4 t = gl_Vertex;			\
                                 t.y = 0.1*sin(0.001*time + 5.0*gl_Vertex.x)* \
                                 sin(0.001*time+5.0*gl_Vertex.z); \
                                 gl_Position = gl_ModelViewProjectionMatrix * t; \
                                 gl_FrontColor = gl_Color;		\
                             }";

const char * FragmentShaderSource = "void main(void) \
{						\
    gl_FragColor = vec4 (1.0, 0.34, 0.34, 0.0); \
}";

SDL_Surface *Display;
bool Running = true;

float time = 0;
GLint timeindex;

int init(void);
void event(SDL_Event *);
void loop(void);
void render(void);
void cleanup(void);

void cube(int x, int y, int z, int size);

void keyDown(SDLKey, SDLMod, Uint16);

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    SDL_Event Event;
    int err;
    if ((err = init())) return err;
    while (Running) {
	while (SDL_PollEvent(&Event)) {
	    event(&Event);
	}
	loop();
	render();
	SDL_Delay(50);
    }
    printf("Cleaning up... ");
    cleanup();
    printf("Good bye!\n");
    return 0;
}

int init(void)
{

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) return 1;

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,            8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,          8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,           8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,          8);

    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,          16);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,         32);

    SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,      8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,    8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,     8);
    SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,    8);

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  0);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  0);

    if ((Display = SDL_SetVideoMode(600, 600, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL)) == NULL) return 2;

    /*-----------------------------------------------------------------------------------*/
    GLfloat light_position[] = { 0.0, 0.0, 3.0, 0.0 };
    GLfloat amb[]  = { 0.0, 0.3, 0.3, 0.7 };

    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv( GL_LIGHT0, GL_AMBIENT , amb  );
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);


    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    
    glMatrixMode(GL_PROJECTION);
    gluPerspective(50,1,0.1,600);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,120,0,0,0,-1,0,0);    
    glColor3f(0.7, 0.3, 0.1);

    
    /*-----------------------------------------------------------------------------------*/
    GLuint VertexShaderObject, FragmentShaderObject;

    VertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
    FragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(VertexShaderObject, 1, &VertexShaderSource, 0);
    glShaderSource(FragmentShaderObject, 1, &FragmentShaderSource, 0);

    glCompileShader(VertexShaderObject);
    glCompileShader(FragmentShaderObject);

    GLint compiled;
    glGetShaderiv(VertexShaderObject, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
	printf("Vertex shader failed compiling\n");
	return 3;
    }

    glGetShaderiv(FragmentShaderObject, GL_COMPILE_STATUS, &compiled);
    if (!compiled) {
	printf("Fragment shader failed compiling\n");
	return 4;
    }

    GLuint Program = glCreateProgram();
    glAttachShader(Program, VertexShaderObject);
    glAttachShader(Program, FragmentShaderObject);

    timeindex = glGetUniformLocation(Program, "time");

    glLinkProgram(Program);
    GLint linked;
    glGetProgramiv(Program, GL_LINK_STATUS, &linked);
    if (!linked) {
	printf("Program failed linking\n");
	return 5;
    }
    
    glUseProgram(Program);
    return 0;
}

void render(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     glUniform1f(timeindex, time);
     printf("time: %f\n", time);
     cube(300-120,300-120,0,240); 
     //     glutSolidTeapot(25); 
     SDL_GL_SwapBuffers();
}

void event(SDL_Event *Event)
{
    switch (Event->type) {
    case SDL_KEYDOWN: {
        keyDown(Event->key.keysym.sym,Event->key.keysym.mod,Event->key.keysym.unicode);
        break;
    }
    case SDL_QUIT: {
        Running = false;
        break;
    }
    default:
        break;
    }
}

void keyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
    switch (sym) {
    case SDLK_ESCAPE: { //ESC
	Running = false;
	break;
    }
    default: break;
    }
}

void loop(void)
{
    time += 75;
    if (time > 8000000000) time = 0;
}

void cleanup(void)
{
    SDL_FreeSurface(Display);
    SDL_Quit();
}

void cube(int x, int y, int z, int size)
{
    int i,j, N=198;
    float data[200][200];
    for(i=0;i<N;i++) for(j=0;j<N;j++) data[i][j]=sin(i)*cos(j)*500;

    glBegin(GL_LINE_LOOP);
    glVertex3f((float)i/N*100, data[i][j], (float)j/N*100);
    glVertex3f((float)i/N*100, data[i][j+1], (float)(j+1)/N*100);
    glVertex3f((float)(i+1)/N*100, data[i+1][j+1], (float)(j+1)/N*100);
    glVertex3f((float)(i+1)/N*100, data[i+1][j], (float)(j)/N*100);
    glEnd();
}
