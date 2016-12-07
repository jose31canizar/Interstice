// #include "parts.h"
#include "../setup/GL.h"
#include "../CSCIx229.h"
#include "../setup/textures.h" //texture array

void drawCylinder(double base, double height, double radius) {
        //column cylinder
        glPushMatrix();


        int inc = 30;
        int max = 360; //416

        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glBindTexture(GL_TEXTURE_2D,texture[6]);

        glColor4f(0.69, 0.31, 0.42, 0.0);

        glBegin(GL_TRIANGLE_STRIP);
        for (int i=0; i <  max; i+= inc)
        {
                // glColor4f(0.4, Cos((double)i), 0.2, 0.5);

                //bottom left
                glTexCoord2f((((double) i)/max), 0.0);
                glNormal3f(Cos(i)*radius,base,Sin(i)*radius);
                glVertex3f(Cos(i)*radius,base,Sin(i)*radius);

                //top left
                glTexCoord2f((((double) i)/max), 1.0);
                // printf("%f\n", (((double) i)/416.0));
                glNormal3f(Cos(i)*radius,base + height,Sin(i)*radius);
                glVertex3f(Cos(i)*radius,base + height,Sin(i)*radius);

                //flute effect
                //glNormal3f(Cos(i)*radius,base + height,Sin(i)*radius);

                //bottom right
                glTexCoord2f((((double) i + (double) inc)/max), 0.0);
                glNormal3f(Cos(i+inc)*radius,base,Sin(i+inc)*radius);
                glVertex3f(Cos(i+inc)*radius,base,Sin(i+inc)*radius);

                //top right
                glTexCoord2f((((double) i + (double) inc)/max), 1.0);
                glNormal3f(Cos(i+inc)*radius,base + height,Sin(i+inc)*radius);
                glVertex3f(Cos(i+inc)*radius,base + height,Sin(i+inc)*radius);
        }

        glEnd();
        glPopMatrix();

        glDisable(GL_TEXTURE_2D);
}



//draws a column
//x, y, z
//dx, dy, dz
//th
//height (h)
void circleFace(double height, double radius) {
        glPushMatrix();

        int inc = 30;
        int max = 390;

        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glBindTexture(GL_TEXTURE_2D,texture[6]);

        // glBegin(GL_TRIANGLE_STRIP);
        glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0.5, 0.5);
        glNormal3f(0,height,0);
        glVertex3f(0.0, height, 0.0);



        for (int i=0; i < max; i+= inc)
        {
                //glColor3f(0.548,0.2,0.7);
                //glColor3f(0.148,0.11,0.13);
                // glColor3f(0.4, Cos((double)i), 0.2);

                glTexCoord2f(0.5*Cos(i)+0.5,0.5*Sin(i)+0.5);

                glVertex3f(Cos(i)*radius,height,Sin(i)*radius);

                //glVertex3f(0.0, height, 0.0);
        }
        glEnd();
        glPopMatrix();

        glDisable(GL_TEXTURE_2D);
}

void drawClosedCylinder(double base, double height, double radius, double x, double y, double z) {
        glPushMatrix();
        glTranslated(x, y, z);
        circleFace(base, radius);
        drawCylinder(base, height, radius);
        circleFace(height, radius);
        glPopMatrix();
}

void drawCircle(float radius) {
        int inc = 20;
        glBegin(GL_LINE_LOOP);

        for (int i=0; i < 360; i+= inc)
        {
                glVertex2f(Cos(i)*radius,Sin(i)*radius);
        }

        glEnd();
}

void drawRect(float w, float h) {
        glPushMatrix();
        glRotated(90, 1, 0, 0);
        glBegin(GL_QUADS);
        glVertex2f(-w, h);
        glVertex2f(w, h);
        glVertex2f(w, -h);
        glVertex2f(-w, -h);
        glEnd();
        glPopMatrix();
}



//fraction of cycle: 1 = full, 0.5 half, etc.
void circle(double fraction, double flute_radius, double radius, double theta, double r, double g, double b, double x, double y, double z) {


        //bottom of first fascia
        //glBegin(GL_LINE_LOOP);

        for (int i=0; i < (int) (360*fraction); i++)
        {
                glColor3f(0.5,0.3,0.45);
                //double x1 = (((double) i)/114.6)*radius;
                double x1 = Cos(i)*flute_radius;
                double y1 = Sin(i)*flute_radius;
                //rotation about the origin
                // x′=xcos⁡θ−ysin⁡θ
                // y′=xsinθ+ycosθ
                double x2 = x1*Cos(theta + 90) - y1*Sin(theta + 90);
                double y2 = x1*Sin(theta + 90) + y1*Cos(theta + 90);
                //114.6
                glNormal3f(x2 + Cos(theta)*radius + x,y, y2 + Sin(theta)*radius + z);
                glVertex3f(x2 + Cos(theta)*radius + x,y, y2 + Sin(theta)*radius + z);

                //center of our wave or half-circle
                // if (i == (int) (360*fraction) - 1) {
                //         glColor3f(0.1, 0.6, 0.9);
                //         glVertex3f(Cos(theta),y,Sin(theta));
                // }
        }



        //glEnd();
}




//fraction of cycle: 1 = full, 0.5 half, etc.
void circle2(double fraction, double flute_radius, double radius, double theta, double r, double g, double b, double h1, double h2, double x, double z) {

        //bottom of first fascia
        //glBegin(GL_LINE_LOOP);

        for (int i=0; i < (int) (360*fraction); i++)
        {
                glColor3f(r,g,b);
                //double x1 = (((double) i)/114.6)*radius;
                double x1 = Cos(i)*flute_radius;
                double y1 = Sin(i)*flute_radius;
                //rotation about the origin
                // x′=xcos⁡θ−ysin⁡θ
                // y′=xsinθ+ycosθ
                double x2 = x1*Cos(theta + 90) - y1*Sin(theta + 90);
                double y2 = x1*Sin(theta + 90) + y1*Cos(theta + 90);
                //114.6
                glNormal3f(x2 + Cos(theta)*radius + x,h1, y2 + Sin(theta)*radius + z);
                glTexCoord2f(0, 0.5);
                glVertex3f(x2 + Cos(theta)*radius + x,h1, y2 + Sin(theta)*radius + z);

                //glNormal3f(x2 +Cos(theta)*radius + x,h2, y2 + Sin(theta)*radius + z);
                glTexCoord2f(0.5, 1);
                glVertex3f(x2 + Cos(theta)*radius + x,h2, y2 + Sin(theta)*radius + z);

                //center of our wave or half-circle
                // if (i == (int) (360*fraction) - 1) {
                //         glColor3f(0.1, 0.6, 0.9);
                //         glVertex3f(Cos(theta),y,Sin(theta));
                // }
        }

        glDisable(GL_TEXTURE_2D);

        //glEnd();
}


//flat outsides on flute
//fraction of cycle: 1 = full, 0.5 half, etc.
void circle3(double fraction, double flute_radius, double radius, double theta, double r, double g, double b, double h1, double h2, double x, double z) {

        //bottom of first fascia
        //glBegin(GL_LINE_LOOP);

        for (int i=0; i < (int) (360*fraction); i++)
        {
                if (i == 0 || i == (int) (360*fraction) - 1) {
                        glColor3f(r,g,b);
                        //double x1 = (((double) i)/114.6)*radius;
                        double x1 = Cos(i)*flute_radius;
                        double y1 = Sin(i)*flute_radius;
                        //rotation about the origin
                        // x′=xcos⁡θ−ysin⁡θ
                        // y′=xsinθ+ycosθ
                        double x2 = x1*Cos(theta + 90) - y1*Sin(theta + 90);
                        double y2 = x1*Sin(theta + 90) + y1*Cos(theta + 90);
                        //114.6
                        glNormal3f(x2 + Cos(theta)*radius + x,h1, y2 + Sin(theta)*radius + z);
                        glVertex3f(x2 + Cos(theta)*radius + x,h1, y2 + Sin(theta)*radius + z);

                        //glNormal3f(x2 + Cos(theta)*radius + x,h1, y2 + Sin(theta)*radius + z);
                        glVertex3f(x2 + Cos(theta)*radius + x,h2, y2 + Sin(theta)*radius + z);

                }


        }



        //glEnd();
}




//flat outsides between flutes
//fraction of cycle: 1 = full, 0.5 half, etc.
void circle4(double fraction, double flute_radius, double radius, double theta, double r, double g, double b, double h1, double h2, double x, double z) {




        for (int i=0; i < (int) (360*fraction); i++)
        {
                if (i == 0) {
                        glColor3f(r,g,b);
                        //double x1 = (((double) i)/114.6)*radius;
                        double x1 = Cos(i)*flute_radius;
                        double y1 = Sin(i)*flute_radius;
                        //rotation about the origin
                        // x′=xcos⁡θ−ysin⁡θ
                        // y′=xsinθ+ycosθ
                        double x2 = x1*Cos(theta + 90) - y1*Sin(theta + 90);
                        double y2 = x1*Sin(theta + 90) + y1*Cos(theta + 90);
                        //114.6
                        glNormal3f(x2 + Cos(theta)*radius + x,h1, y2 + Sin(theta)*radius + z);
                        glTexCoord2f(((double) i)/(360.0), 0.5);
                        glVertex3f(x2 + Cos(theta)*radius + x,h1, y2 + Sin(theta)*radius + z);

                        glVertex3f(x2 + Cos(theta)*radius + x,h2, y2 + Sin(theta)*radius + z);
                }
        }
        //glEnd();
}



//flat outsides between flutes
//fraction of cycle: 1 = full, 0.5 half, etc.
void circle5(double fraction, double flute_radius, double radius, double theta, double r, double g, double b, double h1, double h2, double x, double z) {


        for (int i=0; i < (int) (360*fraction); i++)
        {
                if (i == (int) (360*fraction) - 1) {
                        glColor3f(r,g,b);
                        //double x1 = (((double) i)/114.6)*radius;
                        double x1 = Cos(i)*flute_radius;
                        double y1 = Sin(i)*flute_radius;
                        //rotation about the origin
                        // x′=xcos⁡θ−ysin⁡θ
                        // y′=xsinθ+ycosθ
                        double x2 = x1*Cos(theta + 90) - y1*Sin(theta + 90);
                        double y2 = x1*Sin(theta + 90) + y1*Cos(theta + 90);
                        //114.6
                        glNormal3f(x2 + Cos(theta)*radius + x,h1, y2 + Sin(theta)*radius + z);
                        glVertex3f(x2 + Cos(theta)*radius + x,h1, y2 + Sin(theta)*radius + z);

                        glVertex3f(x2 + Cos(theta)*radius + x,h2, y2 + Sin(theta)*radius + z);
                }
        }
        //glEnd();
}



void circleFace_tex(double height, double radius, int tex) {
        glPushMatrix();

        int inc = 5;
        int max = 390;

        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glBindTexture(GL_TEXTURE_2D,texture[tex]);

        // glBegin(GL_TRIANGLE_STRIP);
        glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0.5, 0.5);
        glNormal3f(0,height,0);
        glVertex3f(0.0, height, 0.0);



        for (int i=0; i < max; i+= inc)
        {
                //glColor3f(0.548,0.2,0.7);
                //glColor3f(0.148,0.11,0.13);
                // glColor3f(0.4, Cos((double)i), 0.2);

                glTexCoord2f(0.5*Cos(i)+0.5,0.5*Sin(i)+0.5);

                glVertex3f(Cos(i)*radius,height,Sin(i)*radius);

                //glVertex3f(0.0, height, 0.0);
        }
        glEnd();
        glPopMatrix();

        glDisable(GL_TEXTURE_2D);
}
