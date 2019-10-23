#include<stdio.h>
#include<stdlib.h>
#include<string.h>


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

void compare_matrices(double* a, double* b, int nRows, int nCols) {
        int n = nRows * nCols;
        int i, j, k;
        for (k = 0; k < n; ++k) {
                if (fabs(a[k]-b[k])/fabs(a[k]) > 1e-12) {
                        i = k/nCols;
                        j = k%nCols;
                        printf("a[%d][%d] == %.12g\nb[%d][%d] == %.12g\ndelta == %.12g\nrelerr == %.12g\n",
                                i, j, a[k], i, j, b[k], fabs(a[k]-b[k]), fabs(a[k]-b[k])/fabs(a[k]));
                        return;
                }
        }
        printf("Matrices are the same\n");
}

void writeMatrix(char *fileName, double* a, int rows, int cols){
        FILE *fp = fopen(fileName, "w");
        if(fp == NULL){
                printf("Error opening %s file to write", fileName);
        }
        fprintf(fp,"%d %d\n",rows,cols);
        for(int i =0; i < rows*cols; i++){
                fprintf(fp,"%lf ",a[i]);
        }
        fclose(fp);
}



