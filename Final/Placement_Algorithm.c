#include <stdio.h>
#include <stdlib.h>
#include "hungarian.h"

int** array_to_matrix(int* m, int rows, int cols) {
  int i,j;
  int** r;
  r = (int**)calloc(rows,sizeof(int*));
  for(i=0;i<rows;i++)
  {
    r[i] = (int*)calloc(cols,sizeof(int));
    for(j=0;j<cols;j++)
      r[i][j] = m[i*cols+j];
  }
  return r;
}


int main() {

  hungarian_problem_t p;

  freopen("input2.txt", "r", stdin);

  int w1,w2;
  int M, N;                                  // M = Number of students, N = Number of jobs
  scanf(" %d %d", &M, &N);
  scanf(" %d %d", &w1, &w2);


  int J[N][M];                              // Each job's student priority list in a form of 2D array
  int s[M][N];                              // Each student's job priority list in a form of 2D array

  int r1[M][N], r[M*N];
  char char1='0', char2='0';

  for(int i=0;i<N;i++)
  {
    for(int j=0;j<M;j++)
    {
      r1[i][j]=1000000000;
    }
  }

  for(int i=0;i<N;i++)
  {
    for(int j=0;j<M;j++)
    {
      scanf(" %d%c",&J[i][j],&char1);
      r1[J[i][j]-1][i] = (w1)*(j+1);
      if(char1=='\n')
      {
        char1='0';
        break;
      }
    }
  }

  for(int i=0;i<M;i++)
  {
    for(int j=0;j<N;j++)
    {
      scanf(" %d%c",&s[i][j],&char2);
      r1[i][s[i][j]-1] = r1[i][s[i][j]-1] + (w2)*(j+1);
      if(char2=='\n')
      {
        char2='0';
        break;
      }
    }
  }

  for(int i=0;i<M;i++)
  {
    for(int j=0;j<N;j++)
    {
      r[i*N+j]=r1[i][j];
    }
  }




  /* an example cost matrix
  int r[4*3] =  {  4, 31, 13,
		   19, 2, 27,
		   1, 10, 40,
		   20, 20, 0 }; */

  int** m = array_to_matrix(r,M,N);

  /* initialize the gungarian_problem using the cost matrix*/
  int matrix_size = hungarian_init(&p, m , M, N, HUNGARIAN_MODE_MINIMIZE_COST) ;
  /*
  fprintf(stderr, "assignement matrix has a now a size %d rows and %d columns.\n",  matrix_size,matrix_size);

   some output
  fprintf(stderr, "cost-matrix:");
  hungarian_print_costmatrix(&p);
  */

  /* solve the assignement problem */
  hungarian_solve(&p);

  /* some output
  fprintf(stderr, "assignment:");
  hungarian_print_assignment(&p);
  */
  print_allocation(&p,N);

  /* free used memory */
  hungarian_free(&p);

  int idx;
  for (idx=0; idx < M; idx+=1) {
    free(m[idx]);
  }
  free(m);

  return 0;
}
