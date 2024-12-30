
# include<omp.h>
#include <stdio.h>
void parallel_updating_grid(int*** grid,int***temp_grid,int num_of_threads,int size_of_grid){
    //calculating how many alive neighbors each collumn have

    #pragma omp parallel for num_threads(num_of_threads) schedule(static)
    for(int row=0;row<size_of_grid;row++){
        for(int collumn = 0; collumn < size_of_grid;collumn++){
            int counter_if_Is=0;
            int curr_state = (*grid)[row][collumn];
            for(int checking_row = row-1; checking_row<=row+1;checking_row++){
                for(int checking_collumn = collumn-1;checking_collumn<=collumn+1;checking_collumn++){
                    if((checking_row>=0 && checking_row<size_of_grid) && (checking_collumn>=0 && checking_collumn<size_of_grid)){
                        if(checking_row== row &&checking_collumn==collumn){
                            continue;
                        }
                        if((*grid)[checking_row][checking_collumn]==1)
                            counter_if_Is++;
                    }
                }

               

            }

            //applying the rules!
            if(curr_state==1){ //if it's initially alive then:
                if(counter_if_Is<2 || counter_if_Is>3)
                    (*temp_grid)[row][collumn] = 0; //assigning it as dead (loneliness)
                else
                    (*temp_grid)[row][collumn] = 1; //staying the same(alive)
            }
            else
                if(counter_if_Is==3)
                    (*temp_grid)[row][collumn]=1; //the state becomes alive (neighbors ==3)
                else
                    (*temp_grid)[row][collumn]=0; //staying dead

        }
        
    }

    // swap pointers
    int **temp = *grid;
    *grid = *temp_grid;
    *temp_grid = temp;    
}


void updating_grid(int*** grid,int***temp_grid,int size_of_grid){
    for(int row=0;row<size_of_grid;row++){
        for(int collumn = 0; collumn < size_of_grid;collumn++){
            int counter_if_Is=0;
            int curr_state = (*grid)[row][collumn];
            for(int checking_row = row-1; checking_row<=row+1;checking_row++){
                for(int checking_collumn = collumn-1;checking_collumn<=collumn+1;checking_collumn++){
                    if((checking_row>=0 && checking_row<size_of_grid) && (checking_collumn>=0 && checking_collumn<size_of_grid)){
                        if(checking_row== row &&checking_collumn==collumn){
                            continue;
                        }
                        if((*grid)[checking_row][checking_collumn]==1)
                            counter_if_Is++;
                    }
                }

               

            }

            //applying the rules!
            if(curr_state==1){ //if it's initially alive then:
                if(counter_if_Is<2 || counter_if_Is>3)
                    (*temp_grid)[row][collumn] = 0; //assigning it as dead (loneliness)
                else
                    (*temp_grid)[row][collumn] = 1; //staying the same(alive)
            }
            else
                if(counter_if_Is==3)
                    (*temp_grid)[row][collumn]=1; //the state becomes alive (neighbors ==3)
                else
                    (*temp_grid)[row][collumn]=0; //staying dead

        }
        
    }

    // swap pointers
    int **temp = *grid;
    *grid = *temp_grid;
    *temp_grid = temp;    
}
