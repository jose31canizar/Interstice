#include "bezier.h"
#include "parts.h"
#include "floors.h"
#include "../setup/GL.h"
#include "../CSCIx229.h"

void neck(double wx, double wy, double wz) {
        drawClosedCylinder(0.0, 1.0, 3.5, wx, wy + 4.0, wz);
        drawClosedCylinder(0.0, 1.0, 4.5, wx, wy + 3.0, wz);
        drawClosedCylinder(0.0, 1.0, 3.5, wx, wy + 2.0, wz);
}

void neck2(double wx, double wy, double wz) {
        drawClosedCylinder(0.0, 1.0, 5.5, wx, wy + 4.0, wz);
        drawClosedCylinder(0.0, 1.0, 6.5, wx, wy + 3.0, wz);
        drawClosedCylinder(0.0, 1.0, 5.5, wx, wy + 2.0, wz);
}

void neck4(double wx, double wy, double wz) {
        // glPushMatrix();
        baluster_tex(0.05, 0.14, wx, wy + 9.0, wz, bezier_astragal, 4);
        baluster_tex(0.05, 0.16, wx, wy + 7.5, wz, bezier_astragal, 4);
        baluster_tex(0.05, 0.14, wx, wy + 6.0, wz, bezier_astragal, 4);
        baluster_tex(0.05, 0.19, wx, wy + 4.5, wz, bezier_astragal, 4);
        // glPopMatrix();
}

void baluster_1(double wx, double wy, double wz) {
        baluster(0.05, 0.2, wx, wy + 0.6, wz, bezier_jar_2);
        baluster(0.05, 0.11, wx, wy + 0.1, wz, bezier_astragal);
}

void baluster_2(double wx, double wy, double wz) {
        baluster(0.05, 0.34, wx, wy + 2.4, wz, bezier_jar_3);
        baluster(0.05, 0.06, wx, wy + 1.6, wz, bezier_baluster_9);
        baluster(0.05, 0.16, wx, wy, wz, bezier_astragal);
}

void baluster_3(double wx, double wy, double wz) {
        baluster(0.05, 0.08, wx, wy + 8.0, wz, bezier_astragal);
        baluster(0.05, 0.4, wx, wy + 2.4, wz, bezier_jar_3);
        baluster(0.05, 0.06, wx, wy + 1.6, wz, bezier_baluster_9);
        baluster(0.05, 0.16, wx, wy, wz, bezier_astragal);
}

void baluster_4(double wx, double wy, double wz) {
        baluster(0.05, 0.09, wx, wy + 8.0, wz, bezier_astragal);
        baluster(0.05, 0.44, wx, wy + 2.4, wz, bezier_jar_3);
        baluster(0.05, 0.07, wx, wy + 1.6, wz, bezier_baluster_9);
        baluster(0.05, 0.16, wx, wy, wz, bezier_astragal);
}

void baluster_5(double wx, double wy, double wz) {
        baluster(0.05, 0.09, wx, wy + 8.0, wz, bezier_astragal);
        baluster(0.05, 0.52, wx, wy + 3.5, wz, bezier_jar_3);
        baluster(0.05, 0.08, wx, wy + 1.35, wz, bezier_baluster_9);
        baluster(0.05, 0.15, wx, wy, wz, bezier_astragal);
}

void baluster_6(double wx, double wy, double wz) {
        drawClosedCylinder(0.0, 3.6, 5.5, wx, wy + 19.0, wz);
        drawClosedCylinder(0.0, 2.1, 3.5, wx, wy + 17.3, wz);
        neck(wx, wy + 4.0, wz);
        baluster(0.05, 0.3, wx, wy + 8.0, wz, bezier_baluster_6);
        baluster(0.05, 0.08, wx, wy + 3.6, wz, bezier_baluster_9);
        drawClosedCylinder(0.0, 3.6, 5.5, wx, wy, wz);
}

void baluster_7(double wx, double wy, double wz) {
        drawClosedCylinder(0.0, 3.6, 5.5, wx, wy + 24.0, wz);
        neck(wx, wy + 4.0, wz);
        baluster(0.05, 0.3, wx, wy + 8.0, wz, bezier_baluster_5);
        neck(wx, wy + 14.0, wz);
        neck(wx, wy + 18.0, wz);
        baluster(0.05, 0.08, wx, wy + 3.6, wz, bezier_baluster_9);
        drawClosedCylinder(0.0, 3.6, 5.5, wx, wy, wz);
}

void baluster_8(double wx, double wy, double wz) {
        drawClosedCylinder(0.0, 3.6, 5.5, wx, wy + 26.0, wz);
        neck(wx, wy + 4.0, wz);
        baluster(0.05, 0.3, wx, wy + 8.0, wz, bezier_baluster_8);
        neck(wx, wy + 14.0, wz);
        neck(wx, wy + 21.0, wz);
        baluster(0.05, 0.08, wx, wy + 3.6, wz, bezier_baluster_9);
        drawClosedCylinder(0.0, 3.6, 5.5, wx, wy, wz);
}

void baluster_9(double wx, double wy, double wz) {
        drawClosedCylinder(0.0, 3.6, 5.5, wx, wy + 28.0, wz);
        neck(wx, wy + 4.0, wz);
        baluster(0.05, 0.3, wx, wy + 8.0, wz, bezier_baluster_4);
        neck(wx, wy + 14.0, wz);
        neck(wx, wy + 23.0, wz);
        baluster(0.05, 0.08, wx, wy + 3.6, wz, bezier_baluster_9);
        drawClosedCylinder(0.0, 3.6, 5.5, wx, wy, wz);
}

void baluster_10(double wx, double wy, double wz) {
        drawClosedCylinder(0.0, 3.6, 5.5, wx, wy + 36.0, wz);
        neck(wx, wy + 4.0, wz);
        baluster(0.05, 0.3, wx, wy + 8.0, wz, bezier_baluster_7);
        neck(wx, wy + 14.0, wz);
        neck(wx, wy + 30.0, wz);
        baluster(0.05, 0.08, wx, wy + 3.6, wz, bezier_baluster_9);
        drawClosedCylinder(0.0, 3.6, 5.5, wx, wy, wz);
}


void baluster_11(double wx, double wy, double wz) {
        drawClosedCylinder(0.0, 3.6, 5.5, wx, wy + 38.0, wz);
        neck(wx, wy + 15.0, wz);
        baluster(0.05, 0.3, wx, wy + 19.0, wz, bezier_baluster_1);
        neck(wx, wy + 25.0, wz);
        neck(wx, wy + 32.0, wz);
        baluster(0.05, 0.08, wx, wy + 14.6, wz, bezier_baluster_9);
        drawClosedCylinder(0.0, 3.6, 5.5, wx, wy + 11.0, wz);
        neck(wx, wy + 9.0, wz);
        baluster(0.05, 0.3, wx, wy + 7.0, wz, bezier_baluster_1);
        neck(wx, wy + 5.0, wz);
        neck(wx, wy + 3.0, wz);
        baluster(0.05, 0.08, wx, wy + 3.0, wz, bezier_baluster_9);
        drawClosedCylinder(0.0, 3.6, 5.5, wx, wy, wz);

}

void baluster_12(double wx, double wy, double wz) {
        drawClosedCylinder(0.0, 3.6, 5.5, wx, wy + 44.0, wz);
        neck(wx, wy + 42.0, wz);
        baluster(0.05, 0.2, wx, wy + 39.0, wz, bezier_baluster_6);
        drawClosedCylinder(0.0, 3.6, 5.5, wx, wy + 36.0, wz);
        neck(wx, wy + 14.0, wz);
        baluster(0.05, 0.3, wx, wy + 18.0, wz, bezier_baluster_1);
        neck(wx, wy + 24.0, wz);
        neck(wx, wy + 31.0, wz);
        baluster(0.05, 0.08, wx, wy + 13.6, wz, bezier_baluster_9);
        neck2(wx, wy + 9.0, wz);
        baluster(0.05, 0.24, wx, wy + 8.5, wz, bezier_astragal);
        drawClosedCylinder(0.0, 0.5, 5.8, wx, wy + 8.0, wz);
        baluster(0.05, 0.3, wx, wy + 2.7, wz, bezier_baluster_6);
        drawClosedCylinder(0.0, 3.6, 7.6, wx, wy, wz);

}


void baluster_13(double wx, double wy, double wz) {
        drawClosedCylinder(0.0, 3.6, 5.5, wx, wy + 52.0, wz);
        neck(wx, wy + 47.0, wz);
        neck(wx, wy + 40.0, wz);
        baluster(0.05, 0.3, wx, wy + 34.0, wz, bezier_baluster_1);
        neck(wx, wy + 30.0, wz);
        baluster(0.05, 0.08, wx, wy + 29.6, wz, bezier_baluster_9);
        drawClosedCylinder(0.0, 3.6, 5.5, wx, wy + 26.0, wz);
        neck(wx, wy + 21.0, wz);
        neck(wx, wy + 14.0, wz);
        baluster(0.05, 0.3, wx, wy + 8.0, wz, bezier_baluster_1);
        neck(wx, wy + 4.0, wz);
        baluster(0.05, 0.08, wx, wy + 3.6, wz, bezier_baluster_9);
        drawClosedCylinder(0.0, 3.6, 5.5, wx, wy, wz);
}

void baluster_14(double wx, double wy, double wz) {
        baluster_7(wx, wy, wz);
        glPushMatrix();
        glTranslated(wx, wy + 50.0, wz);
        glRotated(180, 1, 0, 0);
        baluster_7(0.0, 0.0, 0.0);
        glPopMatrix();
        baluster(0.05, 0.3, wx, wy + 45.0, wz, bezier_jar_2);
}

void baluster_15(double wx, double wy, double wz) {
        baluster_9(wx, wy, wz);
        glPushMatrix();
        glTranslated(wx, wy + 60.0, wz);
        glRotated(180, 1, 0, 0);
        baluster_9(0.0, 0.0, 0.0);
        glPopMatrix();
        baluster(0.05, 0.3, wx, wy + 60.0, wz, bezier_jar_2);
}

void baluster_16(double wx, double wy, double wz) {
        baluster_11(wx, wy, wz);
        glPushMatrix();
        glTranslated(wx, wy + 65.0, wz);
        glRotated(180, 1, 0, 0);
        baluster_11(0.0, 0.0, 0.0);
        glPopMatrix();
        baluster(0.05, 0.3, wx, wy + 65.0, wz, bezier_jar_2);
}


void neck3(double wx, double wy, double wz) {
        // glPushMatrix();
        baluster(0.05, 0.15, wx, wy + 9.5, wz, bezier_astragal);
        baluster(0.05, 0.17, wx, wy + 8.0, wz, bezier_astragal);
        baluster(0.05, 0.15, wx, wy + 6.5, wz, bezier_astragal);
        // glPopMatrix();
}

void regular_baluster_1(double wx, double wy, double wz) {
        double b_range = 0.1;
        cube(wx, wy + 38.5, wz, 2.0, 1.5, 2.0, 0.0, 0.4, 0.6, 0.9, 3, b_range);
        baluster(0.05, 0.06, wx, wy + 36.3, wz, bezier_astragal);
        drawClosedCylinder(0.0, 0.6, 1.5, wx, wy + 36.3, wz);
        baluster(0.05, 0.08, wx, wy + 22.0, wz, bezier_baluster_10);

        baluster(0.05, 0.09, wx, wy + 19.6, wz, bezier_baluster_6);

        baluster(0.05, 0.08, wx, wy + 6.0, wz, bezier_baluster_11);
        drawClosedCylinder(0.0, 0.6, 1.5, wx, wy + 2.9, wz);
        baluster(0.05, 0.06, wx, wy + 2.9, wz, bezier_astragal);
        cube(wx, wy + 1.4, wz, 2.0, 1.5, 2.0, 0.0, 0.4, 0.6, 0.9, 3, b_range);

}

void balustrade(double wx, double wy, double wz) {
        for(int i = 0; i < 10; i++) {
                regular_baluster_1(wx, wy, wz + i*5);
        }
}

void draw_balusters(double wx, double wy, double wz) {
        // double s = 0.3;
        glPushMatrix();
        // baluster(0.05, s, -wx, wy, -wz - 25, &bezier_baluster_8);
        // baluster(0.05, s, -wx, wy, -wz - 50, &bezier_baluster_7);
        // baluster(0.05, s, -wx, wy, -wz - 75, &bezier_baluster_6);
        // baluster(0.05, s, -wx, wy, -wz - 100, &bezier_baluster_5);
        // baluster(0.05, s, -wx, wy, -wz - 125, &bezier_baluster_4);
        // baluster(0.05, s, -wx, wy, -wz - 150, &bezier_baluster_3);
        // baluster(0.05, s, -wx, wy, -wz - 175, &bezier_baluster_2);
        // baluster(0.05, s, -wx, wy, -wz - 200, &bezier_baluster_1);
        // baluster(0.05, s, -wx, wy, -wz - 225, &bezier_bell_2);
        // baluster(0.05, s, -wx, wy, -wz - 250, &bezier_bell_1);
        // baluster(0.05, s, -wx, wy, -wz - 275, &bezier_jar_3);
        // baluster(0.05, s, -wx, wy, -wz - 300, &bezier_jar_2);
        // baluster(0.05, s, -wx, wy, -wz - 325, &bezier_bell_1);
        // baluster(0.05, s, -wx, wy, -wz - 350, &bezier_echinus);
        // baluster(0.05, s, -wx, wy, -wz - 375, &bezier_astragal);
        // baluster(0.05, s, -wx, wy, -wz - 400, &bezier_bed_mould);
        // baluster(0.05, s, -wx, wy, -wz - 425, &bezier_cymatium);
        // baluster(0.05, s, -wx, wy, -wz - 450, &bezier_baluster_9);
        // baluster_1(-wx + 100, wy, -wz);
        // baluster_2(-wx + 100, wy, -wz + 25);
        // baluster_3(-wx + 100, wy, -wz + 50);
        // baluster_4(-wx + 100, wy, -wz + 75);
        // baluster_5(-wx + 100, wy, -wz + 100);
        // baluster_6(-wx + 100, wy, -wz + 125);
        // baluster_7(-wx + 100, wy, -wz + 150);
        // baluster_8(-wx + 100, wy, -wz + 175);
        // baluster_9(-wx + 100, wy, -wz + 200);
        // baluster_10(-wx + 100, wy, -wz + 225);
        // baluster_11(-wx + 100, wy, -wz + 250);
        // baluster_12(-wx + 100, wy, -wz + 275);
        // baluster_13(-wx + 100, wy, -wz + 300);
        // baluster_14(-wx + 100, wy, -wz + 325);
        // baluster_15(-wx + 100, wy, -wz + 350);
        // baluster_16(-wx + 100, wy, -wz + 375);

        //balustrade(-wx + 300, wy, -wz + 200);

        glPopMatrix();

}
