#include "collision.h"

void checker(double baluster_positions[][3], double square_positions[][3], int *square_index, double wx, double wy, double wz) {

        // printf("%d", *square_index);
        // generate_squares_with_detection(baluster_positions, square_positions, square_index, square_positions[*square_index][0] + wx, wy, square_positions[*square_index][2] + wz);
        // generate_squares_with_detection(baluster_positions, square_positions, square_index, square_positions[*square_index][0], wy, square_positions[*square_index][2]);
        generate_squares_with_detection(baluster_positions, square_positions, square_index, wx, wy, wz);

}
