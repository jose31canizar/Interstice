#ifndef CHARACTER_H
#define CHARACTER_H

#include "../setup/GL.h"
#include "../CSCIx229.h"
#include "../main.h"

#define X .525731112119133606
#define Z .850650808352039932

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

int icosahedron_normal_x(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3);

int icosahedron_normal_y(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3);

int icosahedron_normal_z(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3);

void icosahedron(double x,double y,double z, struct statuses * status, GLfloat *BoxMat, unsigned int *texture);

void character(double x,double y,double z, struct statuses *status, GLfloat *BoxMat, unsigned int *texture);
#endif
