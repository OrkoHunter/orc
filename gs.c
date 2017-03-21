#include <stdio.h>
#include <math.h>
#include <stdbool.h>

int my_func() {
	int n, i, j, k;
	double er;
	printf("\nEnter the order of the matrix : ");
	scanf("%d", &n);
	printf("\nEnter the stopping criteria : ");
	scanf("%lf", &er);
	int a[n][n+1];
	for (i=0; i<n; i++) {
		for (j=0; j<n+1; j++) {
			scanf("%d", &a[i][j]);
		}
	}
	float x[n], y[n];
	for (i=0; i++; i<n) {
		x[i] = 0;
		y[i] = 0;
	}
	

	int itr = 0;
	int flag = 0;
	while(true) {
		itr = itr + 1;
		for (i=0; i<n; i++) {
			x[i] = a[i][n];
			for (j=1; j<n; j++) {
				if (i != j)
					x[i] = x[i] - a[i][j]*x[j];
			}
			x[i] = (1.0 * x[i])/a[i][i];
		}
		
		for (k=0; k<n; k++) {
			if (abs(x[k] - y[k]) > 0.000001) {
				printf("itr = %d\n", itr);
				for (i=0; i<n; i++) {
					y[i] = x[i];
					printf("%f\n", x[i]);
				}
			} else {flag = 1; break;}
		}
		if (flag == 1)
			break;
	}		
}

	
int main()
{
	my_func();
}

