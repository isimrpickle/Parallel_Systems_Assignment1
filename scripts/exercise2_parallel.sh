#!/bin/bash

#running for 4 times for each different matrix size(100/1000/10000) the parallel algorithm by row and then for 4 times byCollumn
# the execution time for each instance is saved in a csv file


    output_file="parallel_execution_times.csv"
    echo "matrix_size,Is_serial,Is_row_or_collumn,thread_num,Execution_time" > $output_file

for Is_serial in 0; do
    for Is_row_or_collumn in 0 1; do
        for matrix_size in 100 1000 10000; do
            for thread_num in 1 2 4 8 16 32; do
                for iteration in 1 2 3 4; do
                    execution_time=$(/home/users/sdi2000233/Parallel_Systems_Assignment1/modules/exercise2 $matrix_size $Is_serial $Is_row_or_collumn $thread_num )
                    echo "$matrix_size,$Is_serial,$Is_row_or_collumn,$thread_num,$execution_time" >> $output_file
                done
            done
        done
    done
done