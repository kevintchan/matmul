#include <pthread.h>
#include <cassert>
#include <stdio.h>

typedef struct
{
  double **a;
  double **b;
  double **c;
  int start;
  int end;
} worker_t;

void *matmuld_worker(void *arg)
{
  worker_t *t = static_cast<worker_t*>(arg);
  double **a = t->a;
  double **b = t->b;
  double **c = t->c;

  // Assumes that the cache can hold K*n + n + K words
  int block_size = 64; //(K)
  int matrix_dimension = 1024; //(n)
  int blocks = matrix_dimension / block_size;

  for(int i = t->start; i < t->end; i++) {
    for(int jj=0; jj<matrix_dimension; jj+=block_size) {
      for(int kk=0; kk<matrix_dimension ;kk+=block_size) {
	for (int j=jj; j<jj+block_size; j++) {
	  for (int k=kk; k<kk+block_size; k++) {
	    c[i][j] += a[i][k]*b[k][j];
	  }
	}
      }
    }
  }
}

void pthread_matmuld(double **a,
		     double **b,
		     double **c,
		     int nthr) {
  /* CS194: use pthreads to launch 
   * matrix multply worker threads.
   *
   * The structure and worker function
   * are good hints...
   */
  pthread_t *thr = new pthread_t[nthr];
  worker_t *tInfo = new worker_t[nthr];
  int i;
  int max = 1024;
  int interval = max / nthr;
  for (i = 0; i < nthr; i++)
  {
    tInfo[i].a = a;
    tInfo[i].b = b;
    tInfo[i].c = c;

    // set start/end boundaries
    // start begins at 0
    // end ends at MAX (not MAX - 1)
    int start = interval *i;
    tInfo[i].start = start;

    int end = interval * (i + 1);
    if (end + interval > max) {
      end = max;
    }
    tInfo[i].end = end;
    //printf("start: %d:: end %d\n", start, end);

    //matmuld_worker((void*)tInfo);

    pthread_create(&thr[i], 0, matmuld_worker, (void*) &tInfo[i]);

    
  }

  for (i = 0; i < nthr; i++) {
    pthread_join(thr[i], NULL);
  }
      
  
  delete [] thr;
  delete [] tInfo;
}
