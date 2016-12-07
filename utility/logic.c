#include "collision.h"

void checker(double baluster_positions[][3], double square_positions[][3], int *square_index, double wx, double wy, double wz) {

        for(int i = 0; i < 16; i++) {
                if(i == *square_index) {
                        generate_squares_with_detection(baluster_positions, square_positions, square_index, wx, wy, wz);
                }
        }
}
