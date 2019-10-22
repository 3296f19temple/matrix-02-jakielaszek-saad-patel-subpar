#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#define min(x, y) ((x)<(y)?(x):(y))

double* gen_matrix(int n, int m);
int mmult(double *c, double *a, int aRows, int aCols, double *b, int bRows, int bCols);
void compare_matrix(double *a, double *b, int nRows, int nCols);

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
  int myid, numprocs;
  double starttime, endtime;
  MPI_Status status;
  /* insert other global variables here */
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  if (argc > 1) {
    ////////
    char *matrixA_file = argv[1];
    char *matrixB_file = argv[2];
    int *dimensions_A = getDimensions(matrixA_file);
    int *dimensions_B = getDimensions(matrixB_file);
    //compare dimensions and see if valid multiplication
    if(validMultiply(dimensions_A, dimensions_B)==1){
	//read matrixA and matrixB
	AA = readMatrix(matrixA_file);
	BB = readMatrix(matrixB_file);
    ////////
    nrows = atoi(argv[1]);
    ncols = nrows;
    if (myid == 0) {
      // Master Code goes here
      aa = gen_matrix(nrows, ncols);
      bb = gen_matrix(ncols, nrows);
      cc1 = malloc(sizeof(double) * nrows * nrows); 
      starttime = MPI_Wtime();
      /* Insert your master code here to store the product into cc1 */
      endtime = MPI_Wtime();
      printf("%f\n",(endtime - starttime));
      cc2  = malloc(sizeof(double) * nrows * nrows);
      mmult(cc2, aa, nrows, ncols, bb, ncols, nrows);
      compare_matrices(cc2, cc1, nrows, nrows);
    } else {
      // Slave Code goes here
    }
  } else {
    fprintf(stderr, "Usage matrix_times_vector <size>\n");
  }
  MPI_Finalize();
  return 0;
}
double *readMatrix(char *fileName){
	FILE *file = fopen(fileName, 'r');
	if(file == NULL){
		printf("Error Opening File %s", fileName);
		//exit(0);
	}
	char buffer[1024];
	int nRows, mCols;
	if(fgets(buffer, sizeof(buffer), file)!=NULL){
		sscanf("%d %d", &nRows, &mCols);
	}
	double *matrix = (double*)malloc(sizeof(double)*nRows*mCols);
	char *line;
	//fgets(buffer,1024,file);//skip the first line containing dimensions
		
	while(fgets(buffer, 1024, file)!=NULL){
		line += buffer;
	}	
	
	//tokenize the line and store the array elements
	char *token = strtok(line," ");
	int i =0;
	double *tokens[nRows * mCols];
	tokens[i]= atof(token);
	while(token!=NULL)
		token = strtok(NULL," ");
		tokens[i] = atof(token);
		i++;

	for(int i =0; i<nRows, i++){
		for(int j = 0; j<mCols; j++){
			matrix[i*mCols+j] = tokens[i*mCols+j] ;		
					
	}}
	//free(buffer);
	fclose(file);	
	return matrix;
}

int* getDimensions(char *fileName){
//gets the dimension of the matrix in txt file fileName
	FILE *fp = fopen(fileName, "r");
	if(fp==NULL){
		fprintf("Error Reading file %s",fileName);
		exit(0);
	}
	char buffer[1024];
	int row, col;
	if(fgets(buffer, 1024, fp)!=NULL){
		sscanf("%d %d", &row, &col);
	}
	int dimension[2];
	dimension[0] = row;
	dimension[1] =col;
	return dimension;
}	

int validMultiply( int *a, int *b){
	if(a[1] == b[0])
		return 1;
	else
		return 0;
}
