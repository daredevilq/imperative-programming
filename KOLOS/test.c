#include <stdlib.h>
#include <stdio.h>


typedef struct matrix
{
    int rows;
    int columns;
    double **data;
}matrix;

int get(matrix *pm, int rows, int cols, double *pvalue)
{
    if (pm == 0 || rows<0 || cols<0)
    {
        return 0;
    }

    else
    {
        *pvalue = pm->data[rows][cols];
    }

}

void create_identity_matrix(matrix *pm, int size)
{
    pm->columns=size;
    pm->rows=size;

    for (int i = 0; i < size; i++)
    {
        pm->data = (double *)malloc(size * sizeof(double));
    

    }

}

double dot_prod_vector(const double *v1, const double *v2, int size)
{
    double result;
    int temp=0;
    for (int i = 0; i < size; i++)
    {
        temp = v1[i] * v2[i];
        result +=temp;

        temp=0;
    }
    
    return result;
}



typedef struct 
{
    double *result;
    int len;
}Data;




