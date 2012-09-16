#include <stdio.h>

void matmuld(double **a, double **b, double **c, int block_size) {

  // Assumes that the cache can hold K*n + n + K words
  //int block_size = 64; //(K)
  int matrix_dimension = 1024; //(n)
  int blocks = matrix_dimension / block_size;
  
  for(int ii=0; ii<matrix_dimension; ii+=block_size) {
    for(int jj=0; jj<matrix_dimension; jj+=block_size) {
      for(int kk=0; kk<matrix_dimension ;kk+=block_size) {
	for (int i=ii; i<ii+block_size && i<matrix_dimension; i++) {
	  for (int j=jj; j<jj+block_size && j<matrix_dimension; j++) {
	    for (int k=kk; k<kk+block_size && k<matrix_dimension; k+=4) {
	      c[i][j] += a[i][k]*b[k][j];
	    }
	  }
	}
      }
    }
  }
}
