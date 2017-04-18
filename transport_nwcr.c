#include <stdio.h>

// Declaring golbal variables
int m,n,i,j;
int p=1,q=1;

// Functon to find minimum of two numbers
float min(float a,float b)
{
if (a<b)
   return a;
   else
   return b;
}

// Checking if the transportation problem is balanced
void if_Balance(float supply[],float demand[])
{
    int i,j;
    float Tot_Supply=0.0 , Tot_Demand=0.0;

     for(i=1;i<=m;i++)
        Tot_Supply=Tot_Supply + supply[i];

        printf("Total supply is %f unit\n",Tot_Supply);

      for(j=1;j<=n;j++)
        Tot_Demand=Tot_Demand + demand[j];

        printf("Total demand is %f unit \n\n",Tot_Demand);

        if(Tot_Supply == Tot_Demand)
            printf("Transportation problem is Balanced \n\n");
        else
            printf("Transportation problem is not Balanced \n\n");

}

void print_array(float unit[][10] )
{

for(j=1;j<=n;j++)
    printf("      D[%d]  ",j);
printf("\n");
    for(i=1;i<=m;i++)
    {
         printf("S[%d]  " ,i);
        for(j=1;j<=n+1;j++)
        {
            printf("%f  " ,unit[i][j]);
        }
        printf("\n");
    }
    printf("      ");
    for(j=1;j<=n+1;j++)
        {
            printf("%f  " ,unit[i][j]);
        }
        printf("\n");

}

// Printing the cost
void print_cost(float unit[][10] )
{

for(j=1;j<=n;j++)
    printf("      D[%d]  ",j);
printf("\n");
    for(i=1;i<=m;i++)
    {
         printf("S[%d]  " ,i);
        for(j=1;j<=n;j++)
        {
            printf("%f  " ,unit[i][j]);
        }
        printf("\n");
    }

}

// Function for the North-West Corner Rule
void north_west(float unit[][10],float supply[10],float demand[10])
{
int k;
  float minm = min(unit[p][n+1],unit[m+1][q]);
  printf("\n");
  printf("Minimum is %f \n\n", minm);
  unit[p][q]=minm;

  if(unit[p][n+1]== minm)
  {
      for(j=q+1;j<=n+1;j++)
      {
          unit[p][j]=0;

      }
      unit[m+1][q]=unit[m+1][q]-minm;
      p++;
  }
  else
  {
    for(i=p+1;i<=m+1;i++)
      {
          unit[i][q]=0;

      }
      unit[p][n+1]=unit[p][n+1]-minm;
      q++;
  }

print_array(unit);
float sum=0;
for(k=1;k<=m;k++)
{
    sum=sum+unit[k][n+1];
}
if(sum>0)
north_west(unit,supply,demand);

}

int main()
{

    float cost[10][10],unit[10][10];

    int i,j;

    printf("Enter the no of sources \n");
    scanf("%d",&m);

    printf("Enter the no of Destinations \n");
    scanf("%d",&n);

    float supply[m],demand[n],nwcr[10][10];

printf("Enter no of unit produced at each sources \n\n");
for(i=1;i<=m;i++)
scanf("%f",&supply[i]);

printf("Enter no of unit demanded at each destinations \n\n");
for(j=1;j<=n;j++)
scanf("%f",&demand[j]);

if_Balance(supply , demand);

for(i=1;i<=m;i++)
{
    for(j=1;j<=n;j++)
    {
        nwcr[i][j]= 1.0;

    }
}

for(j=1;j<=n;j++)
    nwcr[m+1][j]= demand[j];

for(i=1;i<=m;i++)
    nwcr[i][n+1]= supply[i];

    nwcr[m+1][n+1] = 0;
printf("\n");
    printf("cost of transportation each unit from i to j (ROW Wise) \n\n");

for(i=1;i<=m;i++)
{
    for(j=1;j<=n;j++)
    {
        scanf("%f",&cost[i][j]);

    }
}
printf("\n");

printf("the cost array is \n\n");
print_cost(cost);

printf("\n");
printf("the intermediate array is \n\n");

print_array(nwcr);

north_west(nwcr,supply,demand);

float Tcost =0;
int count=0;
for(i=1;i<=m;i++)
{
    for(j=1;j<=n;j++)
    {
        Tcost =Tcost + cost[i][j]*nwcr[i][j] ;
        if(nwcr[i][j] >0)
            count++;

    }
}
printf("\n");
printf("Total no of Basic solutions are %d  \n\n",count);
if(count==(m+n-1))
    printf("solution is Non degenerate \n\n");
else
     printf("solution is degenerate \n\n");

printf("Total Transportation cost is %f \n\n" ,Tcost);


}
