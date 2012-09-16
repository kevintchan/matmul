#include <stdio.h>

void matmuld(double **a, double **b, double **c, int block_size) {

  // Assumes that the cache can hold K*n + n + K words
  //int block_size = 64; //(K)
  int matrix_dimension = 1024; //(n)
  int blocks = matrix_dimension / block_size;
  block_size = 32;
  
  for(int ii=0; ii<matrix_dimension; ii+=block_size) {
    for(int jj=0; jj<matrix_dimension; jj+=block_size) {
      for(int kk=0; kk<matrix_dimension ;kk+=block_size) {
        for (int i=ii; i<ii+block_size; i++) {
	  for (int k=kk; k<kk+block_size; k++) {
	    //for (int j=jj; j<jj+block_size; j++) {

              //c[i][j] += a[i][k]*b[k][j];
	      //}

            register double x = a[i][k];
            register double *r = &c[i][jj];
            register double *y = &b[k][jj];
	    // 0
            *r += x * (*y);
            y += 1; r += 1;
	    *r += x * (*y);
	    y += 1; r += 1;
	    *r += x * (*y);
            y += 1; r += 1;
	    *r += x * (*y);
            y += 1; r += 1;
            *r += x * (*y);
            y += 1; r += 1;
            *r += x * (*y);
            y += 1; r += 1;
            *r += x * (*y);
            y += 1; r += 1;
            *r += x * (*y);
	    // 8
	    y += 1; r += 1;
            *r += x * (*y);
            y += 1; r += 1;
            *r += x * (*y);
            y += 1; r += 1;
            *r += x * (*y);
            y += 1; r += 1;
            *r += x * (*y);
            y += 1; r += 1;
            *r += x * (*y);
            y += 1; r += 1;
            *r += x * (*y);
            y += 1; r += 1;
            *r += x * (*y);
            y += 1; r += 1;
            *r += x * (*y);
	    // 16
	    y += 1; r += 1;
            *r += x * (*y);
            y += 1; r += 1;
            *r += x * (*y);
            y += 1; r += 1;
            *r += x * (*y);
            y += 1; r += 1;
            *r += x * (*y);
            y += 1; r += 1;
            *r += x * (*y);
            y += 1; r += 1;
            *r += x * (*y);
            y += 1; r += 1;
            *r += x * (*y);
            y += 1; r += 1;
            *r += x * (*y);
	    // 24
	    y += 1; r += 1;
            *r += x * (*y);
            y += 1; r += 1;
            *r += x * (*y);
            y += 1; r += 1;
            *r += x * (*y);
            y += 1; r += 1;
            *r += x * (*y);
            y += 1; r += 1;
            *r += x * (*y);
            y += 1; r += 1;
            *r += x * (*y);
            y += 1; r += 1;
            *r += x * (*y);
            y += 1; r += 1;
            *r += x * (*y);
	    // 32
          }
        }
      }
    }
  }
}
