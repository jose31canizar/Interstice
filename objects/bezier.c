#include "../setup/GL.h"
#include "../CSCIx229.h"
#include "../setup/textures.h" //texture array

double bezier_x(double x1, double x2, double x3, double x4, double t) {
        double x = (1 - t)*(1 - t)*(1 - t)*x1 + 3*t*(1 - t)*(1 - t)*x2 + 3*t*t*(1 - t)*x3 + t*t*t*x4;
        return x;
}

double bezier_y(double y1, double y2, double y3, double y4, double t) {
        double y = (1 - t)*(1 - t)*(1 - t)*y1 + 3*t*(1 - t)*(1 - t)*y2 + 3*t*t*(1 - t)*y3 + t*t*t*y4;
        return y;
}

double inc = 36;

/*
 *  Draw vertex in polar coordinates with normal
 */
static void Sphere_Vertex(double th,double ph)
{
        // double x = th*0.0027*Cos(ph);
        double x = Sin(th)*Cos(ph);
        double y = Cos(th)*Cos(ph);
        double z =         Sin(ph);
        //  For a sphere at the origin, the position
        //  and normal vectors are the same
        glNormal3d(x,y,z);
        glVertex3d(x,y,z);
}

// static void Cylinder_Vertex(double th,double ph)
// {
//         double x = Sin(th)*Cos(ph);
//         double y = Cos(ph);
//         double z =         Sin(ph);
//         //  For a sphere at the origin, the position
//         //  and normal vectors are the same
//         glNormal3d(x,y,z);
//         glVertex3d(x,y,z);
// }

// draw bezier curve
//f determines size (10.0 makes curve smaller compared to putting in 1.0)
//x, y, z position
void bezier_curve(double f, double x, double y, double z, double *curve) {

        glBegin(GL_LINE_STRIP);
        int i;

        for(i = 0; i < 10; i++) {
                // glScaled(20.0, 20.0, 20.0);
                glVertex3f(bezier_x(curve[0]/f, curve[1]/f, curve[2]/f, curve[3]/f, i/10.0) + x,bezier_y(curve[4]/f, curve[5]/f, curve[6]/f, curve[7]/f, i/10.0) + y,z);
        }
        glEnd();
}

void baluster(double f, double s, double x, double y, double z, double *curve) {
        glPushMatrix();
        glTranslated(x,y,z);
        glScaled(s, s, s);
        int i;
        int j;
        int inc = 30; //number of vertices
        double range = 0.3;
        double shift = -1.0; //starting point shift: -1, range: 2 = -1 to 1
        double angle = 0;
        double hMax = 60.0;

        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glBindTexture(GL_TEXTURE_2D,texture[6]);

        glColor3f(1,0.8,0.8);

        for(i = 0; i < 360; i+= inc) {
                double nx = bezier_x(curve[0]/f, curve[1]/f, curve[2]/f, curve[3]/f, ((double)i)/360.0);
                double ny = bezier_y(curve[4]/f, curve[5]/f, curve[6]/f, curve[7]/f, ((double)i)/360.0);
                double nx1 = bezier_x(curve[0]/f, curve[1]/f, curve[2]/f, curve[3]/f, ((double)i+inc)/360.0);
                double ny1 = bezier_y(curve[4]/f, curve[5]/f, curve[6]/f, curve[7]/f, ((double)i+inc)/360.0);

                for(j = 0; j < 360; j+= inc) {
                        // glBegin(GL_TRIANGLE_STRIP);
                        glBegin(GL_QUADS);

                        //printf("ny1: %f\n", ny1);

                        angle = (double) j;
                        // glColor3f(0.4, Cos(angle), Sin((double)i));
                        //bottom left
                        glTexCoord2f(((double) j)/(360.0/range) + shift, (((double) ny)*(360.0/hMax))/(360.0/range) + shift);
                        glNormal3f(nx*Cos(angle),ny,nx*Sin(angle));
                        glVertex3f(nx*Cos(angle),ny,nx*Sin(angle));
                        //glTexCoord2f(0,0);
                        //printf("%f\n", ((double) j)/(360.0/range) + shift);
                        //top left
                        glTexCoord2f(((double) j)/(360.0/range) + shift, (((double) ny1)*(360.0/hMax))/(360.0/range) + shift);
                        glNormal3f(nx1*Cos(angle),ny1,nx1*Sin((angle)));
                        glVertex3f(nx1*Cos(angle),ny1,nx1*Sin((angle)));
                        // glTexCoord2f(0,1);
                        //top right
                        glTexCoord2f(((double) j + ((double) inc))/(360.0/range) + shift, (((double) ny1)*(360.0/hMax))/(360.0/range) + shift);
                        glNormal3f(nx1*Cos((angle + (double) inc)),ny1,nx1*Sin((angle + (double) inc)));
                        glVertex3f(nx1*Cos((angle + (double) inc)),ny1,nx1*Sin((angle + (double) inc)));
                        // glTexCoord2f(1,1);
                        //bottom right
                        glTexCoord2f(((double) j + ((double) inc))/(360.0/range) + shift, (((double) ny)*(360.0/hMax))/(360.0/range) + shift);
                        glNormal3f(nx*Cos((angle + (double) inc)),ny,nx*Sin((angle + (double) inc)));
                        glVertex3f(nx*Cos((angle + (double) inc)),ny,nx*Sin((angle + (double) inc)));
                        // glTexCoord2f(1,0);

                        glEnd();
                }
        }
        glPopMatrix();

        glDisable(GL_TEXTURE_2D);
}


void sphere(double th, double ph, double *curve) {
        glPushMatrix();
        glTranslated(0.0, 25.0, 0.0);
        glScaled(10.0, 10.0, 10.0);
        for (ph=-90; ph<0; ph+=inc)
        {
                glBegin(GL_QUAD_STRIP);
                glColor3f((ph+90)*0.0055, (ph+90)*0.0055, (ph+90)*0.0055);
                for (th=0; th<=360; th+=2*inc)
                {

                        Sphere_Vertex(th,ph);
                        Sphere_Vertex(th,ph+inc);
                }
                glEnd();

        }
        glPopMatrix();
}

void pentago(double th, double ph, double wx, double wy, double wz) {
        glPushMatrix();
        glTranslated(wx, wy, wz);
        glScaled(10.0, 10.0, 10.0);
        for (ph=-90; ph<90; ph+=inc)
        {
                glBegin(GL_QUAD_STRIP);
                glColor3f((ph+90)*0.0055, (ph+90)*0.0055, (ph+90)*0.0055);
                for (th=0; th<=360; th+=2*inc)
                {
                        Sphere_Vertex(th,ph);
                        Sphere_Vertex(th,ph+inc);
                }
                glEnd();

        }
        glPopMatrix();
}



void baluster_tex(double f, double s, double x, double y, double z, double *curve, int tex) {
        glPushMatrix();
        glTranslated(x,y,z);
        glScaled(s, s, s);
        int i;
        int j;
        int inc = 30; //number of vertices
        double range = 0.3;
        double shift = -1.0; //starting point shift: -1, range: 2 = -1 to 1
        double angle = 0;
        double hMax = 60.0;

        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glBindTexture(GL_TEXTURE_2D,texture[tex]);

        glColor3f(1,0.8,0.8);

        for(i = 0; i < 360; i+= inc) {
                double nx = bezier_x(curve[0]/f, curve[1]/f, curve[2]/f, curve[3]/f, ((double)i)/360.0);
                double ny = bezier_y(curve[4]/f, curve[5]/f, curve[6]/f, curve[7]/f, ((double)i)/360.0);
                double nx1 = bezier_x(curve[0]/f, curve[1]/f, curve[2]/f, curve[3]/f, ((double)i+inc)/360.0);
                double ny1 = bezier_y(curve[4]/f, curve[5]/f, curve[6]/f, curve[7]/f, ((double)i+inc)/360.0);

                for(j = 0; j < 360; j+= inc) {
                        // glBegin(GL_TRIANGLE_STRIP);
                        glBegin(GL_QUADS);

                        //printf("ny1: %f\n", ny1);

                        angle = (double) j;
                        // glColor3f(0.4, Cos(angle), Sin((double)i));
                        //bottom left
                        glTexCoord2f(((double) j)/(360.0/range) + shift, (((double) ny)*(360.0/hMax))/(360.0/range) + shift);
                        glNormal3f(nx*Cos(angle),ny,nx*Sin(angle));
                        glVertex3f(nx*Cos(angle),ny,nx*Sin(angle));
                        //glTexCoord2f(0,0);
                        //printf("%f\n", ((double) j)/(360.0/range) + shift);
                        //top left
                        glTexCoord2f(((double) j)/(360.0/range) + shift, (((double) ny1)*(360.0/hMax))/(360.0/range) + shift);
                        glNormal3f(nx1*Cos(angle),ny1,nx1*Sin((angle)));
                        glVertex3f(nx1*Cos(angle),ny1,nx1*Sin((angle)));
                        // glTexCoord2f(0,1);
                        //top right
                        glTexCoord2f(((double) j + ((double) inc))/(360.0/range) + shift, (((double) ny1)*(360.0/hMax))/(360.0/range) + shift);
                        glNormal3f(nx1*Cos((angle + (double) inc)),ny1,nx1*Sin((angle + (double) inc)));
                        glVertex3f(nx1*Cos((angle + (double) inc)),ny1,nx1*Sin((angle + (double) inc)));
                        // glTexCoord2f(1,1);
                        //bottom right
                        glTexCoord2f(((double) j + ((double) inc))/(360.0/range) + shift, (((double) ny)*(360.0/hMax))/(360.0/range) + shift);
                        glNormal3f(nx*Cos((angle + (double) inc)),ny,nx*Sin((angle + (double) inc)));
                        glVertex3f(nx*Cos((angle + (double) inc)),ny,nx*Sin((angle + (double) inc)));
                        // glTexCoord2f(1,0);

                        glEnd();
                }
        }
        glPopMatrix();

        glDisable(GL_TEXTURE_2D);
}
