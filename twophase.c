#include <stdio.h>
#include <stdlib.h>
#define max 400000000.000
double **main_array,***Tableau_list;
int **Index_list, **nonIndex_list;
int MaxorMin, count, unbdd, alter, infeas,g,l,e;
double minRatio[15], mostNeg[15];

void printSol(int nonIndex[],int n,int m, int g_e, double **main_array){
    int i,j;
    double soln[n];
    for(i=0 ; i<n ; i++)
        soln[i] = 0.0;
    for(i=0 ; i<m ; i++){
        for(j=0; j<m ; j++){
            if(main_array[i][nonIndex[j]]==1){
                soln[nonIndex[j]] = main_array[i][n];
            }
        }
    }
    for(i=(n-1) ; i>=(n-g_e) ; i--){
        if(soln[i]!=0) infeas = 1;
    }
    for(i=0 ; i<n ; i++){
        printf("x%d = %lf         ",(i+1),soln[i]);
    }
    printf("\n");
}

void printArray(int n,int m, double **main_array){
    int i,j;
    for(i=0 ; i<(m+1) ; i++){

        for(j=0 ; j<(n+1) ; j++){

            printf("%lf         ",main_array[i][j] );
        }
        printf("\n");


    }
}

int pivotcol(int Index[],int n,int m, double **main_array){
    int i,pivot=-1;
    double min=0.0;
    for(i=0 ; i<(n-m) ; i++){
        if(main_array[m][Index[i]] <= min && main_array[m][Index[i]]<0 ){
            pivot = Index[i];
            min = main_array[m][Index[i]];
            mostNeg[count] = min;
        }
    }
    return pivot;
}

int pivotrow(int Index[], int n, int m, int col, double **main_array){
    int i,pivot=-1;
    double ratios[m],min;
    for (i = 0; i < m; i++){
        if(main_array[i][col]==0)
            ratios[i]=max;
        else
            ratios[i] = main_array[i][n]/main_array[i][col];
        if(main_array[i][n]==0){
            if(main_array[i][col]>=0) ratios[i]=0;
            else ratios[i]=-1;
        }
    }
    min = max;
    for (i = 0; i < m; ++i){
        if(min >= ratios[i] && ratios[i]>=0.0){
                    pivot = i;
                    min = ratios[i];
                    minRatio[count] = min;
        }
    }
    if(pivot == -1) unbdd = 1;
    return pivot;
}

int SimplexMethod(int n,int m,double **main_array,int MaxorMin,int Index[],int nonIndex[],int phase){
    int i,j,k,xyz,p_r,p_c;
    alter = 0;
    double pivot;
    xyz = 1;
    p_c = pivotcol(Index,n,m,main_array);
    p_r = pivotrow(Index,n,m,p_c,main_array);
    for(i= 0; i<(m+2) ; i++){
        for(j = 0; j <(n+2) ; j++)
            Tableau_list[count][i][j] = main_array[i][j];
    }
    while(1){
        if(p_c==(-1) || p_r==(-1)|| alter >= 1)
            break;
        if(main_array[m][p_c]==0){
            alter = alter + 1;
        }
        int xy=0;
        if(phase ==1){
            if(main_array[m][n]==0 && infeas==0)
                xy = 1;
        }
        if(xy)
            break;
        count = count + 1;
        xyz++;
        pivot = main_array[p_r][p_c];
        for(i=0 ; i<(n+1) ; i++){
            main_array[p_r][i] = main_array[p_r][i]/pivot;
        }
        for(i=0 ; i<(m+1) ; i++){
            double temp = main_array[i][p_c];
            for (j = 0; j<(n+1) ; ++j){
                if (i!=p_r){
                    main_array[i][j] = main_array[i][j] - temp*main_array[p_r][j];
                }
            }
        }
        for(i=0 ; i<m ; i++){
            if(main_array[p_r][nonIndex[i]]!=0){
                for(j=0 ; j<(n-m) ; j++){
                    if(p_c==Index[j]){
                        Index[j] = nonIndex[i];
                        nonIndex[i] = p_c;
                    }
                }
            }
        }
        for(i=0 ; i<(n-m) ; i++){
            Index_list[count][i] = Index[i];
        }
        for (j = 0; j<(m); ++j){
            nonIndex_list[count][j] = nonIndex[j];
        }
        infeas =0;
        p_c = pivotcol(Index,n,m,main_array);
        p_r = pivotrow(Index,n,m,p_c,main_array);
        for(i= 0; i<(m+2) ; i++){
            for(j = 0; j <(n+2) ; j++)
                Tableau_list[count][i][j] = main_array[i][j];
        }
    }
    return count;

}
int TwoPhaseSimplex_Method(double** main_array,double obj_func[],int n_obj,int n_const,int n,int m,int l,int g,int e){
    int i,j,Index[n-m],nonIndex[m];
    count = 0;
    for(i=0 ; i<g ; i++){
        for (j=0; j<m; j++){
            if (i==j){
                main_array[j][n_const+i] = -1;
                main_array[j][n_const+l+g+i] = 1;
            }
            else{
                main_array[j][n_const+i] = 0;
                main_array[j][n_const+l+g+i] = 0;
            }
        }
        main_array[m][n_const+i] = 1;
        main_array[m][n_const+l+g+i] = 0;
    }
    for(i=g ; i<(e+g); i++){
        for (j=0; j<m; j++){
            if (i==j){
                main_array[j][n_const+l+g+i] = 1;
            }
            else{
                main_array[j][n_const+l+g+i] = 0;
            }
        }
        main_array[m][n_const+l+g+i] = 0;
    }
    for(i=(g+e) ; i<m; i++){
        for (j=0; j<m; j++){
            if (i==j){
                main_array[j][n_const+i-e] = 1;
            }
            else{
                main_array[j][n_const+i-e] = 0;
            }
        }
        main_array[m][n_const+i-e] = 0;
    }
    for(i=0 ; i<n_obj ; i++){
        double temp = 0.0;
        for (j=0; j<(g+e); j++)
            temp= temp + main_array[j][i];
        main_array[m][i]= main_array[m][i]- temp;
    }
    for(i=0 ; i<(n-m) ; i++){
        Index[i] = i;
        Index_list[count][i] = Index[i];
    }
    for (j = 0; j<(m); ++j)
    {
        nonIndex[j]=i;
        nonIndex_list[count][j] = nonIndex[j];
        i++;
    }
    printf("\n-------------Phase 1 - Initial Table-----------\n");
    printArray(n,m,main_array);
    printf("\n");
    int ph1 = SimplexMethod(n,m,main_array,MaxorMin,Index,nonIndex,1);
    for(i=0 ; i<ph1 ; i++){
        printf("\nIteration : %d\n",i);
        printSol(nonIndex_list[i],n,m,(g+e),Tableau_list[i]);
        printf("The Objective value is : %lf\n",MaxorMin*Tableau_list[i][m][n]);
    }
    printf("\nThe final solution of Phase-1 is : \n");
    printSol(nonIndex_list[count],n,m,(g+e),main_array);
    printf("The Optimum value of Phase -1 is : %lf\n",MaxorMin*main_array[m][n] );
    double new_obj[n+1];
    for(i=0 ; i<(m+1) ; i++){
        for(j=n-1 ; j>=(n-g-e) ; j--)
            main_array[i][j] = 0.0;
    }
    for(i=0 ; i<n+1 ; i++){
        new_obj[i] = -1*MaxorMin*obj_func[i];
    }
    for(i=0; i<m ; i++){
        if(nonIndex_list[ph1][i]<n_obj){
            new_obj[nonIndex_list[ph1][i]]=0.0;
        }
    }
    for(i=0 ; i<m ; i++){
        if(nonIndex_list[ph1][i]<n_obj){
            int row = -1;
            for(j=0 ; j<m ;j++){
                if(main_array[j][nonIndex_list[ph1][i]] ==1)
                    row = j;
            }
            for(j=0 ; j<(n-m) ; j++){
                new_obj[Index_list[ph1][j]] += MaxorMin*obj_func[nonIndex_list[ph1][i]]*main_array[row][Index_list[ph1][j]];
            }
            new_obj[n] += MaxorMin*obj_func[nonIndex_list[ph1][i]]*main_array[row][n];
        }
    }
    for(i=0 ; i<(n+1) ; i++)
        main_array[m][i] = new_obj[i];
    count++;
    for(i=0; i<m+1 ; i++){
        for(j=0; j<n+1 ; j++)
            Tableau_list[count][i][j] = main_array[i][j];
    }
    printf("\n---------------------Initial Table for 2 Phase ------------------\n");
    printArray(n,m,main_array);
    printf("\n***Initial Basic feasible Solution***\n");
    printSol(nonIndex_list[ph1],n,m,(g+e),main_array);
    int ph2 = SimplexMethod(n,m,main_array,MaxorMin,Index_list[ph1],nonIndex_list[ph1],2);
    for(i = ph1+1 ; i<ph2 ; i++){
        printf("\nIteration : %d\n",i-ph1);
        printf("Most Negative : %lf\n", mostNeg[i]);
        printf("Min ratio : %lf\n",minRatio[i]);
        printSol(nonIndex_list[i],n,m,(g+e),Tableau_list[i]);
        printf("The Objective value is : %lf\n",MaxorMin*Tableau_list[i][m][n]);
    }
    printf("\n----------------------The final solution of Phase-2 is-------------- : \n");
    printSol(nonIndex_list[count],n,m,(g+e),main_array);
    printf("The Optimum value of Phase-2 is : %lf\n",MaxorMin*main_array[m][n] );
    return 0;
}

void main(){
    int i,j,k,m,n,n_obj,n_const;
    double temp,unbdd = 0;
    printf("Enter the Number of Varibales :");
    scanf("%d",&n_const);
    printf("Enter the Number of constraints :");
    scanf("%d",&m);
    printf("Enter the Number of >= , = , <= constraints in the order : ");
    scanf("%d %d %d",&g,&e,&l);
    n = n_const + l + e + 2*g;
    Tableau_list = (double ***)malloc((15)*sizeof(double));
    for (i = 0; i < 15; ++i){
        Tableau_list[i] = (double **)malloc((m+2)*sizeof(double));
        for(j = 0; j < (m+2); j++)
            Tableau_list[i][j] = (double *)malloc((n+2)*sizeof(double));
    }
    Index_list = (int **)malloc((15)*sizeof(int));
    int ind = n-m;
    for (i = 0; i < 15; i++){
        Index_list[i] = (int *)malloc((ind)*sizeof(int));
    }
    int nonind = m;
    nonIndex_list = (int **)malloc((15)*sizeof(int));
    for (i = 0; i<14; i++){
        nonIndex_list[i] = (int *)malloc((nonind)*sizeof(int));
    }
    main_array = (double **)malloc((m+2)*sizeof(double));
    for(i=0; i<m+2 ;i++)
        main_array[i] = (double *)malloc((n+2)*sizeof(double));
    for(i=0; i<m+2 ;i++){
        for(j=0; j<n+2 ; j++)
            main_array[i][j] = 0.0;
    }
    printf("Enter the coefficients of the constraints In order of >= , = , <= :\n");
    for(i=0 ; i<m ; i++){
        for(j=0 ; j<n_const ; j++)
            scanf("%lf",&main_array[i][j]);
    }
    printf("1 to Maximize and -1 to Minmize :");
    scanf("%d",&MaxorMin);
    printf("Enter the constants of the constraints (In order as of Constraints): \n");
    temp = 0.0;
    for(i=0 ; i<m ;i++){
        scanf("%lf",&main_array[i][n]);
        if(i<(g+e))temp = temp + main_array[i][n];
    }
    main_array[m][n] = -1*temp;
    printf("Number of Variables in Objective function :");
    scanf("%d",&n_obj);
    double obj_func[n+1];
    for(i=0 ; i < n+1 ; i++)
        obj_func[i] = 0.0;
    printf("Enter the constants of objective function :\n");
    for(i=0 ; i<n_obj ; i++){
        scanf("%lf",&temp);
        obj_func[i]= temp;
    }
    for(i=n_obj ; i<n ;i++)
        main_array[m][i] = 0;
    int no_of_iterations;
    no_of_iterations = TwoPhaseSimplex_Method(main_array,obj_func,n_obj,n_const,n,m,l,g,e);
}
