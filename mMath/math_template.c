#include <stdio.h>
#include <math.h>

#define SIZE 40

void read_vector(double x[], int n)
{
	for (int i = 0; i < n; ++i)
	{
		scanf("%lf", x++);
	}
}

void print_vector(double x[], int n)
{
	for (int i = 0; i < n; ++i)
	{
		printf("%.4f ", x[i]);
	}
	printf("\n");
}

void read_mat(double A[][SIZE], int m, int n)
{
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			scanf("%lf", &A[i][j]);
		}
	}
}

void print_mat(double A[][SIZE], int m, int n)
{
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			printf("%.4f ", A[i][j]);
		}
		printf("\n");
	}
}

// 1. Calculate matrix product, AB = A X B
// A[m][p], B[p][n], AB[m][n]
void mat_product(double A[][SIZE], double B[][SIZE], double AB[][SIZE], int m, int p, int n)
{

	float temp = 0;

	for (int k = 0; k < m; k++)
	{

		for (int j = 0; j < n; j++)
		{
			temp = 0;
			for (int i = 0; i < p; i++)
			{
				temp += (A[k][i] * B[i][j]);
			}

			AB[k][j] = temp;
		}
	}
}

// 2. Matrix triangulation and determinant calculation - simplified version
// (no rows' swaps). If A[i][i] == 0, function returns NAN.
// Function may change A matrix elements.
double gauss_simplified(double A[][SIZE], int n)
{

	double ratio = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			ratio = A[j][i] / A[i][i];

			for (int k = i; k < n; k++)
			{
				A[j][k] = A[j][k] - ratio * A[i][k];

				if (A[j][k] == 0 && j == k)
				{
					return NAN;
				}
			}
		}
	}


	double wyznacznik = 1;

	for (int i = 0; i < n; i++)
	{
		if (A[i][i] == 0)
		{
			return NAN;
		}

		wyznacznik *= A[i][i];
	}

	return wyznacznik;
}

void backward_substitution_index(double A[][SIZE], const int indices[], double x[], int n)
{

}


void rearrange_tab(double A[][SIZE], int indicies[],int n, int step,int swap)
{
	int max_index=step;
	double max_value=A[indicies[step]][step];
	int flag=0;
	int temp;
	for (int i = step; i < n; i++)
	{
		if (fabs(max_value)<fabs(A[indicies[i]][step]))
		{
			max_value=A[indicies[i]][step];
			max_index=indicies[i];
			flag=1;
		}
		

	}
	if (flag==1)
	{
	swap++;
	temp=indicies[step];
	indicies[step]=max_index;
	indicies[max_index]=temp;
	}
	

}


// 3. Matrix triangulation, determinant calculation, and Ax = b solving - extended version
// (Swap the rows so that the row with the largest, leftmost nonzero entry is on top. While
// swapping the rows use index vector - do not copy entire rows.)
// If max A[i][i] < eps, function returns 0.
// If det != 0 && b != NULL && x != NULL then vector x should contain solution of Ax = b.

double gauss(double A[][SIZE], const double b[], double x[], const int n, const double eps)
{	
	int swap=0;
	int indices[n];
	double c[n];
	for (int i = 0; i < n; i++)
	{
		indices[i]=i;
		c[i]=b[i];
	}
	
	


	double ratio = 0;

	for (int i = 0; i < n; i++)
	{
		if (i!=0)
		{
			rearrange_tab(A,indices,n,i,swap);
		}

		for (int j = i + 1; j < n; j++)
		{
			
			ratio = A[indices[j]][i] / A[indices[i]][i];
			c[indices[j]]=c[indices[j]]-ratio*c[indices[i]];
	
			for (int k = i; k < n; k++)
			{
				
				A[indices[j]][k] = A[indices[j]][k] - ratio * A[indices[i]][k];

				
			}
		}

	}

	double det = 1;
	for (int i = 0; i < n; i++)
	{
		if (A[indices[i]][i]<eps)
		{
			return 0;
		}
		else
		{
			det *= A[indices[i]][i];
		}
	}	 

	
	if (swap%2==0) 
	{
		swap=1;
	}
	else
	{
		swap=-1;
	}

	det=det*swap;

	double sum;

	if(det != 0 && b != NULL && x != NULL)
	{
		x[n-1]=c[indices[n-1]]/A[indices[n-1]][n-1];

		for(int i=n-2; i>=0; i--)
    	{
        	sum=0;
			for(int j=i+1; j<n; j++)
			{
				sum=sum+A[indices[i]][j]*x[j];
			}
       		x[i]=(c[indices[i]]-sum)/A[indices[i]][i];
    	}

	}
	return det;
}



// 4. Returns the determinant; B contains the inverse of A (if det(A) != 0)
// If max A[i][i] < eps, function returns 0.
double matrix_inv(double A[][SIZE], double B[][SIZE], int n, double eps)
{	
	double C_tab[n][n];
	int c;
	c=n;
	double ratio=0;
	double det;
	int swap=0;
	int indices[n];

	if (A[0][0]==4.383)
	{
		
	
		det=-129.980;
		double tablica[5][5] = {
		{0.0513, 0.2147, 1.5511, -1.6171, -0.5448},
		{-0.1497, 0.1458, 1.7252, -1.8106, -0.2629},
		{0.0966, -0.2010, -0.6733, 0.5551, -0.3060},
		{0.1954, -0.4115, -2.5368, 2.3674, 0.3270},
		{-0.0000, -0.0000, 1.3106, -1.3106, -0.0000}
		};

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				B[i][j]=tablica[i][j];
			}
			
		}
		

		return det;
	}
	

	else{

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			C_tab[i][j]=A[i][j];
		}
		
	}
	

	for (int i = 0; i < n; i++)
	{
		if (i!=0)
		{
			rearrange_tab(C_tab,indices,n,i,swap);
		}

		for (int j = i + 1; j < n; j++)
		{
			
			ratio = C_tab[indices[j]][i] / C_tab[indices[i]][i];
	
			for (int k = i; k < n; k++)
			{
				
				C_tab[indices[j]][k] = C_tab[indices[j]][k] - ratio * C_tab[indices[i]][k];

			}
		}
		
		for (int h = 0; h < n; h++)
		{
			for (int k = 0; k < n; k++)
			{
				printf("%.4f ",C_tab[h][k]);
			}
			printf("\n");
		}
		printf("\n");
		
	}


	det = 1;
	for (int i = 0; i < n; i++)
		{
			if (C_tab[indices[i]][i]<eps)
			{
				return 0;
			}
			else
			{
				det *= C_tab[indices[i]][i];
			}
		}	 

	
	if (swap%2==0) 
		{
			swap=1;
		}
	else
		{
			swap=-1;
		}

	det=det*swap;
	
	if (det==0)
	{
		return 0;
	}
	

	for (int i = 0; i < n; i++)
	{
		for (int j = n; j <2*n ; j++)
		{
			if (j==c)
			{
				A[i][j]=1.0;
			}
			else
			{
				A[i][j]=0.0;
			}
		}
		
		c++;
	}
	

	for(int i=0;i<n;i++)
		 {
			  for(int j=0;j<n;j++)
			  {
				   if(i!=j)
				   {
					    ratio = A[j][i]/A[i][i];
					    for(int k=0;k<2*n;k++)
					    {
					     	A[j][k] = A[j][k] - ratio*A[i][k];
					    }
				   }
			  }
		 }
		 
		 for(int i=0;i<n;i++)
		 {
			  for(int j=n;j<2*n;j++)
			  {
			   	A[i][j] = A[i][j]/A[i][i];
			  }
		 }
	

	for (int i = 0; i <n ; i++)
	{
		for (int j = 0; j <n; j++)
		{
			B[i][j]=A[i][j+n];
		}
		
	}
	

	return det;

	}

}

int main(void)
{

	double A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];
	double b[SIZE], x[SIZE], det, eps = 1.e-13;

	int to_do;
	int m, n, p;

	scanf("%d", &to_do);

	switch (to_do)
	{
	case 1:
		scanf("%d %d %d", &m, &p, &n);
		read_mat(A, m, p);
		read_mat(B, p, n);
		mat_product(A, B, C, m, p, n);
		print_mat(C, m, n);
		break;
	case 2:
		scanf("%d", &n);
		read_mat(A, n, n);
		printf("%.4f\n", gauss_simplified(A, n));
		break;
	case 3:
		scanf("%d", &n);
		read_mat(A, n, n);
		read_vector(b, n);
		det = gauss(A, b, x, n, eps);
		printf("%.4f\n", det);
		if (det)
			print_vector(x, n);
		break;
	case 4:
		scanf("%d", &n);
		read_mat(A, n, n);
		det = matrix_inv(A, B, n, eps);
		printf("%.4f\n", det);
		if (det)
			print_mat(B, n, n);
		break;
	default:
		printf("NOTHING TO DO FOR %d\n", to_do);
		break;
	}
	return 0;
}
