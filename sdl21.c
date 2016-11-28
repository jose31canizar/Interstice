// For anything else but Mac
// #include <SDL/SDL.h>
// #include <SDL2/SDL_mixer.h>
// #ifdef USEGLEW
// #include <GL/glew.h>
// #endif
//  OpenGL with prototypes for glext
// #define GL_GLEXT_PROTOTYPES
// #ifdef __APPLE__
// #include <OpenGL/glew.h>
// #include <OpenGL/gl.h>
// #else
// #include <GL/glut.h>
// #endif
#include "setup/GL.h"
#include <stdio.h>
#include "objects/character.h"
#include "objects/floors.h"
#include "objects/parts.h"
// #include "objects/bezier.h"
#include "objects/jars.h"
// #include "objects/balusters.h"
#include "utility/randomizer.h"
#include "sdl21.h"
#include "math.h"
#include "utility/save_progress.h"
#include "setup/textures.h" //texture array
#include "setup/lighting.h" //lighting variables
#include "CSCIx229.h"
#include "utility/collision.h"

double start = 0.0;
int running = 1;

#define PI 3.14159265

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

double asp=1;     //  Aspect ratio
int fov=53;       //  Field of view (for perspective)
double dim=256;     //  Size of world
int th=0,ph=0;    //  View angles
int w = 0;
int h = 0;
double x = 0;
double y = 0;

//Main loop flag
int quit = 0;

//Starting Point
double Fx = -0.1;
double Fy = 0.0;
double Fz = -45.0;
double l = 0; //side to side camera
double u = 0;  //up
double dist = 0.2; //viewing distance
double init_dist = 0.2;

int balustrade_list;

int floor_tex = 0;
double floor_range = 1.0;

//Shadow
float N[] = {0, -1, 0}; // Normal vector for the plane
float E[] = {0, -2, 0 }; // Point of the plane

double wx = 0.0; //world x
double wy = 0.0;
double wz = 0.0;

double vector_x = 1.0;
double vector_z = 0.0;
int isMouseSelection = 0;
int xMouse = 0;
int yMouse = 0;
int clockwise = 0;

int xMouseBefore = 0;
int yMouseBefore = 0;
// double wr = 0.0; //icosa rotation

int grab = 0;

GLfloat BoxMat[16] = {0, 0, 0, 0,
                      0, 0, 0, 0,
                      0, 0, 0, 0,
                      0, 0, 0, 0};

double baluster_positions[16][3] = {{0, 0, 0},
                                    {0, 0, 0},
                                    {0, 0, 0},
                                    {0, 0, 0}, //
                                    {0, 0, 0},
                                    {0, 0, 0},
                                    {0, 0, 0},
                                    {0, 0, 0}, //
                                    {0, 0, 0},
                                    {0, 0, 0},
                                    {0, 0, 0},
                                    {0, 0, 0}, //
                                    {0, 0, 0},
                                    {0, 0, 0},
                                    {0, 0, 0},
                                    {0, 0, 0}};

//Starts up SDL and creates window
int init();

//Loads media
int loadMedia();

//Frees media and shuts down SDL
void SDL_close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gXOut = NULL;

void ShadowProjection(float L[4], float E[4], float N[4])
{
        float mat[16];
        float e = E[0]*N[0] + E[1]*N[1] + E[2]*N[2];
        float l = L[0]*N[0] + L[1]*N[1] + L[2]*N[2];
        float c = e - l;
        //  Create the matrix.
        mat[0] = N[0]*L[0]+c; mat[4] = N[1]*L[0];   mat[8]  = N[2]*L[0];   mat[12] = -e*L[0];
        mat[1] = N[0]*L[1];   mat[5] = N[1]*L[1]+c; mat[9]  = N[2]*L[1];   mat[13] = -e*L[1];
        mat[2] = N[0]*L[2];   mat[6] = N[1]*L[2];   mat[10] = N[2]*L[2]+c; mat[14] = -e*L[2];
        mat[3] = N[0];        mat[7] = N[1];        mat[11] = N[2];        mat[15] = -l;
        //  Multiply modelview matrix
        glMultMatrixf(mat);
}

void Vertex(double th,double ph)
{
        double x = Sin(th)*Cos(ph);
        double z = Cos(th)*Cos(ph);
        double y =         Sin(ph);
        //  For a sphere at the origin, the position
        //  and normal vectors are the same
        glNormal3d(x,y,z);
        glVertex3d(x,y,z);
}

/*
 *  Draw a ball
 *     at (x,y,z)
 *     radius (r)
 */
static void ball(double x,double y,double z,double r)
{
        int th,ph;
        float yellow[] = {1.0,1.0,0.0,1.0};
        float Emission[]  = {0.0,0.0,0.01*emission,1.0};
        //  Save transformation
        glPushMatrix();
        //  Offset, scale and rotate
        glTranslated(x,y,z);
        glScaled(r,r,r);
        //  White ball
        glColor3f(1,1,1);
        glMaterialf(GL_FRONT,GL_SHININESS,shiny);
        glMaterialfv(GL_FRONT,GL_SPECULAR,yellow);
        glMaterialfv(GL_FRONT,GL_EMISSION,Emission);
        //  Bands of latitude
        for (ph=-90; ph<90; ph+=ball_inc)
        {
                glBegin(GL_QUAD_STRIP);
                for (th=0; th<=360; th+=2*ball_inc)
                {
                        Vertex(th,ph);
                        Vertex(th,ph+ball_inc);
                }
                glEnd();
        }
        //  Undo transformations
        glPopMatrix();
}

void overlay()
{
        //  Screen edge
        float w = asp> 2 ? asp : 2;
        //  Save transform attributes (Matrix Mode and Enabled Modes)
        glPushAttrib(GL_TRANSFORM_BIT|GL_ENABLE_BIT);
        //  Save projection matrix and set unit transform
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glOrtho(-asp,+asp,-1,1,-1,1);
        //  Save model view matrix and set to identity
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        //Draw instrument panel
        glColor3f(1,1,1);
        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_MODULATE);


        //glBindTexture(GL_TEXTURE_2D,texture[8]);

        glBegin(GL_QUADS);
        glTexCoord2d(0,0); glVertex2f(-2,-1);
        glTexCoord2d(1,0); glVertex2f(+2,-1);
        glTexCoord2d(1,1); glVertex2f(+2, -0.9);
        glTexCoord2d(0,1); glVertex2f(-2, -0.9);
        glEnd();

        glColor3f(0.8,0.6,0.6);
        glBegin(GL_QUADS);
        //Top Bar
        glVertex2f(-2.0,1);
        glVertex2f(2.0,1);
        glVertex2f(2.0,0.9);
        glVertex2f(-2.0,0.9);
        glEnd();

        glBindTexture(GL_TEXTURE_2D,texture[10]);

        glBegin(GL_QUADS);
        glTexCoord2d(0.25,0.25); glVertex2f(-1.0,-1.0);
        glTexCoord2d(0.75,0.25); glVertex2f(-0.9,-1.0);
        glTexCoord2d(0.75,0.75); glVertex2f(-0.9, -0.9);
        glTexCoord2d(0.25,0.75); glVertex2f(-1.0, -0.9);
        glEnd();

        glDisable(GL_TEXTURE_2D);

        //  Reset model view matrix
        glPopMatrix();
        //  Reset projection matrix
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        //  Pop transform attributes (Matrix Mode and Enabled Modes)
        glPopAttrib();
}


/*
 *  Compile display list
 */
void compile()
{
        balustrade_list = glGenLists(1);
        glNewList(balustrade_list,GL_COMPILE);
        // balustrade(-wx + 300, wy, -wz + 200);
        balustrade(0.0, 0.0, 0.0);
        glEndList();
}


double sind(double angle)
{
        double angleradians = angle * M_PI / 180.0f;
        return sin(angleradians) * M_PI / 180.0f;
}


int loadMedia()
{
        //Load texture images
        char file[80];
        //Loading success flag
        int success = 1;

        //int i = 0;
        for(int i = 0; i < 11; i+= 1) {
                if (i <= 3) {
                        sprintf(file, "images/marble_%d.bmp", i+1);
                        printf("images/marble_%d.bmp\n", i+1);
                        //texture[i] = LoadTexBMP(file);
                } else if( i <= 9) {
                        sprintf(file, "images/wood_%d.bmp", i+1);
                        printf("images/wood_%d.bmp\n", i+1);
                        //texture[i] = LoadTexBMP(file);
                } else {
                        sprintf(file, "images/icon_%d.bmp", i+1);
                        printf("images/icon_%d.bmp\n", i+1);

                }

                texture[i] = LoadTexBMP(file);

                if (texture[i] == NULL) {
                        printf( "Unable to load image %d! SDL Error: %s\n", i+1, SDL_GetError() );
                        success = 0;
                }

        }

        return success;
}

void SDL_close()
{
        //Deallocate surface
        SDL_FreeSurface( gXOut );
        gXOut = NULL;

        //Destroy window
        SDL_DestroyWindow( gWindow );
        gWindow = NULL;

        //Quit SDL subsystems
        SDL_Quit();
}

void handleEvent( SDL_Event* e )
{
        double Rx = Sin(th)*dist;
        //double Ry = u;
        double Rz = Cos(th)*dist;

        Uint8* keystate = SDL_GetKeyboardState(NULL);
        // Uint8* keystate = 0;

        if (keystate[SDL_SCANCODE_W]) {
                wz += -5.0*Rz*(init_dist/(dist*dist));
                wx += 5.0*Rx*(init_dist/(dist*dist));
                status.wr += 10;
                status.wr = fmod(status.wr, 360.0);
                status.vx = vector_x;
                status.vz = vector_z;
                //cos((double) th * PI/180.0)
                // printf("th: %d , Cos(th): %f ", th, Cos((double)th));

        } else if (keystate[SDL_SCANCODE_A]) {
                wx -= 5.0*Rz*(init_dist/(dist*dist));
                wz -= 5.0*Rx*(init_dist/(dist*dist));


        } else if (keystate[SDL_SCANCODE_S]) {
                wz += 5.0*Rz*(init_dist/(dist*dist));
                wx += -5.0*Rx*(init_dist/(dist*dist));

                status.wr -= 10;
                status.wr = fmod(status.wr, 360.0);
                status.vx = vector_x;
                status.vz = vector_z;

        } else if (keystate[SDL_SCANCODE_D]) {
                wx += 5.0*Rz*(init_dist/(dist*dist));
                wz += 5.0*Rx*(init_dist/(dist*dist));

        } else if (keystate[SDL_SCANCODE_Z]) {
                //quit game
                dist += 0.1;

        } else if (keystate[SDL_SCANCODE_X]) {
                //quit game
                if (dist >= init_dist)
                        dist -= 0.1;
        } else if (keystate[SDL_SCANCODE_2]) {

                save_progress(&baluster_positions);

        } else if (keystate[SDL_SCANCODE_3]) {

                if(running) {
                        running = 0;
                } else {
                        running = 1;
                }


        } else if (keystate[SDL_SCANCODE_ESCAPE]) {
                //quit game
                quit = 1;

        }

        //Window event occurred
        if( (*e).type == SDL_WINDOWEVENT )
        {
                Sint32 width;
                Sint32 height;
                switch( (*e).window.event )
                {
                //Get new dimensions and repaint on window size change
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                        width = (*e).window.data1;
                        height = (*e).window.data2;
                        reshape(width, height);
                        break;
                } //arrow keys
        } else if ((*e).type == SDL_KEYDOWN) {
                switch( (*e).key.keysym.sym)
                {
                case SDLK_UP:
                        if(ph < 90)
                                ph += 5.0;
                        break;

                case SDLK_DOWN:
                        if(ph > 0)
                                ph -= 5.0;
                        break;

                case SDLK_LEFT:
                        th -= 5.0;
                        vector_x = Cos((double)th);
                        vector_z = Sin((double)th);
                        status.vx = vector_x;
                        status.vz = vector_z;
                        //printf("vector_z: %f , Sin((double)th): %f ", vector_z, Sin((double)th));
                        break;

                case SDLK_RIGHT:
                        th += 5.0;
                        vector_x = Cos((double)th);
                        vector_z = Sin((double)th);
                        status.vx = vector_x;
                        status.vz = vector_z;
                        break;
                case SDLK_g:
                        grab = 1;
                        break;
                default:
                        break;
                }
                //  Keep angles to +/-360 degrees
                th %= 360;
                ph %= 360;
        } else if ((*e).type == SDL_MOUSEBUTTONDOWN) {
                switch( (*e).button.button) {
                case SDL_BUTTON_LEFT:
                        isMouseSelection = 1;

                default:
                        break;
                }
        } else if ((*e).type == SDL_KEYUP) {
                switch( (*e).key.keysym.sym) {
                case SDLK_g:
                        grab = 0;
                        break;
                default:
                        break;
                }
        } else if ((*e).type == SDL_MOUSEBUTTONUP) {
                switch( (*e).button.button) {
                case SDL_BUTTON_LEFT:
                        isMouseSelection = 0;
                        break;
                default:
                        break;
                }
        } else if ((*e).type == SDL_MOUSEMOTION) {

                Uint8* mousestate = SDL_GetMouseState(&xMouse, &yMouse);
                int direction = 0;

                switch(isMouseSelection) {
                case 1:
                        //horizontal or vertical

                        if (abs(yMouse - yMouseBefore) > abs(xMouse - xMouseBefore)) {
                                direction = 0;
                        } else {
                                direction = 1;
                        }

                        if (direction == 1) {
                                if (xMouse < xMouseBefore) {
                                        // clockwise = 1;
                                        th -= ((*e).motion.x)*0.025;
                                } else if (xMouse >= xMouseBefore) {
                                        // clockwise = 0;
                                        th += ((*e).motion.x)*0.025;
                                }
                        } else {
                                if (yMouse < yMouseBefore) {
                                        ph -= ((*e).motion.y)*0.021;
                                } else if (yMouse >= yMouseBefore) {
                                        ph += ((*e).motion.y)*0.021;
                                }
                        }
                        // if (clockwise) {
                        //         th += ((*e).motion.x)*0.005 + ((*e).motion.y)*0.005;
                        // } else {
                        //         th -= ((*e).motion.x)*0.005 + ((*e).motion.x)*0.005;
                        // }

                        th %= 360;
                        break;
                case 0:
                        break;
                default:
                        break;
                }
                xMouseBefore = xMouse;
                yMouseBefore = yMouse;
        }

        Project(fov, asp, dim);
}
void Project(double fov,double asp,double dim)
{
        //  Tell OpenGL we want to manipulate the projection matrix
        glMatrixMode(GL_PROJECTION);
        //  Undo previous transformations
        glLoadIdentity();
        //  Perspective transformation
        gluPerspective(100,asp,0.1,8*dim);
        //gluPerspective(fov,asp,dim/4,4*dim);
        //  Orthogonal transformation
        glMatrixMode(GL_MODELVIEW);
        //  Undo previous transformations
        glLoadIdentity();
}

int reshape(int width,int height)
{
        // SDL_Rect r;
        // r.x = 50 + x;
        // r.y = 50 + y;
        // r.w = 50;
        // r.h = 50;
        //const double dim=2.5;
        //  Ratio of the width to the height of the window
        asp = (height>0) ? (double)width/height : 1;
        //  Set the viewport to the entire window
        glViewport(0,0, width,height);
        //  Update projection
        Project(fov,asp,dim);
        //Project();
        return 0;
}
void axes(double len) {

        glColor3f(0.8, 0.25, 0.1);
        glLineWidth(5.0);
        glBegin(GL_LINE_STRIP);
        glVertex3d(0.0,0.0,0.0);
        glVertex3d(len,0.0,0.0);
        glVertex3d(0.0,0.0,0.0);
        glVertex3d(0.0,len,0.0);
        glVertex3d(0.0,0.0,0.0);
        glVertex3d(0.0,0.0,len);

        glEnd();
}
//
// void initBoxMat() {
//         for (int i = 0; i < 16; i++) {
//                 strcpy(BoxMat[i], 1.0);
//         }
// }

int display()
{

        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        //  Enable Z-buffer depth test
        glEnable(GL_DEPTH_TEST);

        //  Reset transformations
        glLoadIdentity();






        //double s = 0.05;
        //glScaled(s,s,s);

        // Set render color to blue ( background will be rendered in this color )
        SDL_SetRenderDrawColor( gRenderer, 0, 0, 255, 255 );
        // Clear window
        SDL_RenderClear( gRenderer );

        double Fx = -1*dim*Sin((double)th)*Cos(ph);
        double Fy = +1*dim        *Sin(ph);
        double Fz = +1*dim*Cos((double)th)*Cos(ph);
        //from where your eye is looking at
        gluLookAt(Fx*dist,Fy*dist,Fz*dist, 0.0,0.0,0.0, 0,Cos(ph),0);

        // drawCircle(20.0);
        glPushMatrix();
        glRotated(-th, 0, 1, 0);
        glRotated(90, 1, 0, 0);
        // drawRect(15.0, 15.0);
        glPopMatrix();
        glColor3f(0.16, 0.59, 0.54);
        glLineWidth(100.0);
        // glScaled(20.0, 20.0, 20.0);
        axes(200.0);

        glColor3f(0.96, 0.68, 0.81);

        //floor
        cube(-wx, wy, -wz, 800.0, 0.0, 800.0, 0.0, 0.85, 0.75, 0.81, floor_tex, floor_range);





        // glBegin(GL_LINE_STRIP);
        // glVertex3f(0, 0, 0);
        // glVertex3f(5.0*Fz, 0.0, -5.0*Fx);
        // glEnd();

        //Light ball
        glPushMatrix();
        glTranslated(-wx, wy, -wz);

        //Lighting
        glShadeModel(GL_SMOOTH);

        // printf("%f", start);
        zh = fmod(90*start,360.0);

        //  Translate intensity to color vectors
        float Ambient[]   = {0.01*ambient,0.01*ambient,0.01*ambient,1.0};
        float Diffuse[]   = {0.01*diffuse,0.01*diffuse,0.01*diffuse,1.0};
        float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
        //  Light position
        float Position[]  = {distance*Cos(zh),ylight,distance*Sin(zh),1.0};
        //  Draw light position as ball (still no lighting here)
        glColor3f(1,1,1);
        ball(Position[0],Position[1],Position[2], 5.0);
        //  OpenGL should normalize normal vectors
        glEnable(GL_NORMALIZE);
        //  Enable lighting
        glEnable(GL_LIGHTING);
        //  Location of viewer for specular calculations
        glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,local);
        //  glColor sets ambient and diffuse color materials
        glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL);
        //  Enable light 0
        glEnable(GL_LIGHT0);
        //  Set ambient, diffuse, specular components and position of light 0
        glLightfv(GL_LIGHT0,GL_AMBIENT,Ambient);
        glLightfv(GL_LIGHT0,GL_DIFFUSE,Diffuse);
        glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
        glLightfv(GL_LIGHT0,GL_POSITION,Position);

        glPopMatrix();

        glPushMatrix();
        glColor3f(0.9, 0.4, 0.5);
        glTranslated(0.0, 8.0, 0.0);

        // glEnable(GL_LINE_SMOOTH);

        // glEnable(GL_POLYGON_SMOOTH);
        // glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

        // glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
        // glLineWidth(1.5);

        character(0.0, 0.0, 0.0, &status, &BoxMat, texture);
        glPopMatrix();



        glPushMatrix();
        glTranslated(-wx, wy, -wz);
        glCallList(balustrade_list);
        glPopMatrix();





        draw_balusters(wx, wy, wz);
        //glEnable(GL_POLYGON_OFFSET_FILL);
        //glPolygonOffset(1,1);
        generate_scene_with_collision(&baluster_positions, -wx, wy, -wz, th, grab);
        // glDisable(GL_POLYGON_OFFSET_FILL);


        // //Shadows
        // glPushAttrib(GL_ENABLE_BIT);
        //
        // glDisable(GL_LIGHTING);
        // //  Enable stencil operations
        // glEnable(GL_STENCIL_TEST);
        //
        // /*
        //  *  Step 1:  Set stencil buffer to 1 where there are shadows
        //  */
        // //  Existing value of stencil buffer doesn't matter
        // glStencilFunc(GL_ALWAYS,1,0xFFFFFFFF);
        // //  Set the value to 1 (REF=1 in StencilFunc)
        // //  only if Z-buffer would allow write
        // glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
        // //  Make Z-buffer and color buffer read-only
        // glDepthMask(0);
        // glColorMask(0,0,0,0);
        // //  Draw flattened scene
        // glPushMatrix();
        // ShadowProjection(Position,E,N);
        // generate_scene_with_collision(&baluster_positions, -wx, wy, -wz, th);
        // glPopMatrix();
        // //  Make Z-buffer and color buffer read-write
        // glDepthMask(1);
        // glColorMask(1,1,1,1);
        //
        // /*
        //  *  Step 2:  Draw shadow masked by stencil buffer
        //  */
        // //  Set the stencil test draw where stencil buffer is > 0
        // glStencilFunc(GL_LESS,0,0xFFFFFFFF);
        // //  Make the stencil buffer read-only
        // glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
        // //  Enable blending
        // glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        // glColor4f(0,0,0,0.5);
        // //  Draw the shadow over the entire floor
        // cube(-wx, wy, -wz, 800.0, 0.0, 800.0, 0.0, 0.85, 0.75, 0.81, floor_tex, floor_range);
        //
        //
        // //  Undo glEnables
        // glPopAttrib();






        glDisable(GL_DEPTH_TEST);



        glDisable(GL_LIGHTING);



        glDisable(GL_NORMALIZE);



        overlay();


        glFlush();
        return 0;
}

int main( int argc, char* args[] )
{
        //Initialization flag
        int success = 1;
        SDL_Event *event;

        //Initialize SDL
        if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
        {
                printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
                success = 0;
        }
        else
        {
                //Use OpenGL 2.1
                SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
                SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );

                // SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
                // SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
                // SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
                // SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
                // SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
                //Create window
                gWindow = SDL_CreateWindow( "Interstice", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN |  SDL_WINDOW_RESIZABLE);
                if( gWindow == NULL )
                {
                        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
                        success = 0;
                }
                else
                {
                }
        }


        //Create renderer for window
        gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
        if( gRenderer == NULL )
        {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = 0;
        }
        else
        {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        }

        if( success == 0 )
        {
                printf( "Failed to initialize!\n" );
        }
        else
        {
                //Load media
                if( !loadMedia() )
                {
                        printf( "Failed to load media!\n" );
                }
                else
                {

                        loadMedia();

                        //compile balustrade
                        compile();

                        load_progress(&baluster_positions);

                        //Event handler
                        SDL_Event e;

                        //While application is running



                        while( !quit )
                        {
                                if(running) {
                                        start = SDL_GetTicks()/1000.0;
                                }

                                //Handle events on queue
                                while( SDL_PollEvent( &e ) != 0 )
                                {
                                        //User requests quit
                                        if( e.type == SDL_QUIT )
                                        {
                                                quit = 1;
                                        }
                                        event = &e;
                                        handleEvent(event);
                                }
                                display();
                                SDL_RenderPresent( gRenderer );
                        }
                }
        }

        //Free resources and close SDL
        SDL_close();

        return 0;
}
