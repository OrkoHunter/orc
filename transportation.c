#include<stdio.h>
#include<stdlib.h>

int m,n;
double **A,**C,*a,*b;

void printmatrix()
{
  int i,j;
  printf("\nThe matrix for availability and demand is\n");
  for(i=0;i<m;i++)
    {
      for(j=0;j<n;j++)
	printf("\t ",A[i][j]);

      printf("\n");
    }
}

void input()
{
  int i,j;
  double dem=0,sup=0;
  printf("\nEnter number of available sources or rows\n");
  scanf("%d",&m);
  printf("\nEnter number of demand places or columns\n");
  scanf("%d",&n);

  A=(double **)malloc(m*sizeof(double *));
  for(i=0;i<m;i++)
    A[i]=(double *)malloc(n*sizeof(double));

  for(i=0;i<m;i++)
    for(j=0;j<n;j++)
      A[i][j]=0;

  C=(double **)malloc(m*sizeof(double *));
  for(i=0;i<m;i++)
    C[i]=(double *)malloc(n*sizeof(double));

  a=malloc(m*sizeof(double));
  b=malloc(n*sizeof(double));

  printf("\nAmount of supply for each source\n");
  for(i=0;i<m;i++)
    scanf("%lf",&a[i]);

  printf("\nAmount of Demand for each place\n");
  for(i=0;i<n;i++)
    scanf("%lf",&b[i]);

  for(i=0;i<m;i++)
    sup+=a[i];

  for(i=0;i<n;i++)
    dem+=b[i];

  printf("\nTOTAL DEMAND=%lf\n",dem);
  printf("\nTOTAL SUPPLY=%lf\n",sup);

  if(dem==sup)
    printf("\nIt is a balanced transportation problem\n");
  else
    {
      printf("\nIt is an unbalanced transportation problem\n");
      exit(1);
    }

  printf("\nEnter the cost value at each of the corresponding locations\n");

  for(i=0;i<m;i++)
    for(j=0;j<n;j++)
      scanf("%lf",&C[i][j]);

}

void NWCR()
{
  int i,j,k;
  for(i=0;i<m;i++)
    for(j=0;j<n;j++)
      {
	if(a[i]>=b[j])
	  {
	    A[i][j]=b[j];
	    a[i]-=b[j];
	    b[j]-=b[j];
	  }
	else if(a[i]<b[j])
	  {
	    A[i][j]=a[i];
	    b[j]-=a[i];
	    a[i]-=a[i];
	  }
      }
}


double cost()
{
  int i,j;
  double val=0;

  for(i=0;i<m;i++)
    for(j=0;j<n;j++)
      val+=C[i][j]*A[i][j];

  return val;

}


int main()
{
  double totalcost=0;
  input();
  NWCR();
  totalcost=cost();
  printf("\nPhase-I Solution (basic feasible solution) of the above transportation problem is= %lf\n\n",totalcost);
  return 0;
}

/*
  OUTPUT

  $ cc prog7.c
  $ ./a.out

  Enter number of sources or rows
  3

  Enter number of demand location or columns
  4

  Enter the supply amount for each source
  25
  30
  55

  Enter the demand amount for each demand location
  15
  30
  45
  20

  Total Demand=110.000000

  Total Supply=110.000000

  The given transportation problem is balanced

  Enter the cost for each demand supply at each source and location values
  5
  6
  5
  6
  6
  5
  5
  6
  6
  5
  5
  6

  The total transportation cost through Phase-I solution = 580.000000

*/
