/*	map_gen.c
 *	
 *	Function library for map generator.
 *	Written by Crow.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "map_gen.h"

map_t new_world;

// Handles memory allocation of map.
void createWorld() {

    srand(time(NULL));

    // Load default contents of of each tile to "X"
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            new_world.grid[i][j] = malloc(sizeof(tile_t));
            strcpy(new_world.grid[i][j]->contents, "X");
        }
    }

    // Populate the world
    set_water();
    set_water();
    set_woods();
    set_mountains();
    set_mountains();
    //set_fort();
    set_grass();

}

// Print map to console.
void printWorld() {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            printf("%s", new_world.grid[i][j]->contents);
        }
        printf("\n");
    }
}

// Option to set a fort with walls in the middle of the map.
void set_fort() {
    int row = ROW / 2;
    int col = COL / 2;

    strcpy(new_world.grid[row][col]->contents, "{F}");

    // Tiles around fort
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i != 0 || j != 0) {
                strcpy(new_world.grid[row + i][col + j]->contents, wall);
            }
        }
    }
}

// Attempts to create random bodies of water on the map.
void set_water() {
    int seed_row = dice(1, ROW);
    int seed_col = dice(1, COL);

    for (int i = 0; i < seed_row; i++) {
        strcpy(new_world.grid[i][seed_col]->contents, water);
    }
    for (int i = 0; i < seed_col; i++) {
        strcpy(new_world.grid[seed_row][i]->contents, water);
    }

    int lake_num = dice(1, 5);
    for (int i = 0; i < lake_num; i++) {
        seed_row = rand() % ROW;
        seed_col = rand() % COL;
        int lake_width = dice(1, 7);
        int lake_length = dice(1, 7);

        if (seed_row + lake_length > ROW) lake_length = ROW - seed_row;
        if (seed_col + lake_width > COL) lake_width = COL - seed_col;

        for (int j = 0; j < lake_length; j++) {
            strcpy(new_world.grid[seed_row + j][seed_col]->contents, water);
        }
        for (int j = 0; j < lake_width; j++) {
            strcpy(new_world.grid[seed_row][seed_col + j]->contents, water);
        }
    }
}

// Sets vegetation including forests, thickets, and grass.
// The four passes are an attempt to hit all the banks of the bodies of water.
void set_woods() {
    int water_flag = 0;

    // Pass one: Left to right, top to bottom.
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (strcmp(new_world.grid[i][j]->contents, water) == 0) {
                water_flag = 1;
                continue;
            }

            if (water_flag) {
                switch (dice(1, 6)) {
                    case 1:
                    case 2:
			strcpy(new_world.grid[i][j]->contents, water);
			water_flag = 0;
			break;
                    case 3:
                        strcpy(new_world.grid[i][j]->contents, thicket);
                        water_flag = 1;
                        break;
                    case 4:
                        strcpy(new_world.grid[i][j]->contents, forest);
                        water_flag = 1;
                        break;
                    case 5:
                    case 6:
                        strcpy(new_world.grid[i][j]->contents, grass);
                        water_flag = 0;
                        break;
                }
            } else {
                switch (dice(1, 3)) {
                    case 1:
                        strcpy(new_world.grid[i][j]->contents, forest);
                        break;
                    case 2:
                        strcpy(new_world.grid[i][j]->contents, thicket);
                        break;
                    case 3:
                        strcpy(new_world.grid[i][j]->contents, grass);
                        break;
                }
            }
        }
    }

    // Pass two: Right to left, top to bottom.
    for (int i = ROW - 1; i > 0; i--) {
        for (int j = COL -1; j > 0; j--) {
            if (strcmp(new_world.grid[i][j]->contents, water) == 0) {
                water_flag = 1;
                continue;
            }

            if (water_flag) {
                switch (dice(1, 6)) {
                    case 1:
                    case 2:
			strcpy(new_world.grid[i][j]->contents, water);
			water_flag = 0;
			break;
                    case 3:
                        strcpy(new_world.grid[i][j]->contents, thicket);
                        water_flag = 1;
                        break;
                    case 4:
                        strcpy(new_world.grid[i][j]->contents, forest);
                        water_flag = 1;
                        break;
                    case 5:
                    case 6:
                        strcpy(new_world.grid[i][j]->contents, grass);
                        water_flag = 0;
                        break;
                }
            } else {
                switch (dice(1, 3)) {
                    case 1:
                        strcpy(new_world.grid[i][j]->contents, forest);
                        break;
                    case 2:
                        strcpy(new_world.grid[i][j]->contents, thicket);
                        break;
                    case 3:
                        strcpy(new_world.grid[i][j]->contents, grass);
                        break;
                }
            }
        }
    }

    // Pass three: Right to left, bottom to top.
    for (int i = COL - 1; i > 0; i--) {
        for (int j = ROW -1; j > 0; j--) {
            if (strcmp(new_world.grid[i][j]->contents, water) == 0) {
                water_flag = 1;
                continue;
            }

            if (water_flag) {
                switch (dice(1, 6)) {
                    case 1:
                    case 2:
			strcpy(new_world.grid[i][j]->contents, water);
			water_flag = 0;
			break;
                    case 3:
                        strcpy(new_world.grid[i][j]->contents, thicket);
                        water_flag = 1;
                        break;
                    case 4:
                        strcpy(new_world.grid[i][j]->contents, forest);
                        water_flag = 1;
                        break;
                    case 5:
                    case 6:
                        strcpy(new_world.grid[i][j]->contents, grass);
                        water_flag = 0;
                        break;
                }
            } else {
                switch (dice(1, 3)) {
                    case 1:
                        strcpy(new_world.grid[i][j]->contents, forest);
                        break;
                    case 2:
                        strcpy(new_world.grid[i][j]->contents, thicket);
                        break;
                    case 3:
                        strcpy(new_world.grid[i][j]->contents, grass);
                        break;
                }
            }
        }
    }

    // Pass four: Right to left, top to bottom.
    for (int i = 0; i < COL; i++) {
        for (int j = 0; j < ROW; j++) {
            if (strcmp(new_world.grid[i][j]->contents, water) == 0) {
                water_flag = 1;
                continue;
            }

            if (water_flag) {
                switch (dice(1, 6)) {
                    case 1:
                    case 2:
			strcpy(new_world.grid[i][j]->contents, water);
			water_flag = 0;
			break;
                    case 3:
                        strcpy(new_world.grid[i][j]->contents, thicket);
                        water_flag = 1;
                        break;
                    case 4:
                        strcpy(new_world.grid[i][j]->contents, forest);
                        water_flag = 1;
                        break;
                    case 5:
                    case 6:
                        strcpy(new_world.grid[i][j]->contents, grass);
                        water_flag = 0;
                        break;
                }
            } else {
                switch (dice(1, 3)) {
                    case 1:
                        strcpy(new_world.grid[i][j]->contents, forest);
                        break;
                    case 2:
                        strcpy(new_world.grid[i][j]->contents, thicket);
                        break;
                    case 3:
                        strcpy(new_world.grid[i][j]->contents, grass);
                        break;
                }
            }
        }
    }
}

// Create a random number of mountains.
void set_mountains() {
    int num_mountains = dice(4, 4);

    for (int m = 0; m < num_mountains; m++) {
        int mtn_row = dice(1, ROW - 2);
        int mtn_col = dice(1, COL - 2);
        int mtn_length = dice(1, 4);
        int mtn_width = dice(1, 4);

        if (mtn_length + mtn_row > ROW) mtn_length = ROW - mtn_row;
        if (mtn_width + mtn_col > COL) mtn_width = COL - mtn_col;

        for (int i = 0; i < mtn_length; i++) {
            for (int j = 0; j < mtn_width; j++) {
                if (strcmp(new_world.grid[mtn_row + i][mtn_col + j]->contents, "X") != 0) {
                    strcpy(new_world.grid[mtn_row + i][mtn_col + j]->contents, mountain);
                }
            }
        }
    }
}

// "Catch all" to eliminate any remaining empty tiles with grsas or oats.
void set_grass() {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (strcmp(new_world.grid[i][j]->contents, "X") == 0 || strcmp(new_world.grid[i][j]->contents, grass) == 0) {
                switch (dice(1, 3)) {
                    case 1:
                        strcpy(new_world.grid[i][j]->contents, grass);
                        break;
                    case 2:
                        strcpy(new_world.grid[i][j]->contents, oats);
                        break;
                }
            }
	   if (strcmp(new_world.grid[i][j]->contents, mountain) == 0) {
		switch (dice(1,3)) {
			case 1: strcpy(new_world.grid[i][j]->contents, grass); break;
		}
	   }
        }
    }
}

// Dice roller program.
int dice(int number, int sides) {
    int sum = 0;
    for (int i = 0; i < number; i++) {
        sum += (rand() % sides) + 1;
    }
    return sum;
}
