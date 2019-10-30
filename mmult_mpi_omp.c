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
MPI_Status status;
int mmult_omp(double *c, double *a, int aRows, int aCols, double *b, int bRows, int bCols);

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
  int myid, numprocs, dest, numworker, offset,numsent,sender,anstype, row,i,j,k;
  
  double *cc3; //* A x B computed usng omp *//

  double starttime, endtime;
  double *buff, ans;
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
    cc2  = malloc(sizeof(double) * nrows * nrows);
    numworker = numprocs - 1; // sets up the amount that need to be received from
    aa = read_matrix(f_mat_a, &nrows);
    bb = read_matrix(f_mat_b, &nrows);
    ncols = nrows;
    buff = (double *)malloc(sizeof(double) * ncols);
    if (myid == 0) {
      //nrows = 0;
      // Master Code goes here
      //aa = read_matrix(f_mat_a, &nrows);
      //bb = read_matrix(f_mat_b, &nrows);
      //ncols = nrows;
      printf("CUR DIMS [%d]\n", nrows);
      row = nrows/numworker;
      // offset = 0;
      cc1 = malloc(sizeof(double) * nrows * nrows); 
      starttime = MPI_Wtime();
      /* Insert your master code here to store the product into cc1 */
      mmult_slow(cc1, aa, nrows, ncols, bb, ncols, nrows);
      endtime = MPI_Wtime();
      fprintf(fp, "SLOW %d %f\n",nrows*ncols, (endtime - starttime));
      //cc2  = malloc(sizeof(double) * nrows * nrows);
      starttime = MPI_Wtime();
      double *cc4 = malloc(sizeof(double)*nrows*ncols);
      /* Insert your master code here to store the product into cc1 */
      mmult(cc4, aa, nrows, ncols, bb, ncols, nrows);
      endtime = MPI_Wtime();
      fprintf(fp, "FAST %d %f\n",nrows*ncols, (endtime - starttime));
      starttime = MPI_Wtime();
      numsent = 0;
      MPI_Bcast(bb,ncols*nrows,MPI_DOUBLE,0,MPI_COMM_WORLD);
      for(int i = 0; i<min(numworker,nrows);i++){
	for(int j = 0; j < ncols; j++ ){
	  buff[j] = aa[i*ncols+j];
	}
	MPI_Send(buff,ncols,MPI_DOUBLE,i+1,i+1,MPI_COMM_WORLD);
	numsent++;
      }
      for(int i = 0; i < nrows; i++ ){
	MPI_Recv(&ans,1,MPI_DOUBLE,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
        anstype = status.MPI_TAG;
        sender = status.MPI_SOURCE;
	cc2[(anstype-1)] = ans;
	if(numsent < nrows){
	  for(int j = 0; j < ncols; j++){
	    buff[j] = aa[numsent*ncols+j];
	  }
	  MPI_Send(buff,ncols,MPI_DOUBLE,sender,numsent+1,MPI_COMM_WORLD);
	  numsent++;
	} else {
	  MPI_Send(MPI_BOTTOM,0,MPI_DOUBLE,sender,0,MPI_COMM_WORLD);
	}
      }
      endtime = MPI_Wtime();
      fprintf(fp, "MPI %d %f\n",nrows*ncols, (endtime - starttime));
      printf("DEBUGGING MPI CALLS RECV in master: %d %d\n",row, offset);

      
      cc3 = malloc(sizeof(double) *nrows * nrows);
      starttime = MPI_Wtime();
      mmult_omp(cc3, aa, nrows, ncols, bb, ncols, nrows);
      endtime = MPI_Wtime();
      fprintf(fp,"OMP %d %f\n",nrows*ncols, (endtime-starttime));
      compare_matrices(cc3,cc1,nrows, nrows);

      compare_matrices(cc2, cc1, nrows, nrows);
      fclose(fp);
    } else {
      // Slave Code goes here
      /*
        recv from dest for loop set dest to 0
        do matrix multiplication
        send the multiplied matrix back
      */
      
      puts("receiving from master");
      int row_inc = row;
      MPI_Bcast(bb,ncols*nrows,MPI_DOUBLE,0,MPI_COMM_WORLD);
      if(myid <= nrows){
	while(1){
	  MPI_Recv(buff,ncols,MPI_DOUBLE,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&status);
	  if(status.MPI_TAG == 0){
	    break;
	  }
	  row = status.MPI_TAG;
	  ans = 0.0;
	  for(int i = 0; i < nrows; i++){
	   ans+=buff[i]*bb[i*ncols+row];
	  }
	  MPI_Send(&ans,1,MPI_DOUBLE,0,row,MPI_COMM_WORLD);
	}
      }
    }
  } else {
    fprintf(stderr, "Usage matrix_times_vector <size>\n");
  }
  MPI_Finalize();
  return 0;
}
