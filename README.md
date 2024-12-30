# Parallel_Systems_Assignment1
The second assignment in the subjet of di's parallel systems. The second assignment focus on openmp usage in various use cases.


modules contains the source code for exercises 1 and 2 as also the implementation of functions that was used in exercise 1.

scripts directory contains some bash scripts which runs an exercise for 3 different sizes and lots of different number of threads. The execution time of each execution is written in a csv file which is used later by the python script to extract the diagrams that were used in the official ReadMe.

tests directory contains a standard pattern of game of life in order to check the correctness of the algorithm that was used in exercise1. To run the test go to tests directory and type make run.

In order to compile the exercises on the main directory just type make. Then you can run the exercises by going to modules directory and type normally ./exercise1/2 followed by the values of the instance you want to execute. Othwewise you can just run the scripts by compiling the bash script eg. "chmod +x exercise1.sh" and then execute it by ./exercise1.sh . 
Executing a bash script will also update the csv files.