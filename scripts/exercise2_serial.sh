#!/bin/bash
echo -e "Enter the size of triangular matrix:"
read matrix_size

echo -e "Enter 1 for parallel execution or 0 for serial execution:"
read Is_serial

echo -e "Enter 1 to execute by byCollumn or byRow:"
read Is_row_or_collumn

#creating csv files for the diagrams later
    output_file="serial_execution_times.csv"
    echo "matrix_size,Is_serial,Is_row_or_collumn,Execution_time" > $output_file

for Is_serial in 1; do
    for Is_row_or_collumn in 0 1; do
        for matrix_size in 100 1000 10000; do
            for iteration in 1 2 3 4; do
                execution_time=$(/home/users/sdi2000233/Parallel_Systems_Assignment1/modules/exercise2 $matrix_size $Is_serial $Is_row_or_collumn $thread_num )
                echo "$matrix_size,$Is_serial,$Is_row_or_collumn,$execution_time" >> $output_file
            done
        done
    done
done