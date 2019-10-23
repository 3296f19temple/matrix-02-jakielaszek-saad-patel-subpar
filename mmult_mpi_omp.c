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
  int myid, numprocs;
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
    
    if (myid == 0) {
      nrows = 0;
      // Master Code goes here
      aa = read_matrix(f_mat_a, &nrows);
      bb = read_matrix(f_mat_b, &nrows);
      
      ncols = nrows;

      cc1 = malloc(sizeof(double) * nrows * nrows); 
      starttime = MPI_Wtime();
      /* Insert your master code here to store the product into cc1 */
      mmult_slow(cc1, aa, nrows, ncols, bb, ncols, nrows);
      endtime = MPI_Wtime();
      fprintf(fp, "FAST %d %f\n",nrows*ncols, (endtime - starttime));
      cc2  = malloc(sizeof(double) * nrows * nrows);
      starttime = MPI_Wtime();
      mmult(cc2, aa, nrows, ncols, bb, ncols, nrows);
      endtime = MPI_Wtime();
      fprintf(fp, "SLOW %d %f\n",nrows*ncols, (endtime - starttime));

      compare_matrices(cc2, cc1, nrows, nrows);

      fclose(fp);
    } else {
      // Slave Code goes here
    }
  } else {
    fprintf(stderr, "Usage matrix_times_vector <size>\n");
  }
  MPI_Finalize();
  return 0;
}
