#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
	int first;
	int second;
} pair;

int is_reflexive(pair *relation, int n){

	int flag=0;
	
	for (int i = 0; i < n; i++)
	{
		flag=0;
        for (int j = 0; j < n; j++)
        {
            if (relation[i].first==relation[j].first && relation[i].first==relation[j].second)
            {
                flag=1;
            }
        }
        
        if (flag==0)
        {
            return 0;
        }
        
	}
	
    flag=0;

    for (int i = 0; i < n; i++)
	{
		flag=0;
        for (int j = 0; j < n; j++)
        {
            if (relation[i].second==relation[j].first && relation[i].second==relation[j].second)
            {
                flag=1;
            }
        }
        
        if (flag==0)
        {
            return 0;
        }
        
	}

    return 1;

}


int is_irreflexive(pair *relation, int n)
{
	
	int flag=0;
	
	for (int i = 0; i < n; i++)
	{
		flag=0;
        for (int j = 0; j < n; j++)
        {
            if (relation[i].first!=relation[j].first && relation[i].first!=relation[j].second)
            {
                flag=1;
            }
        }
        
        if (flag==0)
        {
            return 0;
        }
        
	}
	
    flag=0;

    for (int i = 0; i < n; i++)
	{
		flag=0;
        for (int j = 0; j < n; j++)
        {
            if (relation[i].second!=relation[j].first && relation[i].second!=relation[j].second)
            {
                flag=1;
            }
        }
        
        if (flag==0)
        {
            return 0;
        }
        
	}

    return 1;


}

int is_symmetric(pair *relation, int n)
{	
	int flag=0;
	for (int i = 0; i < n; i++)
	{
		flag=0;
		for (int j = 0; j < n; j++)
		{
			if (relation[i].first==relation[j].second && relation[i].second==relation[j].first)
			{
				flag=1;
			}
		}
		if (flag==0)
		{
			return 0;
		}
	}
	return 1;

}


int read_relation(pair *relation) {

	int ssize;
	int left;
    int right;

	scanf("%d",&ssize);

	for (int i = 0; i < ssize; i++)
	{
		scanf("%d %d",&left,&right);
        relation[i].first=left;
        relation[i].second=right;
    
	}
	return ssize;

}

int is_antisymmetric(pair *relation, int n)
{
	int flag=0;
	for (int i = 0; i < n; i++)
	{
		flag=0;
		for (int j = 0; j < n; j++)
		{
			if (relation[i].first==relation[j].second && relation[i].second==relation[j].first)
			{
				if (relation[i].first!=relation[i].second)
				{
					return 0;
				}
				
			}
		}
	
	}
	return 1;

}

int is_asymmetric(pair *relation, int n){
	
	for (int i = 0; i < n; i++)
	{
		
		for (int j = 0; j < n; j++)
		{
			if (relation[i].first==relation[j].second && relation[i].second==relation[j].first)
			{
				return 0;
				
			}
		}
	
	}
	return 1;

}


int is_transitive(pair *relation, int n){
	
	int flag=0;
	for (int i = 0; i < n; i++)
	{
		
		for (int j = 0; j < n; j++)
		{
			flag=0;
			
			if (relation[i].second==relation[j].first)
			{
				for (int k = 0; k < n; k++)
				{
					if (relation[i].first==relation[k].first && relation[j].second==relation[k].second)
					{
						flag=1;
					}
				}
				
				if (flag==0)
				{
					return 0;
				}
			}
		}
	
	}
	return 1;


}

int is_partial_order(pair *relation, int n){
	if (is_reflexive(relation,n)==1 && is_antisymmetric(relation,n)==1 && is_transitive(relation,n)==1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}

int is_connected(pair *relation, int n)
{
	int flag=1;
	int X[2*n];
	int unique[2*n];
	int pointer=0;
	int counter1=0;
	int counter2=0;
    int temp=0;
    int flag_x_y=0;
	for (int i = 0; i < 2*n-1; i+=2)
	{
		X[i]=relation[temp].first;
		X[i+1]=relation[temp].second;
        temp++;
		
	}
	


	for (int i = 0; i < 2*n; i++)
	{
		flag=1;
		for (int j = 0; j < pointer; j++)
		{
			if (unique[j]==X[i])
			{
				flag=0;
			}
			
		}

		if (flag==1)
		{
			unique[pointer]=X[i];
			pointer++;
		}
	}
	
	flag=1;

	for (int i = 0; i < pointer; i++)
	{
		counter1=0;
        flag_x_y=0;
		
		for (int j = 0; j < n;j++)
		{
			if (unique[i]==relation[j].first || unique[i]==relation[j].second)
			{
				counter1++;
			
                if (relation[j].first==relation[j].second)
                {
                    flag_x_y=1;
                }
            }
			
		}
       
        if (flag_x_y==1)
        {
            if (counter1!=pointer)
			{
				flag=0;
                break;			
			}
        }

        else{
            if (counter1!=pointer-1)
                {
                    flag=0;
                    break;			
                }
            }   

	}
	
	return flag;

}

int is_total_order(pair *relation, int n)
{
	if (is_connected(relation,n)==1 && is_partial_order(relation,n==1))
	{
		return 1;
	}
	else{
		return 0;
	}

}


int get_domain(pair *relation, int n, int *array)
{
	int flag=1;
	int X[2*n];
	int unique[2*n];
	int pointer=0;
    int temp=0;
  
	for (int i = 0; i < 2*n-1; i+=2)
	{
		X[i]=relation[temp].first;
		X[i+1]=relation[temp].second;
        temp++;
		
	}
	
	for (int i = 0; i < 2*n; i++)
	{
		flag=1;
		for (int j = 0; j < pointer; j++)
		{
			if (unique[j]==X[i])
			{
				flag=0;
			}
			
		}

		if (flag==1)
		{
			unique[pointer]=X[i];
			pointer++;
		}
	}
	
	 int i, key, j;

    for (i = 1; i < pointer; i++) {
        key = unique[i];
        j = i - 1;
 
        while (j >= 0 && unique[j] > key) {
            unique[j + 1] = unique[j];
            j = j - 1;
        }
        unique[j + 1] = key;
    }


	for (int i = 0; i < pointer; i++)
	{
		array[i]=unique[i];
	}
	
	return pointer;
}

void print_int_array(const int *array, int n) {
	printf("%d",n);
	printf("\n");

	for (int i = 0; i < n; i++)
	{
		printf("%d ",array[i]);
	}
	printf("\n");	

}

int find_max_elements(pair *relation, int n, int *max_elements)
{
	int counter=0;

	int flag=1;
	int X[2*n];
	int unique[2*n];
	int pointer=0;
    int temp=0;
	for (int i = 0; i < 2*n-1; i+=2)
	{
		X[i]=relation[temp].first;
		X[i+1]=relation[temp].second;
        temp++;
		
	}
	
	for (int i = 0; i < 2*n; i++)
	{
		flag=1;
		for (int j = 0; j < pointer; j++)
		{
			if (unique[j]==X[i])
			{
				flag=0;
			}
			
		}

		if (flag==1)
		{
			unique[pointer]=X[i];
			pointer++;
		}
	}
	
	int i, key, j;
    for (i = 1; i < pointer; i++) {
        key = unique[i];
        j = i - 1;
 
        while (j >= 0 && unique[j] > key) {
            unique[j + 1] = unique[j];
            j = j - 1;
        }
        unique[j + 1] = key;
    }


	flag=1;

	for (int i = 0; i < pointer; i++)
	{
		flag=1;
		for (int j = 0; j< n; j++)
		{
			if (unique[i]!=relation[j].second && unique[i]==relation[j].first )
			{
				flag=0;
			}
					
		}

		if (flag==1)
		{
			max_elements[counter]=unique[i];
			counter++;
		}
			
	}
	
	return counter;

}

int find_min_elements(pair *relation, int n, int *max_elements){
int counter=0;

	int flag=1;
	int X[2*n];
	int unique[2*n];
	int pointer=0;
    int temp=0;
	for (int i = 0; i < 2*n-1; i+=2)
	{
		X[i]=relation[temp].first;
		X[i+1]=relation[temp].second;
        temp++;
		
	}
	
	for (int i = 0; i < 2*n; i++)
	{
		flag=1;
		for (int j = 0; j < pointer; j++)
		{
			if (unique[j]==X[i])
			{
				flag=0;
			}
			
		}

		if (flag==1)
		{
			unique[pointer]=X[i];
			pointer++;
		}
	}
	
	int i, key, j;
    for (i = 1; i < pointer; i++) {
        key = unique[i];
        j = i - 1;
 
        while (j >= 0 && unique[j] > key) {
            unique[j + 1] = unique[j];
            j = j - 1;
        }
        unique[j + 1] = key;
    }


	flag=1;

	for (int i = 0; i < pointer; i++)
	{
		flag=1;
		for (int j = 0; j< n; j++)
		{
			if (unique[i]!=relation[j].first && unique[i]==relation[j].second )
			{
				flag=0;
			}
					
		}

		if (flag==1)
		{
			max_elements[counter]=unique[i];
			counter++;
		}
			
	}
	
	return counter;

}

int add_relation (pair *tab, int n, pair new_pair) {

	int flag=1;

	for (int i = 0; i < n; i++)
	{
		if (tab[i].first==new_pair.first && tab[i].second==new_pair.second )
		{
			flag=0;
		}
		
	}
	if (flag==1)
		{
			tab[n].first=new_pair.first;
			tab[n].second=new_pair.second;
		}
	
}


int composition (pair *relation, int size, pair *relation_2, int size_2, pair *comp_relation)
{
	int counter=0;
	int flag=1;
	for (int i = 0; i < size_2; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (relation_2[i].second==relation[j].first)
			{
			
				flag=1;
				for (int k = 0; k < counter; k++)
				{
					if (comp_relation[k].first==relation_2[i].first && comp_relation[k].second==relation[j].second)
					{
						flag=0;
					}
				
				}
				if (flag==1)
				{
					comp_relation[counter].first=relation_2[i].first;
					comp_relation[counter].second=relation[j].second;
					counter++;
				}
			}
		}
	}
	
	flag=1;
	int X[2*counter];
	int unique[2*counter];
	int pointer=0;
    int temp=0;
  
	for (int i = 0; i < 2*counter-1; i+=2)
	{
		X[i]=relation[temp].first;
		X[i+1]=relation[temp].second;
        temp++;
		
	}
	
	for (int i = 0; i < 2*counter; i++)
	{
		flag=1;
		for (int j = 0; j < pointer; j++)
		{
			if (unique[j]==X[i])
			{
				flag=0;
			}
			
		}

		if (flag==1)
		{
			unique[pointer]=X[i];
			pointer++;
		}
	}

	return pointer;


}




int main(){
    pair relation[100];
    pair relation_2[100];
    int size = read_relation(relation);
    int ordered, size_2, n_domain;
    int domain[100];
    int max_elements[100];
	int min_elements[100];
    pair comp_relation[100];
    //printf("%d ", is_reflexive(relation, size));
    //printf("%d ", is_irreflexive(relation, size));
    //printf("%d ", is_symmetric(relation, size));
    //printf("%d ", is_antisymmetric(relation, size));
    //printf("%d ", is_asymmetric(relation, size));
    //printf("%d\n", is_transitive(relation, size));
    //printf("%d ", is_partial_order(relation, size));
    //printf("%d ", is_connected(relation,size));
    printf("%d ", is_total_order(relation,size));

    //n_domain = get_domain(relation, size, domain);
    //print_int_array(domain, n_domain);

    //int no_max_elements = find_max_elements(relation, size, max_elements);
	//int no_min_elements = find_min_elements(relation, size, min_elements);
	//print_int_array(max_elements, no_max_elements);
	//print_int_array(min_elements, no_min_elements);

    //size_2 = read_relation(relation_2);
	//printf("%d\n", composition(relation, size, relation_2, size_2, comp_relation));

    //for (int i = 0; i < 11; i++)
    //{
      //  printf("%d %d",comp_relation[i].first,comp_relation[i].second);
    //    printf("\n");
   // }
    
    

}

