#include <stdio.h>
#include <math.h>
void simplex(int m, int n) {
        int i, j, maxcheck;
        maxcheck = 1;
        int itr;
        itr = 0;
        float c[100], d; //for objective function
        printf("Enter the type of objective function (0 for min, 1 for max): ");
        scanf("%d", & maxcheck);
        printf("Enter the objective function.\n");
        for (i = 1; i <= n; i++) {
            //printf("c[%d] = ", i);
            scanf("%f", & c[i]);
            if (maxcheck == 0)
                c[i] = -1 * c[i];
        }
        printf("d = ");
        scanf("%f", & d);
        printf("Enter the constraint eqns.");
        printf("(All variables should be ≥0).\n");
        printf("All constraints must be of type ≤.\n");
        printf("If all constraints are ≤ type and all b[i]≥0, then input their dual form.\n");
        float a[100][100], b[100];
        for (i = 1; i <= m; i++) {
            for (j = 1; j <= n; j++) {
                //printf("a[%d][%d] = ", i, j);
                scanf("%f", & a[i][j]);
            }
            //printf("b[%d] = ", i);
            scanf("%f", & b[i]);
        }
        // printf("\nSolution---\n");
        float simp[100][100]; //simplex tableau
        float itrtable[100][100][100];
        for (i = 1; i <= m + 1; i++) {
            for (j = 1; j <= n + 1; j++) {
                if (i <= m && j <= n)
                    simp[i][j] = a[i][j];
                else if (i == m + 1 && j <= n)
                    simp[i][j] = -1 * c[j];
                else if (i <= m && j == n + 1)
                    simp[i][j] = b[i];
                else if (i == m + 1 && j == n + 1)
                    simp[i][j] = d;
            }
        }
        int x[100], z[100];
        for (i = 1; i <= n; i++) {
            x[i] = -1 * i;
        }
        for (i = 1; i <= m; i++) {
            z[i] = i;

        }
        int check = 1;
        while (check == 1) {
            for (i = 1; i <= m + 1; i++)
                for (j = 1; j <= n + 1; j++)
                    itrtable[itr][i][j] = simp[i][j];
            float min1 = 0.0, pivot;
            int u, v;
            for (i = 1; i <= m; i++) {
                if (min1 > simp[i][n + 1]) {
                    min1 = simp[i][n + 1];
                    v = i;
                }
            }
            if (min1 == 0) {
                break;
            }
            float min2 = 9999.0; {
                for (i = 1; i <= n; i++)
                    if (simp[v][i] < 0) {
                        if (min2 > fabs(simp[m + 1][i] / simp[v][i])) {
                            min2 = fabs(simp[m + 1][i] / simp[v][i]);
                            u = i;
                        }
                    }
            }
            int unbound;
            unbound = 0;
            if (min2 == 9999.0) {
                unbound = 1;
                break;
            }
            pivot = simp[v][u];
            int temp;
            temp = z[v];
            z[v] = x[u];
            x[u] = temp;
            for (i = 1; i <= m + 1; i++) {
                for (j = 1; j <= n + 1; j++) {
                    if (i != v && j != u) {
                        simp[i][j] = (simp[v][u] * simp[i][j] - simp[v][j] * simp[i][u]) / simp[v][u];
                    }
                }
            }
            for (i = 1; i <= m + 1; i++) {
                for (j = 1; j <= n + 1; j++) {
                    if (i == v) {
                        simp[i][j] = simp[i][j] / pivot;
                    } else if (j == u && i != v) {
                        simp[i][j] = -1 * simp[i][j] / pivot;
                    }
                }
            }
            check = 1;
            itr++;
        }
        int choice, choice1;
        int check2 = 0;
        do {
            printf("Total no. of iterations = %d\n", itr - 1);
            printf("1. Initial table,\n2. List of basic & non-basic variables in ith iteration,\n3. Table of ith iteration,\n");
            printf("4. Optimal solution.\nAny other no. to exit.\n");
            printf("Enter your choice: ");
            scanf("%d", & choice);
            if (choice == 1) {
                for (i = 1; i <= m + 1; i++) {
                    for (j = 0; j <= n + 1; j++)
                        printf("%.2f\t", itrtable[0][i][j]);
                    printf("\n");
                }
                printf("\n");
            }
            if (choice == 2) {
                printf("Enter the iteration no. (≤%d): ", itr - 1);
                scanf("%d", & choice1);
                for (i = 1; i <= n; i++) {
                    if (x[i] > 0)
                        printf("x[%d]= %.2f\t", i, simp[x[i]][n + 1]);
                    else
                        printf("x[%d]= 0.00\t", i);
                }
                for (i = 1; i <= m; i++) {
                    if (z[i] > 0)
                        printf("z[%d]= %.2f\t", i, simp[z[i]][n + 1]);
                    else
                        printf("z[%d]= 0.00\t", i);
                }
                printf("\n");
            }
            if (choice == 3) {
                printf("Enter the iteration no. (≤%d): ", itr);
                scanf("%d", & choice1);
                for (i = 1; i <= m + 1; i++) {
                    for (j = 0; j <= n + 1; j++)
                        printf("%.2f\t", itrtable[choice1][i][j]);
                    printf("\n");
                }
                printf("\n");
            }
            if (choice == 4) {
                if (maxcheck == 1)
                    printf("\nMaximum value of LPP is: %.2f\n", simp[m + 1][n + 1]);
                else
                    printf("\nMinimum value of LPP is: %.2f\n", -1.0 * simp[m + 1][n + 1]);
            }
            if (choice > 4)
                printf("Exiting.\n");
        }
        while (choice <= 4);
    }

int main() {
    int n, m; //m=no. of eqns, n=no. of variables
    printf("Enter the no. of variables: ");
    scanf("%d", & n);
    printf("Enter the no. of constraint eqns: ");
    scanf("%d", & m);
    simplex(m, n);
    return 0;
}
