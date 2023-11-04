#include <stdio.h>
#include <math.h>


void linspace(double v[], double start, double stop, int n)
{
    if (n==0)
    {
        return v;
    }

    if (n==1)
    {
        v[0]=start;
        printf("%.2f",v[0]);
    }
    
    double r=abs(start-stop)/(n-1);
    
    for ( int i = 0; i < n; i++)
    {   

        printf("%.2f ",start);
        start+=r;

    }  
    
}

void add(double v1[], const double v2[], int n) 
{
    for (int i = 0; i < n; i++)
    {
        v1[i]+=v2[i];
        printf("%.2f ",v1[i]);    
    }


}

double dot_product(const double v1[], const double v2[], int n) 
{
    double sum;
    for (int i = 0; i < n ; i++)
    {
        sum+=v1[i]*v2[i];

    }
    
    //printf("%.2f ",sum);
    return("%.2f",sum);
}


void multiply_by_scalar(double v[], int n, double scalar) 
{
    for (int i = 0; i < n; i++)
    {
        v[i]*=scalar;

        //printf("%.2f ",v[i]);
    }
    

}


void range(double array[], double start, double step, int n)
{
    for (int i = 0; i < n; i++)
    {
        int to_add=step*i;
        array[i]=start+to_add;
        //printf("%.2f",array[i]);

    }
    


}



int main() 

{
    double v[11];

    linspace(v,-10,10,11);

    return 0;


    
}
