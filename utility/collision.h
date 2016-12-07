#ifndef COLLISION_H
#define COLLISION_H

void generate_scene_with_collision(double baluster_positions[][3], double wx, double wy, double wz, double th, int grab);
void generate_squares_with_detection(double baluster_positions[][3], double square_positions[][3], double *square_index, double wx, double wy, double wz);


#endif
