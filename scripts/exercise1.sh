#!/bin/bash

#runs the exercise 1 for different instances and save the results in a csv file

echo -e " Enter num of births you want."

read num_of_births

echo -e "Enter 1 for parallel execution or 0 for serial execution:"

read Is_parallel
#creating csv files for the diagrams later
output_file="execution_times.csv"
echo "Grid_Size,Num_Threads,Num_Births,Is_parallel,Execution_Time" > $output_file #initializing the format that each value will be printed

for size_of_grid in 64 1024 4096; do
    for thread_number in 1 2 4 8 16 32; do
        for iteration in 1 2 3 4; do
                execution_time=$(/home/users/sdi2000233/Parallel_Systems_Assignment1/modules/exercise1 $num_of_births $size_of_grid $Is_parallel $thread_number)
                echo "$size_of_grid,$thread_number,$num_of_births,$Is_parallel,$execution_time" >> $output_file
        done
    done
done