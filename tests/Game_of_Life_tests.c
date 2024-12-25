#include "acutest.h"
#include <stdio.h>
#include "my_rand.h"
#include "exercise1.h"


void test(){


/* creating a standard pattern of game of life called blinker  which should return some standard results 
https://conwaylife.com/wiki/blinker*/
    int size_of_grid = 5;
    int** grid = (int**)malloc(size_of_grid * sizeof(int*));
    int** temp_grid = (int**)malloc(size_of_grid * sizeof(int*));
    for (int i = 0; i < size_of_grid; i++) {
        grid[i]= (int*)malloc(size_of_grid* sizeof(int));
        temp_grid[i] = (int*)malloc(size_of_grid* sizeof(int));
    }

    // Initialize blinker pattern
    for(int i =0;i<size_of_grid;i++){
        for(int j=0;j<size_of_grid;j++){
            grid[i][j]=0;
        }
    }
    //initializing the 3-sized horizontal line as alive
    grid[2][1]= grid[2][2]= grid[2][3] =1;

    //calling the serial function which updates the grid
    updating_grid(&grid, &temp_grid);

    //verifying that the horizontal line turns into a vertical line
    TEST_CHECK(grid[1][2] == 1 && grid[2][2] == 1 && grid[3][2] == 1);
    TEST_CHECK(grid[2][1] == 0 && grid[2][3] == 0);

    //re-initializing the grid and the first state of blinker transformation

    for(int i =0;i<size_of_grid;i++){
        for(int j=0;j<size_of_grid;j++){
            grid[i][j]=0;
            temp_grid[i][j]=0;
        }
    }

    //with the same logic checking now the functionality of the parallel update.
    grid[2][1] = grid[2][2] = grid[2][3] = 1;
    int num_of_threads=4;
    parallel_updating_grid(&grid, &temp_grid,num_of_threads);
    
    TEST_CHECK(grid[1][2] == 1 && grid[2][2] == 1 && grid[3][2] == 1);
    TEST_CHECK(grid[2][1] == 0 && grid[2][3] == 0);


    // freeing the two arrays
    for (int i = 0; i < size_of_grid; i++) {
        free(grid[i]);
        free(temp_grid[i]);
    }
    free(grid);
    free(temp_grid);








}

// void Game_of_Life_Parallel(){

// }









TEST_LIST ={
    {"Game_of_Life_serial",test},
    // {"Game_of_Life_Parallel",Game_of_Life_Parallel},
    {"NULL",NULL}
};