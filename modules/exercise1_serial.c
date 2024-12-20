#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "my_rand.h"
# include <omp.h>
/* Εάν ένας οργανισμός (κατειλημμένη θέση) έχει λιγότερους από 2 γειτονικούς οργανισμούς, ο οργανισμός
πεθαίνει από μοναξιά.
 Εάν ένας οργανισμός έχει 2 ή 3 γειτονικούς οργανισμούς, ο οργανισμός επιζεί στην επόμενη γενιά.
 Εάν ένας οργανισμός έχει περισσότερους από 3 γειτονικούς οργανισμούς, ο οργανισμός πεθαίνει λόγω
υπερπληθυσμού.
 Εάν μία μη κατειλημμένη θέση έχει ακριβώς 3 γειτονικούς οργανισμούς, αυτή η θέση θα καταληφθεί στην
επόμενη γενιά από έναν νέο οργανισμό, δηλαδή ένας οργανισμός γεννιέται.*/
int size_of_grid=64;


void updating_grid(int*** grid,int***temp_grid){
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

                //applying the rules!
                if(curr_state==1){ //if it's initially alive then:
                    if(counter_if_Is<2 || counter_if_Is>3)
                        (*temp_grid)[row][collumn] = 0; //assigning it as dead (loneliness)
                    else
                        (*temp_grid)[row][collumn] = 1;
                }
                else
                    if(counter_if_Is==3)
                        (*temp_grid)[row][collumn]=1; //the state becomes alive (neighbors ==3)
                    else
                        (*temp_grid)[row][collumn]=0;

            }



        }
        
    }
    // swap pointers
    int **temp = *grid;
    *grid = *temp_grid;
    *temp_grid = temp;    
}





int main(int argc,char**argv){
    int num_of_births = 100;
    int size_of_grid=64;
    int Is_serial=0; //1 if it's parallel 0 if it's serial
    int number_of_threads=0;

    //passing values from command line
    if (argc>1){
        num_of_births = strtol(argv[1],NULL,10);
        size_of_grid=strtol(argv[2],NULL,10);
        Is_serial = strtol(argv[3],NULL,2);
        number_of_threads = strtol(argv[4],NULL,10);
    }

    //random  birth initialization
    srand(time(NULL));
    int** grid = malloc(size_of_grid*sizeof(int*));
    int** temp_grid = malloc(size_of_grid*sizeof(int*));
    for (int i = 0; i < size_of_grid; i++) {
        grid[i] = malloc(size_of_grid * sizeof(int));
        temp_grid[i] = malloc(size_of_grid * sizeof(int));
}
    
        for(int row =0;row<size_of_grid;row++){
            for(int collumn = 0; collumn < size_of_grid;collumn++){
                    unsigned int random_seed = rand();
                    random_seed ^= (row + collumn); // XOR with (row+column) in order to make the seed vary
                    int state_of_point = (my_drand(&random_seed) > 0.5) ? 1 : 0; //if my drand returns a double >0.5 then assign it as 1 else as 0

                    grid[row][collumn] = state_of_point;
                    temp_grid[row][collumn] = state_of_point;
            }
        }
        if(Is_serial == 0){
            printf("I am outsidee \n");fflush(stdout);
            while(num_of_births>0){
                updating_grid(&grid,&temp_grid);
                num_of_births--;

            }
        }

        else{
           #pragma omp parallel for num_threads(number_of_threads) 
        }



    //deallocating the 2d array.
    for(int i =0;i<size_of_grid;i++){
        free(grid[i]);
        free(temp_grid[i]);
    }
    free(grid);
    free(temp_grid);
}