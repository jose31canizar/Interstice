#ifndef PARTS_H
#define PARTS_H

void load_initial_scene(double baluster_positions[][3]);
void load_squares(double square_positions[][3]);
void generate_scene(double baluster_positions[][3], double wx, double wy, double wz);
void generate_square(double square_positions[][3], int *index, double wx, double wy, double wz);

#endif
