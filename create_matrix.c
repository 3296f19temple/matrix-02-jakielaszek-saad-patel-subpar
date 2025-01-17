#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double* gen_matrix(int n, int m);

int main(int argc, char ** argv){
  int dims = atoi(argv[1]);
  int power = 1;
  int k = 0;
  for(k = 0; k < dims; k++){
    power *= 2;
  }
  dims=power;
  char * fname = argv[2];

  double * matrix = gen_matrix(dims,dims);

  FILE * fp = fopen(fname, "w");

  int i = 0;
  for(i = 0; i < dims; i++){
    int j = 0;
    for(j = 0; j < dims-1; j++){
      fprintf(fp, "%lf ", matrix[i*dims+j]);
    }
    fprintf(fp, "%lf\n", matrix[i*dims+j]);
  }

  fclose(fp);
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
