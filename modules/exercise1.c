#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "my_rand.h"
#include "updating_grid.h"
#include "timer.h"
# include<omp.h>
/* Εάν ένας οργανισμός (κατειλημμένη θέση) έχει λιγότερους από 2 γειτονικούς οργανισμούς, ο οργανισμός
πεθαίνει από μοναξιά.
 Εάν ένας οργανισμός έχει 2 ή 3 γειτονικούς οργανισμούς, ο οργανισμός επιζεί στην επόμενη γενιά.
 Εάν ένας οργανισμός έχει περισσότερους από 3 γειτονικούς οργανισμούς, ο οργανισμός πεθαίνει λόγω
υπερπληθυσμού.
 Εάν μία μη κατειλημμένη θέση έχει ακριβώς 3 γειτονικούς οργανισμούς, αυτή η θέση θα καταληφθεί στην
επόμενη γενιά από έναν νέο οργανισμό, δηλαδή ένας οργανισμός γεννιέται.*/






int main(int argc,char**argv){
    int num_of_births = 1000000;
    int size_of_grid=64;
    int Is_serial=1; //1 if it's parallel 0 if it's serial
    int number_of_threads=8;

    //passing values from command line
    if (argc>1){
        num_of_births = strtol(argv[1],NULL,10);
        size_of_grid=strtol(argv[2],NULL,10);
        Is_serial = strtol(argv[3],NULL,2);
        number_of_threads = strtol(argv[4],NULL,10);
    }

    //random  birth initialization
    int** grid = malloc(size_of_grid*sizeof(int*));
    int** temp_grid = malloc(size_of_grid*sizeof(int*));
    for (int i = 0; i < size_of_grid; i++) {
        grid[i] = malloc(size_of_grid * sizeof(int));
        temp_grid[i] = malloc(size_of_grid * sizeof(int));
}
        double before,now;
        for(int row =0;row<size_of_grid;row++){
            for(int collumn = 0; collumn < size_of_grid;collumn++){
                    unsigned int random_seed = rand();
                    random_seed ^= (row + collumn); // XOR with (row+column) in order to make the seed vary
                    int state_of_point = (my_drand(&random_seed) > 0.5) ? 1 : 0; //if my drand returns a double >0.5 then assign it as 1 else as 0

                    grid[row][collumn] = state_of_point;
                    temp_grid[row][collumn] = state_of_point;
            }
        }
        GET_TIME(before);
        if(Is_serial == 0){
            printf("I am outsidee \n");fflush(stdout);
            while(num_of_births>0){
                updating_grid(&grid,&temp_grid,size_of_grid);
                num_of_births--;

            }
        }

        else{
           while(num_of_births>0){
                parallel_updating_grid(&grid,&temp_grid,number_of_threads,size_of_grid);
                num_of_births--;
           }
        }
        GET_TIME(now);
        double elapsed_time=now-before;
        printf("%f",elapsed_time);


    //deallocating the 2d array.
    for(int i =0;i<size_of_grid;i++){
        free(grid[i]);
        free(temp_grid[i]);
    }

    free(grid);
    free(temp_grid);
}