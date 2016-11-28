#include "../setup/GL.h"
#include "../CSCIx229.h"
#include "parts.h"

void column(double x,double y,double z,
            double dx,double dy,double dz,
            double th, double h) {
        glPushMatrix();
        //  Offset
        glTranslated(x,y,z);
        glRotated(th,0,1,0);
        glScaled(dx,dy,dz);

        //  Enable textures
        // glEnable(GL_TEXTURE_2D);
        // glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glColor3f(1,1,1);

        // glBindTexture(GL_TEXTURE_2D,texture[4]);


        int i;
        float radius = 0.2;
        float height = h;

        //top and bottom of main column
        circleFace(0, radius);
        circleFace(height, radius);
        //cylinder of main columns
        drawCylinder(0, height, radius);

        // glBindTexture(GL_TEXTURE_2D,texture[1]);

        //top fascia
        for(i = 0; i < 3; i++) {
                float h0 = height + i*0.05;
                float h = 0.1; //height of each fascia is constant
                float r = radius + (height/(40.0))*i*i*1.0; //quadratic
                circleFace(h0, r);
                drawCylinder(h0, h, r);
        }
        //bottom fascia
        for(i = 3; i >= 0; i--) {
                float h0 = -i*0.05;
                float h = 0.1; //height of each fascia is constant
                float r = radius + (height/(40.0))*(i+1)*1.0; //linear
                circleFace(h0, r);
                drawCylinder(h0, -h, r);
        }
        //  Undo transformations
        glPopMatrix();
}

//draws a fluted column
void column2(double x,double y,double z,
             double dx,double dy,double dz,
             double th) {
        glPushMatrix();
        //  Offset
        glTranslated(x,y,z);
        glRotated(th,0,1,0);
        glScaled(dx,dy,dz);

        //  Enable textures
        // glEnable(GL_TEXTURE_2D);
        // glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_MODULATE);
        //glColor3f(1,1,1);

        // glBindTexture(GL_TEXTURE_2D,texture[2]);

        const float DEG2RAD = 3.14159/180;
        int i;
        float radius = 0.2;
        float height = 2.5;

        int colRate = 4;

        //bottom of fluted column
        circleFace(0, radius);

        //top of fluted column
        circleFace(height, radius);

        //top fascia
        for(i = 0; i < 3; i++) {
                float h0 = height + i*0.05;
                float h = 0.1; //height of each fascia is constant
                float r = radius + (height/(40.0))*i*i*1.0; //quadratic
                circleFace(h0, r);
                drawCylinder(h0, h, r);
        }
        //bottom fascia
        for(i = 3; i >= 0; i--) {
                float h0 = -i*0.05;
                float h = 0.1; //height of each fascia is constant
                float r = radius + (height/(40.0))*(i+1)*1.0; //linear
                circleFace(h0, r);
                drawCylinder(h0, -h, r);
        }

        //  Undo transformations
        glPopMatrix();
}
