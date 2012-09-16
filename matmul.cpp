#include <stdio.h>

void matmuld(double **a, double **b, double **c, int block_size) {

  // Assumes that the cache can hold K*n + n + K words
  //int block_size = 64; //(K)
  int matrix_dimension = 1024; //(n)
  int blocks = matrix_dimension / block_size;
  block_size = 8;
  
  for(int ii=0; ii<matrix_dimension; ii+=block_size) {
    for(int jj=0; jj<matrix_dimension; jj+=block_size) {
      for(int kk=0; kk<matrix_dimension ;kk+=block_size) {
        for (int i=ii; i<ii+block_size; i++) {
          for (int k=kk; k<kk+block_size; k++) {
            /*
            for (int j=jj; j<jj+block_size; j++) {
              c[i][j] += a[i][k]*b[k][j];
            }
            */
            int x = a[i][k];
            int *r = &c[i][jj];
            int *y = &b[k][jj];
            *r += x * (*y);
            y++;
            *r += x * (*y);
            yy++;
            *r += x * (*y);
            yy++;
            *r += x * (*y);
            yy++;
            *r += x * (*y);
            yy++;
            *r += x * (*y);
            yy++;
            *r += x * (*y);
            yy++;
            *r += x * (*y);
          }
        }
      }
    }
  }
}
