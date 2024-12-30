#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "timer.h"

//initialing nxn upper triangular with random values from 0-9
void initialize_upper_triangular_matrix(int n, int** A, int* b) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j >= i) {
                A[i][j] = (int)(rand() %9 +1 );  // Τυχαίοι αριθμοί 1-10
            } else {
                A[i][j] = 0;  // Μηδενικά κάτω από τη διαγώνιο
            }
        }
        b[i] = (int)(rand() % 10 + 1);  // Τυχαίοι αριθμοί 1-10
    }
}

//self-explanatory
void printing_matrix(int**A,int n,int*b){
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%d",A[i][j]);
        }
        printf("   %d",b[i]);
        printf("\n");fflush(stdout);
    }
}
//same
void printing_results(double*x,int n ){
    for(int i =0;i<n;i++){
        printf("x%d is %f\n",i,x[i]);fflush(stdout);
    }
}


void serial_byRow(double* x,int n, int*b, int**A){

    for (int row = n-1; row >= 0; row--) {
        x[row] = b[row];
        for (int col = row+1; col < n; col++)
            x[row] -= A[row][col]*x[col];
        x[row] /= A[row][row];
}
}

//loosesly based on this paper: https://www.researchgate.net/publication/359143805_Parallel_implementation_of_solving_linear_equations_using_OpenMP#pf7 ,chapter 3.1

void parallel_byRow(double* x, int n, int*b, int**A,int thread_count){
    for(int i= n-1; i>=0; i--){
        double temp = b[i]; //each thread will have its own temp variable

        //parallelizing the calculation of x[row] because it's based on calculations that have already been done
        #pragma omp parallel for num_threads(thread_count)\
            reduction(+:temp)
            for(int j=i+1;j<=n-1;j++){
                temp = temp-(A[i][j]*x[j]);
                }

        x[i] = temp / A[i][i]; 
    }
}

void parallel_byCollumn(double *x, int n , int*b, int** A,int thread_count){
    //parallelizing the initialization of x array
    #pragma omp parallel for num_threads(thread_count) schedule(static)
        for(int row=0; row<n;row++)
            x[row]=b[row];
        
        for(int j = n-1; j>=0; j--){ //this cannot be parallelized because x[j-1] needs x[j] to be calculated
            x[j] /= A[j][j];

            //parallelizing the inner calculation(this calculation is indepedent, it only accesses elements that have already been calculated)
            #pragma omp parallel for num_threads(thread_count)
                for( int i=0;i<j;i++){
                    #pragma omp atomic //it will be executed only by 1 thread at a time, thus avoidin race condtions.
                        x[i] -= (A[i][j]*x[j]);
                }
        }


}


void serial_byCollumn(double* x,int n, int*b, int**A){
    for (int row = 0; row < n; row++)
        x[row] = b[row];
    for (int col = n-1; col >= 0; col--) {
        x[col] /= A[col][col];
        for (int row = 0; row < col; row++)
            x[row] -= A[row][col]*x[col];
    }
}



//./exercise2 sizeOfMatrix( 0=parallel / 1=serial ) (0=row algorithm / 1=Collumn algorithm) NumberOfThreads

int main(int argc,char**argv){
        int n=strtol(argv[1],NULL,10);
        int Is_serial = strtol(argv[2],NULL,2);
        int Is_row_or_collumn = strtol(argv[3],NULL,2); //if 0 is rows,else if 1 is collumns
        int num_of_threads = strtol(argv[4],NULL,10);
   
    int** A = malloc(n* sizeof(int*));
    for(int i=0;i<n;i++)   
        A[i]=malloc(n*sizeof(int));
    
    int* b = malloc(n*sizeof(int));
    double* x = malloc(n*sizeof(double));
    initialize_upper_triangular_matrix(n,A,b);


    double before,now;
    //if it's parallel we execute the parallel row/collumn function else the serial functions

    if(Is_serial==0){
        if(Is_row_or_collumn==0){
            GET_TIME(before)
            parallel_byRow (x,n,b,A,num_of_threads);  
            GET_TIME(now);
        }
        else{
            GET_TIME(before)
            parallel_byCollumn(x,n,b,A,num_of_threads);
            GET_TIME(now);
        }

    }
    else{
        if(Is_row_or_collumn==0){
            GET_TIME(before);
            serial_byRow(x,n,b,A);
            GET_TIME(now);
        }
        else{
            GET_TIME(before);
            serial_byCollumn(x,n,b,A);
            GET_TIME(now);
        }
    }
    double elapsed_time = now-before;
    printf("%f\n",elapsed_time);fflush(stdout); //calculatinh and printing the elapsed time

    for(int i=0;i<n;i++)
        free(A[i]);

    free(A);
    free(b);




}



