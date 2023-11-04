#include <stdio.h>
#include <math.h>


int main(){


    int A[4][4]={{1,-1,2,-1},{2,-2,3,-3},{1,1,1,0},{1,-1,4,3}};

    int indices[4];
    int check[4];
	int swaps=-1;

	for (int i = 0; i < 4; i++)
	{
		indices[i]=i;
        check[i]=-1;
	}
	

	double max_val,min_val;
	int max_indx,min_indx;
	for (int i = 0; i < 3; i++)
	{
		max_val=A[0][i];
        max_indx=0;
		for (int j = 0; j < 4; j++)
		{
			if (fabs(A[j][i])>fabs(max_val) && check[j]==-1)
			{
				max_indx=j;
				max_val=A[j][i];
			}

        
		}

		indices[i]=max_indx;
        indices[max_indx]=i;
        check[max_indx]=1;
        
    }   


    for (int i = 0; i < 4; i++)
    {
        printf("%d",indices[i]);
    }
    








    return 0;
}



////


