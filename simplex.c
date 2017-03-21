#include<stdio.h>
#include<math.h>
#include<stdbool.h>
float updated_mat[100][100];
int interchangeX[100],interchangeZ[100];
float simplex();
int min(float a[], int n){
	int i,pivot_column;
	float min = 100000;
	for(i=0;i<n;i++){
		if(a[i]<min){
			min = a[i];
			pivot_column = i;
		}
	}
	return pivot_column;
}
float simplex(int m, int n, float mat[][n+1]){
	int i,j,pivot_row,pivot_column;
	int flag = 0;
	int key = 0;
	float mr[m]; //minimum ratio
	float max_val;
	float max[n];
	for(i=0;i<n;i++){
		max[i] = mat[m][i];
	}
	for(i=0;i<n;i++){
		if(mat[m][i]<0){
			flag = 1;//to check stopping criteria
		}
	}
	if(flag==0){
		max_val = mat[m][n];
		return max_val;
	}
	pivot_column = min(max,n);
	for(i=0;i<m;i++){
		if(mat[i][pivot_column]>0){
			mr[i] = mat[i][n]/mat[i][pivot_column];
			key = 1; //to check bounded or not 
		}
		else mr[i] = 1000000;
	}
	if(key == 0){
		printf("Problem Unbounded\n");
		return 0;
	}
	pivot_row = min(mr,m);
	//transformation of updated simplex table
	updated_mat[pivot_row][pivot_column] = 1/(mat[pivot_row][pivot_column]); //updating pivot
	for(i=0;i<n+1;i++){
		if(i != pivot_column){
			updated_mat[pivot_row][i] = mat[pivot_row][i]*updated_mat[pivot_row][pivot_column]; //updating pivot row
		}
	}
	for(i=0;i<m+1;i++){
		if(i != pivot_row){
			updated_mat[i][pivot_column] = -mat[i][pivot_column]*updated_mat[pivot_row][pivot_column]; //updating pivot column
		}
	}
	for(i=0;i<m+1;i++){
        for(j=0;j<n+1;j++){
	     	if(i !=pivot_row && j!= pivot_column)
	   			updated_mat[i][j]=((mat[i][j]*mat[pivot_row][pivot_column])-(mat[i][pivot_column]*mat[pivot_row][j]))/mat[pivot_row][pivot_column]; //transforming other elements
	    }	
	}
	interchangeX[pivot_row] = pivot_column;
	interchangeZ[pivot_column] = pivot_row;
	float rec_mat[m+1][n+1]; //new matrix to store the table for next step
	for(i=0;i<m+1;i++){
		for(j=0;j<n+1;j++){
			rec_mat[i][j] = updated_mat[i][j];
		}
	}
	max_val = simplex(m,n,rec_mat);
	return max_val;
}
int main(){
	int m,n,i,j;
	printf("Enter no. of inequalities\n");
	scanf("%d", &m);
	printf("Enter no of variables \n");
	scanf("%d", &n);
	float mat[m+1][n+1];
	float max[n+1];
	float max_val;
	printf("Enter the coefficient of inequalities and b\n");
  for(i=0;i<m;i++){
    	for(j=0;j<n+1;j++){
    		if(j<n){
    			printf("Enter a[%d][%d]\n",i,j );
				scanf("%f",&mat[i][j]);
			}
			else{
				printf("Enter value b[%d]\n",i);
				scanf("%f",&mat[i][n]);
	   		}
		}
      	interchangeX[i]= -1;
      	interchangeZ[i]= -1;
    }
  printf("Enter the objective coefficients\n");
  for(i=0;i<n+1;i++){
    	if(i!=n){
			scanf("%f",&max[i]);
			max[i]=-max[i];
       	}
		else{
			mat[m][n] = 0;
		}
        mat[m][i]=max[i];  
    }
 
  max_val=simplex(m,n,mat);
  printf("Maximum Value Z is %f\n",max_val);
  printf("Values are \n");
  for(i=0;i<m;i++){
    	if(interchangeX[i] != -1){
		   	printf("x%d = %f, ",interchangeX[i]+1,updated_mat[i][n]);
		}
    }
  for(i=0;i<n;i++){
    	if(interchangeZ[i]== -1){
	    	printf("x%d = 0, ",i+1);
		}
	}
}