#include "../setup/GL.h"
#include "../CSCIx229.h"
#include "parts.h"
#include "balusters.h"
#include "../setup/textures.h" //texture array


void column(double sx, double sy, double sz, double h) {
        glPushMatrix();
        //  Offset
        //glTranslated(x,y,z);
        //glRotated(th,0,1,0);
        glScaled(sx,sy,sz);

        glColor3f(1,1,1);

        // glBindTexture(GL_TEXTURE_2D,texture[4]);

        float radius = 1.5;
        float height = h;

        //top and bottom of main column
        circleFace(0, radius);
        circleFace(height, radius);
        //cylinder of main columns
        drawCylinder(0, height, radius);

        // glBindTexture(GL_TEXTURE_2D,texture[1]);

        circleFace(0.0, 2.0);

        //top fascia
        // for(i = 0; i < 3; i++) {
        //         float h0 = height + i*0.5;
        //         float h = 1.0; //height of each fascia is constant
        //         float r = radius + (height/(40.0))*(i+1)*1.0; //linear
        //         // float r = radius + (height/(40.0))*i*i*1.0; //quadratic
        //         circleFace(h0, r);
        //         drawCylinder(h0, h, r);
        // }
        //bottom fascia
        // for(i = 3; i >= 0; i--) {
        //         float h0 = -i*0.5;
        //         float h = 1.0; //height of each fascia is constant
        //         float r = radius + (height/(40.0))*(i+1)*1.0; //linear
        //         // float r = radius + (height/(40.0))*i*i*1.0; //quadratic
        //         circleFace(h0, r);
        //         drawCylinder(h0, -h, r);
        // }
        //  Undo transformations
        glPopMatrix();


}


// fr//radius of flutes
// r //radius of whole column
// x
// z
// y
// height
void fluted_column(double x, double y, double z, double r, double fr, double height) {

        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glBindTexture(GL_TEXTURE_2D,texture[0]);
        //  Save transformation
        glPushMatrix();
        int i;

        // //  Enable textures
        // glEnable(GL_TEXTURE_2D);
        // glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_MODULATE);
        // //glColor3f(1,1,1);
        //
        // glBindTexture(GL_TEXTURE_2D,texture[2]);

        //tops and bottoms
        for (i = 0; i < 360; i+= 45) {
                glBegin(GL_TRIANGLE_FAN);
                //
                circle(0.5, fr, r, (double) i, 0.3, 0.1, 0.2, x, y, z);
                glEnd();
                glBegin(GL_TRIANGLE_FAN);
                //
                circle(0.5, fr, r, (double) i, 0.3, 0.1, 0.2, x, y + height, z);
                glEnd();
        }
        //curved insides
        for (i = 0; i < 360; i+= 45) {
                glBegin(GL_QUAD_STRIP);
                //
                circle2(0.5, fr, r, (double) i, 0.67, 0.36, 0.34, y, y + height, x, z);
                glEnd();
        }
        //flat outsides on flutes
        // for (i = 0; i < 360; i+= 45) {
        //         glBegin(GL_QUAD_STRIP);
        //         //
        //         sine_wave3(0.5, fr, r, (double) i, 0.37, 0.26, 0.24, y, y + height, x, z);
        //         glEnd();
        // }

        //flat outsides between flutes
        for (i = 0; i < 360; i+= 45) {
                glBegin(GL_QUAD_STRIP);
                //
                glTexCoord2f(0, ((double) i)/360.0);
                circle4(0.5, fr, r, (double) i, 0.49, 0.36, 0.44, y, y + height, x, z);
                glTexCoord2f(1, ((double) i)/360.0);
                circle5(0.5, fr, r, (double) i + 45.0, 0.39, 0.26, 0.34, y, y + height, x, z);

                glEnd();
        }

        glPopMatrix();

        glDisable(GL_TEXTURE_2D);

}


//draws a fluted column
void column2(double sx,double sy,double sz) {
        glPushMatrix();
        //  Offset
        // glTranslated(x,y,z);
        // glRotated(th,0,1,0);
        glScaled(sx,sy,sz);

        //  Enable textures
        // glEnable(GL_TEXTURE_2D);
        // glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_MODULATE);
        //glColor3f(1,1,1);

        // glBindTexture(GL_TEXTURE_2D,texture[2]);
        float radius = 0.2;
        float height = 2.5;

        //top of column
        circleFace(13.2, radius*7.0);

        //bottom of fluted column
        circleFace(0, radius);

        glPushMatrix();
        glTranslated(0.4, -2.0, -1.0);
        glScaled(0.3, 0.3, 0.3);
        neck4(-1.5,-2.0, 3.5);
        glPopMatrix();

        glPushMatrix();
        glTranslated(-1.0, 14.0, 0.5);
        glRotated(180, 1, 0, 1);
        glScaled(0.3, 0.3, 0.3);
        neck4(-1.5,-2.0, 3.5);
        glPopMatrix();

        //top of fluted column
        circleFace(height, radius);

        fluted_column(0.0, 0.0, 0.0, 1.0, 0.14, 12.5);

        //  Undo transformations
        glPopMatrix();

        glDisable(GL_TEXTURE_2D);
}
