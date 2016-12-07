#include "../setup/GL.h"
#include "../objects/balusters.h"
#include "math.h"
#include "stdlib.h"
#include "time.h"
#include "logic.h"
#include "../objects/parts.h"

void load_initial_scene(double baluster_positions[][3], double square_positions[][3]) {
        time_t t;
        int i = 0;
        int shuffledNums[16] = {1, 4, 14, 8,
                                3, 7, 13, 5,
                                9, 11, 10, 2,
                                15, 12, 16, 6};
        /* Intializes random number generator */
        srand((unsigned) time(&t));

        double spacing = 20.0;
        double starting_point_x = -180.0;

        /* Print 5 random numbers from 0 to 49 */
        for(i = 0; i < 16; i++)
        {
                baluster_positions[i][0] = shuffledNums[i] * spacing + starting_point_x;
                // baluster_positions[i][2] = (rand() % 50) * 10;
                baluster_positions[i][2] = -50.0;
                // printf("%d\n", rand() % 50);
        }
}

void load_squares(double square_positions[][3]) {
        time_t t;
        int i = 0;
        double spacing = 5.0;
        srand((unsigned) time(&t));
        double starting_point = -150.0;


        for(i = 0; i < 16; i++)
        {
                //initalize blue square positions
                //-150 to 150
                square_positions[i][0] = (rand() % 60) * spacing + starting_point;
                square_positions[i][2] = (rand() % 60) * spacing + starting_point;
        }
}

void generate_scene(double baluster_positions[][3], double wx, double wy, double wz) {
        int i = 0;
        for(i = 0; i < 16; i += 1)
        {
                switch(i) {
                case 0:
                        baluster_1(wx + baluster_positions[i][0], wy, wz + baluster_positions[i][2]);

                        break;
                case 1:
                        baluster_2(wx + baluster_positions[i][0], wy, wz + baluster_positions[i][2]);

                        break;
                case 2:
                        baluster_3(wx + baluster_positions[i][0], wy, wz + baluster_positions[i][2]);

                        break;
                case 3:
                        baluster_4(wx + baluster_positions[i][0], wy, wz + baluster_positions[i][2]);

                        break;
                case 4:
                        baluster_5(wx + baluster_positions[i][0], wy, wz + baluster_positions[i][2]);

                        break;
                case 5:
                        baluster_6(wx + baluster_positions[i][0], wy, wz + baluster_positions[i][2]);

                        break;
                case 6:
                        baluster_7(wx + baluster_positions[i][0], wy, wz + baluster_positions[i][2]);

                        break;
                case 7:
                        baluster_8(wx + baluster_positions[i][0], wy, wz + baluster_positions[i][2]);

                        break;
                case 8:
                        baluster_9(wx + baluster_positions[i][0], wy, wz + baluster_positions[i][2]);

                        break;
                case 9:
                        baluster_10(wx + baluster_positions[i][0], wy, wz + baluster_positions[i][2]);

                        break;
                case 10:
                        baluster_11(wx + baluster_positions[i][0], wy, wz + baluster_positions[i][2]);

                        break;
                case 11:
                        baluster_12(wx + baluster_positions[i][0], wy, wz + baluster_positions[i][2]);

                        break;
                case 12:
                        baluster_13(wx + baluster_positions[i][0], wy, wz + baluster_positions[i][2]);

                        break;
                case 13:
                        baluster_14(wx + baluster_positions[i][0], wy, wz + baluster_positions[i][2]);

                        break;
                case 14:
                        baluster_15(wx + baluster_positions[i][0], wy, wz + baluster_positions[i][2]);

                        break;
                case 15:
                        baluster_16(wx + baluster_positions[i][0], wy, wz + baluster_positions[i][2]);
                        break;
                default:
                        break;

                }
                //baluster_1(wx + baluster_positions[i][0], wy, wz + baluster_positions[i][2]);
                // printf("%d\n", rand() % 50);
        }
}

void generate_square(double square_positions[][3], int *index, double posx, double posy, double posz) {
        // printf("%f\n", *index);

        for(int i = 0; i < *index+1; i++) {

                if (*index == 16) {
                        glPushMatrix();
                        glColor3f(0.99, 0.11, 0.20);
                        drawRect(150, 150);
                        glPopMatrix();
                } else {
                        glPushMatrix();
                        if (i == *index) {
                                glColor3f(0.55, 0.51, 0.92);
                        } else {
                                glColor3f(0.99, 0.11, 0.20);
                        }
                        // glTranslated(posx, posy, posz);
                        glTranslated(square_positions[i][0] + posx, posy, square_positions[i][2] + posz);
                        drawRect(8, 8);
                        glPopMatrix();
                }

        }


}
