#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<pthread.h>
#include "my_rand.h"
#include<time.h>

/* Εάν ένας οργανισμός (κατειλημμένη θέση) έχει λιγότερους από 2 γειτονικούς οργανισμούς, ο οργανισμός
πεθαίνει από μοναξιά.
 Εάν ένας οργανισμός έχει 2 ή 3 γειτονικούς οργανισμούς, ο οργανισμός επιζεί στην επόμενη γενιά.
 Εάν ένας οργανισμός έχει περισσότερους από 3 γειτονικούς οργανισμούς, ο οργανισμός πεθαίνει λόγω
υπερπληθυσμού.
 Εάν μία μη κατειλημμένη θέση έχει ακριβώς 3 γειτονικούς οργανισμούς, αυτή η θέση θα καταληφθεί στην
επόμενη γενιά από έναν νέο οργανισμό, δηλαδή ένας οργανισμός γεννιέται.*/







int main(int argc,char**argv){
    int num_of_births = 4;
    int size_of_grid=64;
    int Is_serial=0; //1 if it's parallel 0 if it's serial
    int number_of_threads=0;

    if (argc>1){
        num_of_births = strtol(argv[1],NULL,10);
        size_of_grid=strtol(argv[2],NULL,10);
        Is_serial = strtol(argv[3],NULL,2);
        number_of_threads = strtol(argv[4],NULL,10);
    }

    //random  birth initialization
    int counter = 0;
    int** grid = malloc(size_of_grid*sizeof(int*));
    for (int i = 0; i < size_of_grid; i++) {
        grid[i] = malloc(size_of_grid * sizeof(int));
}
    while(counter<num_of_births){  //ensuring that all the initial birthss have been enforced(In the extreme case it doesn't happen in the first iteration of th grid)
        for(int row =0;row<size_of_grid;row++){
            for(int collumn = 0; collumn < size_of_grid;collumn++){
                    unsigned int random_seed = collumn*row;
                    if(counter < num_of_births){
                        int state_of_point = (my_drand(&random_seed) > 0.5) ? 1 : 0; //if my drand returns a double >0.5 then assign it as 1 else as 0
                        grid[row][collumn] = state_of_point;
                        if(state_of_point==1){
                            printf("counter increased!!\n");
                            counter++;
                        }
                }
                else{
                    grid[row][collumn]=0;
                }
            }
        }
    }

    


    //deallocating the 2d array.
    for(int i =0;i<size_of_grid-1;i++){
        free(grid[i]);
    }
    free(grid);



    

}