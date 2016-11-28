#include "randomizer.h"
#include <stdio.h>

void load_progress(double baluster_positions[][3]) {
        FILE *fp = fopen("progress.txt", "r");

        //File does not exist
        if(fp == NULL) {
                printf("First time opening game...\n");
                //randomize
                load_initial_scene(baluster_positions);

                fp = fopen("progress.txt", "w+");

                if (fp != NULL) {
                        printf( "New file created!\n" );

                        int i = 0;
                        double p1;
                        double p2;
                        for(i = 0; i < 16; i+= 1) {
                                p1 = baluster_positions[i][0];
                                p2 = baluster_positions[i][2];
                                //write to file
                                fprintf(fp, "%f %f\n", p1, p2);
                        }

                        fclose(fp);
                } else
                {
                        printf( "Error: Unable to create file!");
                }
        } else {
                printf( "Loading file...!\n" );
                // SDL_RWread( file, &baluster_positions, sizeof(48), 1 );
                double * p1;
                double * p2;
                int i;
                for(i = 0; i < 16; i+= 1) {
                        p1 = &baluster_positions[i][0];
                        p2 = &baluster_positions[i][2];
                        //read from file
                        fscanf(fp, "%lf %lf\n", p1, p2);
                }
                // printf("%f %f\n", baluster_positions[0][0], baluster_positions[0][2]);

                fclose(fp);
        }
}

void save_progress(double baluster_positions[][3]) {
        FILE *fp = fopen("progress.txt", "r+"); //reading and writing

        if (fp != NULL) {
                printf( "Saving your progress!\n" );

                int i = 0;
                double p1;
                double p2;
                for(i = 0; i < 16; i+= 1) {
                        p1 = baluster_positions[i][0];
                        p2 = baluster_positions[i][2];
                        //write to file
                        fprintf(fp, "%f %f\n", p1, p2);
                }

                fclose(fp);
        } else
        {
                printf( "Error: Unable to save progress!");
        }
}
