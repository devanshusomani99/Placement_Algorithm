#include <bits/stdc++.h>

using namespace std;

int main(int argc, char const *argv[]) {

  freopen("input.txt", "r", stdin);


  int M,N;                                  // M = Number of students, N = Number of jobs
  scanf(" %d %d", &M, &N);


  int J[N][M];                              // Each job's student priority list in a form of 2D array
  int s[M][N];                              // Each student's job priority list in a form of 2D array
  int a[N];                                 // The array which will store the final student job allocation
  int p[N];                                 // The array which will store the priority number of the selected
                                            // student for each job

  int i,j,k,l;

  for(i=0;i<N;i++)
  {
    for(j=0;j<M;j++)
    {
      scanf(" %d",&J[i][j]);
    }
  }

  for(i=0;i<M;i++)
  {
    for(j=0;j<N;j++)
    {
      scanf(" %d",&s[i][j]);
    }
  }

  for(i=0;i<N;i++)
  {
    a[i] = J[i][0];                         // This loop will set the base case
    p[i] = 0;                               // Each job gets associated with its top priority student
  }

  for(i=0;i<N;i++)
  {
    for(j=i+1;j<N;j++)
    {
      if(a[i]==a[j])                        // If 2 jobs are associated with the same student
      {
        k = a[i];
        for(l=0;l<N;l++)                    // Then look into that student's priority list
        {
          if(s[k-1][l]==i+1)                // And associate that job with him/her which comes before in the
                                            // student's priority list
          {
            p[j]++;
            a[j] = J[j][p[j]];              // And associate the other job with its next priority student
            i=0;                            // Start this process all over agian because the new student could
                                            // also be associated with some other previously checked job
            break;
          }
          if(s[k-1][l]==j+1)
          {
            p[i]++;
            a[i] = J[i][p[i]];
            i=0;
            break;
          }
        }
      }
    }
  }

  for(i=0;i<N;i++)
  {
    printf("Job%d - Student%d\n",i+1,a[i]);
  }

  return 0;
}
