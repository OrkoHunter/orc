#include <stdio.h>
#include <math.h>
#include <stdbool.h>

int numOfCombinations = 0;
bool basicsol[100], feasiblesol[100], nondegsol[100], extremePoints[100];

void printOptimal(double (*allBsol)[100], double objFunction[], int n, int m){
    int i, j, temp = 0;
    double numbers[1001], sum = 0, largestValue;
    for(i = 0; i <= 1000; i++) numbers[i] = -1;
    for(i = 0; i < numOfCombinations; i++){
            if(!feasiblesol[i]) continue;
        sum = 0;
        for(j = 1; j <= n; j++)
            sum += objFunction[j]*allBsol[i][j];
        numbers[i] = sum;
    }
    largestValue = numbers[0];
    for(i = 0; i < 100; i++) extremePoints[i] = false;
    extremePoints[0] = true;

    for (i = 1; i < numOfCombinations; i++) {
        if (numbers[i] > largestValue) {
            largestValue = numbers[i]; // Update largestValue
        for(j = 0; j < 100; j++) extremePoints[j] = false;    // Get rid of indices of smaller values
        extremePoints[i] = true;     // Add this index
    }
    else if (numbers[i] == largestValue) {
        extremePoints[i] = true;      // Add this index
    }
}

printf("The optimal solution of the problem is/are:\n\n");
    for(i = 0; i < numOfCombinations; i++){
        if (extremePoints[i]) {
            temp = 1;
        for(j = 1; j <= n; j++)
            printf("x_%d = %lf, ", j, allBsol[i][j]);
    printf("\n");
    }
}
if (!temp) printf("No such solutions.\n");
}

void printFeasible(double (*allBsol)[100], int n){
    int i, j, temp = 0;
    printf("The basic feasible solutions of the problem are:\n\n");
    for(i = 0; i < numOfCombinations; i++){
        if (feasiblesol[i]) {
            temp = 1;
        for(j = 1; j <= n; j++)
            printf("x_%d = %lf, ", j, allBsol[i][j]);
    printf("\n");
    }
}
if (!temp) printf("No such solutions.\n");
}

void printExtreme(double (*allBsol)[100], int n){
    int i, j, temp = 0;
    printf("The extreme points of the problem are:\n\n");
    for(i = 0; i < numOfCombinations; i++){
        if (feasiblesol[i]) {
            temp = 1;
        for(j = 1; j <= n; j++)
            printf("x_%d = %lf, ", j, allBsol[i][j]);
    printf("\n");
    }
}
if (!temp) printf("No such points\n");
}

void printBasic(double (*allBsol)[100], int n){
    int i, j, temp = 0;
    printf("The basic solutions of the problem are:\n\n");
    for(i = 0; i < numOfCombinations; i++){
        if (basicsol[i]) {
            temp = 1;
        for(j = 1; j <= n; j++)
            printf("x_%d = %lf, ", j, allBsol[i][j]);
    printf("\n");
    }
}
if (!temp) printf("No such solutions\n");
}

void printDeg(double (*allBsol)[100], int n){
    int i, j, temp = 0;
    printf("The degenerate solutions of the problem are:\n\n");
    for(i = 0; i < numOfCombinations; i++){
        if (feasiblesol[i] && !nondegsol[i]) {
            temp = 1;
        for(j = 1; j <= n; j++)
            printf("x_%d = %lf, ", j, allBsol[i][j]);
    printf("\n");
    }
}
if (!temp) printf("No such solutions\n");
}

void printNonDeg(double (*allBsol)[100], int n){
    int i, j, temp = 0;
    printf("The non-degenerate solutions of the problem are:\n\n");
    for(i = 0; i < numOfCombinations; i++){
        if (nondegsol[i]) {
            temp = 1;
        for(j = 1; j <= n; j++)
            printf("x_%d = %lf, ", j, allBsol[i][j]);
    printf("\n");
    }
}
if (!temp) printf("No such solutions\n");
}

void readAugMatrix(double (*A)[101], int m, int n){

    printf("\nEnter the elements of augmented matrix row-wise:\n\n");

    int i, j;
    for(i = 1; i <= m; i++)
        for(j=1; j<=n+1; j++)
        {
            printf("A[%d][%d] : ", i,j);
            scanf("%lf",&A[i][j]);
        }
}

void combinationUtil();

void makeCombination(int arr[], int (*combinations)[100], int n, int r)
{
    int data[r];
    combinationUtil(arr, combinations, data, 0, n-1, 0, r);
}

void combinationUtil(int arr[], int (*combinations)[100], int data[], int start, int end,
                     int index, int r)
{

    if (index == r)
    {
        int j;
        for (j = 0; j<r; j++)
            combinations[numOfCombinations][j] = data[j];
        numOfCombinations++;
        return;
    }
    int i;
    for (i=start; i<=end && end-i+1 >= r-index; i++)
    {
        data[index] = arr[i];
        combinationUtil(arr, combinations, data, i+1, end, index+1, r);
    }
}

void gaussElimination(double (*A)[101], double x[], int n)
{

    int i, j, k;
    double sum = 0.0, c;

    for(j=1; j<=n; j++)
    {
        for(i=1; i<=n; i++)
        {
            if(i>j)
            {
                c = A[i][j]/A[j][j];
                for(k=1; k<=n+1; k++)
                {
                    A[i][k]=A[i][k]-c*A[j][k];
                }
            }
        }
    }
    x[n]=A[n][n+1]/A[n][n];

    for(i=n-1; i>=1; i--)
    {
        sum=0;
        for(j=i+1; j<=n; j++)
        {
            sum = sum + A[i][j]*x[j];
        }
        x[i]=(A[i][n+1]-sum)/A[i][i];
    }
}


int main()
{
    int m, n, combinations[10001][100], columnIndices[100];
    double augMatrix[100][101], bSolutions[100], sqMatrix[100][101], allBsol[1001][100];

    printf("\nEnter the number of equations (m) and variables (n) respectively: \n");
    scanf("%d%d", &m, &n);

    int i = 0;
    for(i = 0; i < 100; i++){
        basicsol[i] = true;
        feasiblesol[i] = true;
        nondegsol[i] = true;
    }
    for (i = 0; i < n; i++)
        columnIndices[i] = i + 1;

    readAugMatrix(augMatrix, m, n);

    makeCombination(columnIndices, combinations, n, m);

    int j, k, l, r, feasible;
    for(i = 0; i < numOfCombinations; i++){
        for(j = 0; j < m; j++){
            for(k = 1; k <= m; k++){
                sqMatrix[k][j+1] = augMatrix[k][combinations[i][j]];
            }
        }
        for (r = 1; r <=m; r++)
        sqMatrix[r][m+1] = augMatrix[r][n+1];

        gaussElimination(sqMatrix, bSolutions, m);
        int temp = 0;

        for(feasible = 1; feasible <= m; feasible++){
            if (!isfinite(bSolutions[feasible])){
                basicsol[i] = false;
                feasiblesol[i] = false;
                nondegsol[i] = false;
            }
            if(bSolutions[feasible] < 0){
                feasiblesol[i] = false;
                nondegsol[i] = false;
            }
            if(bSolutions[feasible] == 0)
                nondegsol[i] = false;
        }
        for(l = 1; l <= n; l++){
            if (l == combinations[i][temp]){
                allBsol[i][l] = bSolutions[temp+1];
                temp++;
            }
            else allBsol[i][l] = 0;
        }
    }

    while(1){
        int c, quit = 0;
        printf("Choose an option from the list below\n\n");
        printf("1. Print basic solutions.\n");
        printf("2. Print basic feasible solutions.\n");
        printf("3. Print degenerate solutions\n");
        printf("4. Print non-degenerate solutions\n");
        printf("5. Print extreme points and optimal solution.\n");
        printf("6. Exit.\n");
        scanf("%d", &c);
        switch(c){
            case 1:
            printBasic(allBsol, n);
            break;
            case 2:
            printFeasible(allBsol, n);
            break;
            case 3:
            printDeg(allBsol, n);
            break;
            case 4:
            printNonDeg(allBsol, n);
            break;
            case 5:
                {
                // Objective function
                double objFunction[100];
                printf("Give the Objective function.\n");
                for(i = 1; i <= n; i++){
                    printf("Coefficient of x_%d:   ", i);
                    scanf("%lf", &objFunction[i]);
                }
                printExtreme(allBsol, n);
                printOptimal(allBsol, objFunction, n, m);
                break;
                }
            case 6:
            quit = 1;
            break;
}
    if (quit) break;
    }
    return(0);
}
