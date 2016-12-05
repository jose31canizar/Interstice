#include "randomizer.h"
#include "math.h"
#include "../CSCIx229.h"
#include "../setup/GL.h"

int grabbed = -1; //  1 - 16

double rotate_x(double x, double z, double th) {
        return x*Cos(th) - z*Sin(th);
}

double rotate_z(double x, double z, double th) {
        return x*Sin(th) + z*Cos(th);
}

void generate_scene_with_collision(double baluster_positions[][3], double wx, double wy, double wz, double th, int grab) {


        generate_scene(baluster_positions, wx, wy, wz);

        int i;
        int j;

        double a = 10.0; // amount of grab movement
        // int inc = 45.0;
        double r = 5.0; //object box width and height
        double box = 10.0; //character width and height
        double d = 5.0; // collision distance

        double ax = box; //width box
        double az = box; //height box

        //four corners
        double x1 = rotate_x(-ax, az, th);
        double z1 = rotate_z(-ax, az, th);

        double x2 = rotate_x(ax, az, th);
        double z2 = rotate_z(ax, az, th);

        double x3 = rotate_x(ax, -az, th);
        double z3 = rotate_z(ax, -az, th);

        double x4 = rotate_x(-ax, -az, th);
        double z4 = rotate_z(-ax, -az, th);


        //collision box edge lengths
        double a1 = sqrt(pow(x1 - x2, 2.0) + pow(z1 - z2, 2.0));
        double a2 = sqrt(pow(x2 - x3, 2.0) + pow(z2 - z3, 2.0));
        double a3 = sqrt(pow(x3 - x4, 2.0) + pow(z3 - z4, 2.0));
        double a4 = sqrt(pow(x4 - x1, 2.0) + pow(z4 - z1, 2.0));

        //character bounding box drawn here
        //glPushMatrix();
        // glBegin(GL_QUAD_STRIP);
        // glVertex3f(x1, 2.0, z1);
        // glVertex3f(x2, 2.0, z2);
        // glVertex3f(x3, 2.0, z3);
        // glVertex3f(x4, 2.0, z4);
        // glEnd();
        //glPopMatrix();

        double ox;
        double oz;

        double b1;
        double b2;
        double b3;
        double b4;

        double u1;
        double u2;
        double u3;
        double u4;

        double A1;
        double A2;
        double A3;
        double A4;

        double A = a1*a2; //area of collision box

        double still_grabbing = 0;

        for(i = 0; i < 16; i += 1)
        {
                //object bounding box drawn
                // glColor3f(0.97, 0.8, 0.94);
                // glBegin(GL_QUAD_STRIP);
                // glVertex3f(baluster_positions[i][0] + r + wx, 4.0, baluster_positions[i][2] - r + wz);
                // glVertex3f(baluster_positions[i][0] + r + wx, 4.0, baluster_positions[i][2] + r + wz);
                // glVertex3f(baluster_positions[i][0] - r + wx, 4.0, baluster_positions[i][2] - r + wz);
                // glVertex3f(baluster_positions[i][0] - r + wx, 4.0, baluster_positions[i][2] + r + wz);
                // glEnd();

                if (grabbed == i && grab) {
                        baluster_positions[i][0] = -wx + a*Sin(th);
                        baluster_positions[i][2] = -wz - a*Cos(th);
                        still_grabbing = 1;
                }

                for(j = 0; j < 4; j+= 1) {

                        //object box points from viewport perspective
                        if (j == 0) {
                                ox = baluster_positions[i][0] + r + wx;
                                oz = baluster_positions[i][2] + r + wz;
                        } else if (j == 1) {
                                ox = baluster_positions[i][0] - r + wx;
                                oz = baluster_positions[i][2] + r + wz;
                        } else if (j == 2) {
                                ox = baluster_positions[i][0] - r + wx;
                                oz = baluster_positions[i][2] - r + wz;
                        } else if (j == 3) {
                                ox = baluster_positions[i][0] + r + wx;
                                oz = baluster_positions[i][2] - r + wz;
                        }

                        //lengths from point to each corner
                        b1 = sqrt(pow(x1 - ox, 2.0) + pow(z1 - oz, 2.0));
                        b2 = sqrt(pow(x2 - ox, 2.0) + pow(z2 - oz, 2.0));
                        b3 = sqrt(pow(x3 - ox, 2.0) + pow(z3 - oz, 2.0));
                        b4 = sqrt(pow(x4 - ox, 2.0) + pow(z4 - oz, 2.0));

                        //Heron's formula
                        u1 = (a1 + b1 + b2)/2.0;
                        u2 = (a2 + b2 + b3)/2.0;
                        u3 = (a3 + b3 + b4)/2.0;
                        u4 = (a4 + b4 + b1)/2.0;


                        A1 = sqrt(u1*(u1 - a1)*(u1 - b1)*(u1 - b2));
                        A2 = sqrt(u2*(u2 - a2)*(u2 - b2)*(u2 - b3));
                        A3 = sqrt(u3*(u3 - a3)*(u3 - b3)*(u3 - b4));
                        A4 = sqrt(u4*(u4 - a4)*(u4 - b4)*(u4 - b1));

                        if(A == A1 + A2 + A3 + A4) {

                                //first grab
                                if (grab && grabbed != i && !still_grabbing) {
                                        grabbed = i;

                                } else if (still_grabbing) {
                                        //still grabbing, so push others
                                        baluster_positions[i][0] += d*Sin(th);
                                        baluster_positions[i][2] -= d*Cos(th);
                                } else {
                                        still_grabbing = 0;
                                        //push away
                                        grabbed = -1;
                                        baluster_positions[i][0] += d*Sin(th);
                                        baluster_positions[i][2] -= d*Cos(th);
                                }
                        }
                }
        }
}
