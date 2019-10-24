#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#define min(x, y) ((x)<(y)?(x):(y))

double* gen_matrix(int n, int m);
int mmult(double *c, double *a, int aRows, int aCols, double *b, int bRows, int bCols);
int mmult_slow(double *c, double *a, int aRows, int aCols, double *b, int bRows, int bCols);
void compare_matrix(double *a, double *b, int nRows, int nCols);
double* read_matrix(char * fname, int *dims);

/** 
    Program to multiply a matrix times a matrix using both
    mpi to distribute the computation among nodes and omp
    to distribute the computation among threads.
*/

int main(int argc, char* argv[])
{
  int nrows, ncols;
  double *aa;	/* the A matrix */
  double *bb;	/* the B matrix */
  double *cc1;	/* A x B computed using the omp-mpi code you write */
  double *cc2;	/* A x B computed using the conventional algorithm */
  double *AA; //* A matrix read from file*//
  double *BB; // B matrix read from file*//
  int myid, numprocs, dest, numworker, offset, row,i,j,k;
  double starttime, endtime;
  MPI_Status status;
  /* insert other global variables here */
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  if (argc > 1) {

    char * logFile = argv[3];
    FILE * fp = fopen(logFile, "a");

    char * f_mat_a = argv[1];
    char * f_mat_b = argv[2];

    numworkers = numprocs - 1; // sets up the amount that need to be received from
    if (myid == 0) {
      nrows = 0;
      // Master Code goes here
      aa = read_matrix(f_mat_a, &nrows);
      bb = read_matrix(f_mat_b, &nrows);
      ncols = nrows;
      printf("CUR DIMS [%d]\n", nrows);
      row = nrows/numworker;
      offset = 0;
      cc1 = malloc(sizeof(double) * nrows * nrows); 
      starttime = MPI_Wtime();
      /* Insert your master code here to store the product into cc1 */
      /*
        for(dest = 1; dest <= numworker; dest++){
          MPI send col MPI_INT
          MPI send row MPI_INT
          MPI send a[col][0] row*nrows
          MPI send b ncol*ncol
          col+=row
        }
        for(i=1;  i < numworker: i++){
          recv col
          recv row
          recv c[col][0]
        }
        print to log files
      */
      mmult_slow(cc1, aa, nrows, ncols, bb, ncols, nrows);
      endtime = MPI_Wtime();
      fprintf(fp, "SLOW %d %f\n",nrows*ncols, (endtime - starttime));
      cc2  = malloc(sizeof(double) * nrows * nrows);
      starttime = MPI_Wtime();
      mmult(cc2, aa, nrows, ncols, bb, ncols, nrows);
      endtime = MPI_Wtime();
      fprintf(fp, "FAST %d %f\n",nrows*ncols, (endtime - starttime));

      compare_matrices(cc2, cc1, nrows, nrows);

      fclose(fp);
    } else {
      // Slave Code goes here
      /*
        recv from dest for loop set dest to 0
        do matrix multiplication
        send the multiplied matrix back
      */
    }
  } else {
    fprintf(stderr, "Usage matrix_times_vector <size>\n");
  }
  MPI_Finalize();
  return 0;
}

