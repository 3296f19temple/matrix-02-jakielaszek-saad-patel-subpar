#include<stdio.h>
#include<stdlib.h>
#include<math.h>

double* gen_matrix(int n, int m);

int main(int argc, char ** argv){
  int dims = atoi(argv[1]);
  char * fname = argv[2];

  double * matrix = gen_matrix(dims,dims);

  FILE * fp = fopen(fname, "w");

  fprintf(fp, "%d ", dims);

  int i = 0;
  for(i = 0; i < dims*dims - 1; i++){
    fprintf(fp, "%lf ", matrix[i]);
  }

  fprintf(fp, "%lf", matrix[i]);
  
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
