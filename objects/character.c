#include "character.h"


//data for icosahedron
static float vdata[12][3] = {
        {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},
        {0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},
        {Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0}
};

//data for icosahedron
static int tindices [20][3] = {
        {1, 4, 0}, {4, 9, 0}, {4, 5, 9}, {8, 5, 4}, {1, 8, 4},
        {1, 10, 8}, {10, 3, 8}, {8, 3, 5}, {3, 2, 5}, {3, 7, 2},
        {3, 10, 7}, {10, 6, 7}, {6, 11, 7}, {6, 0, 11}, {6, 1, 0},
        {10, 1, 6}, {11, 0, 9}, {2, 11, 9}, {5, 2, 9}, {11, 2, 7},
};


int icosahedron_normal_x(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3) {
        int nx = (y2 - y1)*(z3 - z1) - (z2 - z1)*(y3 - y1);
        return nx;
}

int icosahedron_normal_y(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3) {
        int ny = (z2 - z1)*(x3 - x1) - (x2 - x1)*(z3 - z1);
        return ny;
}

int icosahedron_normal_z(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3) {
        int nz = (x2 - x1)*(y3 - y1) - (y2 - y1)*(x3 - x1);
        return nz;
}


/*
 *  Draw an icosahedron
 *     at (x,y,z)
 *     dimentions (dx,dy,dz)
 *     rotated th about the y axis
 */
// unsigned int *texture
GLfloat BoxMat2[16] = {0, 0, 0, 0,
                       0, 0, 0, 0,
                       0, 0, 0, 0,
                       0, 0, 0, 0};

//character proxy
void character(double x,double y,double z, struct statuses *status, GLfloat *BoxMat, unsigned int *texture) {
        icosahedron(x,y,z,status, BoxMat, texture);
}

void icosahedron(double x,double y,double z, struct statuses *status, GLfloat *BoxMat, unsigned int *texture) {

        // for(int i = 0; i < 16; i++) {
        //         BoxMat2[i] = BoxMat[i];
        // }
        // BoxMat2[1] = 0.5;
        // BoxMat2[5] = 0.5;
        // BoxMat2[9] = 0.5;
        // glRotatef(-(status->wr), status->vx, 0.0, status->vz);
        // glGetFloatv(GL_MODELVIEW_MATRIX, BoxMat2);

        // for(int i = 0; i < 16; i++) {
        //         printf("1: %f ", BoxMat[i]);
        //         printf("2: %f \n", BoxMat2[i]);
        // }

        glPushMatrix();
        glTranslated(x, y, z);
        // glLoadIdentity();
        // glMultMatrixf(BoxMat2);
        glRotatef(-(status->wr), status->vx, 0.0, status->vz);
        glScaled(8.0, 8.0, 8.0);


        //glRotated(-wr, Cos(-th), 0, Sin(-th));
        // glRotated(wr, 0.0, 1.0, 0.0);
        // gluLookAt(Fx,Fy,Fz, 0.0,0.0,0.0, 0,1,0);
        // glMultMatrixf(BoxMat);
        //glRotatef(-wr, Cos(th), 0.0, Sin(th));
        //printf("%f ", status->vz);
        //from where your eye is looking at

        //  Enable textures
        glEnable(GL_TEXTURE_2D);
        glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glColor3f(1,1,1);

        glBindTexture(GL_TEXTURE_2D,texture[6]);



        glBegin(GL_POLYGON);
        // glVertex3f(0.25,0.25,0);

        // glVertex3f(0.25,0.25,0);
        //
        // glVertex3f(0.75,0.25,0);
        //
        // glVertex3f(0.75,0.75,0);
        //
        // glVertex3f(0.25,0.75,0);
        glEnd();


        int i;

        double t = 0.05;
        glBegin(GL_TRIANGLES);
        for(i=0; i<20; i++) {
                // glColor4f(0.043*i + 0.07,0.019*i + 0.07,0.017*i + 0.06, 0.1);
                //glColor3f(0.76, 0.45, 0.59);

                glNormal3f(vdata[tindices[i][0]][0],vdata[tindices[i][0]][1],vdata[tindices[i][0]][2]);
                glTexCoord2f(-t, t);
                glVertex3fv(&vdata[tindices[i][0]][0]);
                glNormal3f(vdata[tindices[i][1]][0],vdata[tindices[i][1]][1],vdata[tindices[i][1]][2]);
                glTexCoord2f(-t, t);
                glVertex3fv(&vdata[tindices[i][1]][0]);
                glNormal3f(vdata[tindices[i][2]][0],vdata[tindices[i][2]][1],vdata[tindices[i][2]][2]);
                glTexCoord2f(-t, -t);
                glVertex3fv(&vdata[tindices[i][2]][0]);
        }

        glEnd();

        glPopMatrix();

        glDisable(GL_TEXTURE_2D);

}
