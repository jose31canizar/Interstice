#include "floors.h"
#include "../setup/GL.h"
#include "../setup/textures.h" //texture array

/*
 *  Draw a floor plane
 *     at (x,y,z)
 *     dimentions (dx,dy,dz)
 *     rotated th about the y axis
 *    r, g, b is the base color
 */
//, unsigned int *texture
void cube(double x,double y,double z,
          double dx,double dy,double dz,
          double th, double r, double g, double b, int tex, double range) {

        glPushMatrix();
        //  Offset
        glTranslated(x,y,z);
        glRotated(th,0,1,0);
        glScaled(dx,dy,dz);

        double shift = 0.0;

        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glBindTexture(GL_TEXTURE_2D,texture[tex]);

        //  Platform
        glBegin(GL_QUADS);
        //  Front
        // glColor3f(r + 0.07,g + 0.04,b + 0.09);
        glNormal3f(0,0, 1);
        glTexCoord2f(shift, shift);
        glVertex3f(-1,-1, 1);
        glTexCoord2f(range + shift, shift);
        glVertex3f(+1,-1, 1);
        glTexCoord2f(range + shift, range + shift);
        glVertex3f(+1,+1, 1);
        glTexCoord2f(shift, range + shift);
        glVertex3f(-1,+1, 1);
        //  Back

        // glColor3f(r + 0.02,g + 0.08,b + 0.12);
        glNormal3f(0,0, -1);
        glTexCoord2f(range + shift, shift);
        glVertex3f(+1,-1,-1);
        glTexCoord2f(shift, shift);
        glVertex3f(-1,-1,-1);
        glTexCoord2f(shift, range + shift);
        glVertex3f(-1,+1,-1);
        glTexCoord2f(range + shift, range + shift);
        glVertex3f(+1,+1,-1);
        //  Right
        // glColor3f(r + 0.04,g + 0.04, b + 0.07);
        glNormal3f(1,0, 0);
        glTexCoord2f(range + shift, shift);
        glVertex3f(+1,-1,+1);
        glTexCoord2f(shift, shift);
        glVertex3f(+1,-1,-1);
        glTexCoord2f(range + shift, range + shift);
        glVertex3f(+1,+1,-1);
        glTexCoord2f(shift, range + shift);
        glVertex3f(+1,+1,+1);
        //  Left
        // glColor3f(r + 0.06,g + 0.06,b + 0.09);
        glNormal3f(-1,0, 0);
        glTexCoord2f(shift, shift);
        glVertex3f(-1,-1,-1);
        glTexCoord2f(shift, range + shift);
        glVertex3f(-1,-1,+1);
        glTexCoord2f(range + shift, range + shift);
        glVertex3f(-1,+1,+1);
        glTexCoord2f(range + shift, shift);
        glVertex3f(-1,+1,-1);
        //  Top
        // glColor3f(0.14,0.08,0.085);
        glNormal3f(0,1, 0);
        glTexCoord2f(shift, range + shift);
        glVertex3f(-1,+1,+1);
        glTexCoord2f(range + shift, range + shift);
        glVertex3f(+1,+1,+1);
        glTexCoord2f(range + shift, shift);
        glVertex3f(+1,+1,-1);
        glTexCoord2f(shift, shift);
        glVertex3f(-1,+1,-1);
        //  Bottom
        // glColor3f(0.19, 0.09,0.08);
        glNormal3f(0,-1, 0);
        glTexCoord2f(shift, shift);
        glVertex3f(-1,-1,-1);
        glTexCoord2f(range + shift, shift);
        glVertex3f(+1,-1,-1);
        glTexCoord2f(shift, range + shift);
        glVertex3f(+1,-1,+1);
        glTexCoord2f(range + shift, range + shift);
        glVertex3f(-1,-1,+1);
        //  End
        glEnd();
        //  Undo transformations
        glPopMatrix();
}
