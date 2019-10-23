#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

int mmult(double *c, 
	  double *a, int aRows, int aCols, 
	  double *b, int bRows, int bCols) {
  int i, j, k;
  for (i = 0; i < aRows; i++) {
    for (j = 0; j < bCols; j++) {
      c[i*bCols + j] = 0;
    }
    for (k = 0; k < aCols; k++) {
      for (j = 0; j < bCols; j++) {
	c[i*bCols + j] += a[i*aCols + k] * b[k*bCols + j];
      }
    }
  }
  return 0;
}

int mmult_slow(double *c, 
	  double *a, int aRows, int aCols, 
	  double *b, int bRows, int bCols) {
  int i, j, k;
  for (i = 0; i < aRows; i++) {
    for (j = 0; j < bCols; j++) {
      c[i*bCols + j] = 0;
      for (k = 0; k < aCols; k++) {
	c[i*bCols + j] += a[i*aCols + k] * b[k*bCols + j];
      }
    }
  }
  return 0;
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

double* read_matrix(char * fname, int *dims){
  FILE * fp = fopen(fname, "r");
  int BUFFSIZE = 100000000;
  char *buffer = (char*)malloc(sizeof(char)*BUFFSIZE);

  if(fgets(buffer, BUFFSIZE, fp) == NULL){
    printf("ERROR: Invalid matrix file");
  }
  char * token = strtok(buffer, " ");
  *dims = atoi(token);

  int length = (*dims)*(*dims);
  double * matrix = (double*)malloc(sizeof(double)*length);
  
  int i =0;
  for(i = 0; i <length; i++){
    char * token = strtok(NULL, " ");
    matrix[i] = atof(token);

  }

  return(matrix);
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

double *readMatrix(char *fileName){
        FILE *file = fopen(fileName, "r");
        if(file == NULL){
                printf("Error Opening File %s", fileName);
                exit(0);
        }
        char line[1024];
        int nRows = 0;
		int mCols =0;
        if (fgets(line, sizeof(line), file)) {
			printf("%s", line); 
		}
		sscanf(line, "%d %d", &nRows, &mCols);
		
        double matrix[nRows*mCols];
  
        if(fgets(line,1024,file)){//skip the first line containing dimensions
		}
        //tokenize the line and store the array elements
		char buffer[1024];
		strcpy(buffer, line);
		int i =1;
		double val;
        char *token = strtok(buffer," ");
        matrix[0]= atof(token);
        while(token!=NULL){
				sscanf (token, "%lf", &val);
                matrix[i] = val;
                i++;
				
				token = strtok(NULL," ");
        }
		
		fclose(file);
        return matrix;
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

void tabulateMatrix(double *matrix, int rows, int cols){
	int j =0;int k = 0;
	double newMatrix[rows][cols];
	for(int i = 0; i < rows*cols; i++){
		if((i+1)%cols ==0){
			j++;
			k=0;
			printf("\n");
		}
		printf("%lf ",matrix[i]);
		newMatrix[j][k] = matrix[i];
		k++;
	}
}
