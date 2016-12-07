#ifndef CHARACTER_H
#define CHARACTER_H

#include "../setup/GL.h"
#include "../CSCIx229.h"
#include "../main.h"

#define X .525731112119133606
#define Z .850650808352039932


int icosahedron_normal_x(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3);

int icosahedron_normal_y(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3);

int icosahedron_normal_z(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3);

void icosahedron(double x,double y,double z, struct statuses * status, GLfloat *BoxMat, unsigned int *texture);

void character(double x,double y,double z, struct statuses *status, GLfloat *BoxMat, unsigned int *texture);
#endif
