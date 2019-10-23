#include <stdio.h>
#include <stdlib.h>

void write_matrix(int dim, double * mat, FILE * fp);
double* gen_matrix(int n, int m);

int main(int argc, char ** argv){

  FILE * fp = fopen(argv[1], "w");

  if(fp == NULL){
    printf("ERROR: Could not open file [%s]\n", argv[1]);
    exit(-1);
  }
  
  int i = 2;
  for(int i = 2; i <= 1024; i*=2){
    double * mat1 = gen_matrix(i, i);
    double * mat2 = gen_matrix(i, i);
    write_matrix(i, mat1, fp);
    write_matrix(i, mat2, fp);
  }
  
  fclose(fp);
  return 0;
}

void write_matrix(int dim, double * mat, FILE * fp){
  int length = dim*dim;
  fprintf(fp, "%d ", dim);

  int j;
  for(j = 0; j < length-1; j++){
    fprintf(fp, "%lf ", mat[j]);  
  }
  
  fprintf(fp, "%lf\n", mat[j]);
}

double* gen_matrix(int n, int m) {
  int i, j;
  double *a = malloc(sizeof(double) * n * m);
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      a[i*m + j] = (double)rand()/RAND_MAX;
    }
  }
  return a;
}
