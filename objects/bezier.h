#ifndef BEZIER_H
#define BEZIER_H

//17 different curves
double bezier_jar_1[8] = {0.32, 2.11, -0.3, 0.6,
                          -0.01, 0.55, 1.88, 2.32};
double bezier_jar_2[8] = {0.26, 2.34, -0.4, 0.84,
                          -0.01, 0.76, 2.07, 2.6};
double bezier_jar_3[8] = {0.15, 1.64, -0.43, 0.47,
                          -0.01, 0.34, 1.68, 1.69};
//
double bezier_baluster_1[8] = {0.26, 1.15, 0.2, 0.24,
                               -0.02, 0.9, 1.67, 3.37};
//
double bezier_baluster_2[8] = {0.26, 2.15, 0.22, 0.22,
                               -0.02, 0.75, 1.6, 2.97};
//fat
double bezier_baluster_3[8] = {0.57, 2.5, 0.45, 0.62,
                               -0.01, 0.9, 2.02, 2.91};
//cylindrical
double bezier_baluster_4[8] = {0.05, 1.82, 0.53, 0.62,
                               0.02, -0.01, 1.81, 2.91};
//sharp
double bezier_baluster_5[8] = {0.05, 1.82, 0.05, 0.3,
                               0.02, -0.01, 1.72, 3.14};
//tall & skinny
double bezier_baluster_6[8] = {0.05, 1.97, -0.1, 0.45,
                               0.02, 0.04, 3.18, 0.45};
//tall & thick
double bezier_baluster_7[8] = {0.05, 2.44, 0.0, 0.5,
                               0.02, 0.45, 3.93, 5.03};
//regular
double bezier_baluster_8[8] = {0.05, 1.68, 0.02, 0.43,
                               0.02, -0.06, 2.01, 2.77};
//curved base
double bezier_baluster_9[8] = {3.00, 1.91, 1.9, 0.9,
                               0.04, 0.0, 1.75, 1.77};
//tallest
double bezier_baluster_10[8] = {0.12, 1.5, 0.54, 0.4,
                                0.13, 0.08, 2.53, 9.1};
//tallest upside down
double bezier_baluster_11[8] = {0.4, 0.54, 1.5, 0.12,
                                -1.5, 6.57, 8.93, 9.1};
//
double bezier_bell_1[8] = {0.05,1.75, 0.3, 1.37,
                           0.02, 0.03, 2.01, 2.01};
//
double bezier_bell_2[8] = {0.83, 0.83, 0.98, 1.47,
                           0.04, 2.61, 1.46, 2.12};
//
double bezier_echinus[8] = {0.8, 2.39, 2.85, 2.93,
                            0.0, 0.01, 0.725, 1.6};
//
double bezier_astragal[8] = {1.135, 1.73, 1.73, 1.13,
                             0.0, 0.01, 0.58, 0.59};
//
double bezier_bed_mould[8] = {1.18, 1.18, 2.0, 2.01,
                              0.01, 1.06, 0.39, 1.31};
//
double bezier_cymatium[8] = {1.01, 1.73, 2.3, 2.32,
                             0.03, 0.045, 0.2, 0.86};

double bezier_x(double x1, double x2, double x3, double x4, double t);
double bezier_y(double y1, double y2, double y3, double y4, double t);
void bezier_curve(double f, double x, double y, double z, double *curve);
void baluster(double f, double s, double x, double y, double z, double *curve);
void baluster_tex(double f, double s, double x, double y, double z, double *curve, int tex);

#endif
