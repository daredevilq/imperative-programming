#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REL_SIZE 100
#define MAX_RANGE 100

typedef struct {
	int first;
	int second;
} pair;

// Add pair to existing relation if not already there
int add_relation (pair*, int, pair);

// Case 1:

// The relation R is reflexive if xRx for every x in X
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


// The relation R on the set X is called irreflexive
// if xRx is false for every x in X
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

// A binary relation R over a set X is symmetric if:
// for all x, y in X xRy <=> yRx
int is_symmetric(pair *relation, int n) // idk czy 1 1 jest symetryczne
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

// A binary relation R over a set X is antisymmetric if:
// for all x,y in X if xRy and yRx then x=y
int is_antisymmetric(pair *relation, int n)
{
	
	for (int i = 0; i < n; i++)
	{
		
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

// A binary relation R over a set X is asymmetric if:
// for all x,y in X if at least one of xRy and yRx is false
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

// A homogeneous relation R on the set X is a transitive relation if:
// for all x, y, z in X, if xRy and yRz, then xRz
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

// Case 2:

// A partial order relation is a homogeneous relation that is
// reflexive, transitive, and antisymmetric
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



// Relation R is connected if for each x, y in X:
// xRy or yRx (or both)
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






// A total order relation is a partial order relation that is connected
int is_total_order(pair *relation, int n)
{	
	int con=is_connected(relation,n);
	int partial=is_partial_order(relation,n);

	if (con==1 && partial==1)
	{
		return 1;
	}
	else{
		return 0;
	}

}

// Relation R is connected if for each x, y in X:
// xRy or yRx (or both)


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

// Case 3:

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

// Comparator for pair
int cmp_pair (const void *a, const void *b) {

}

int insert_int (int *tab, int n, int new_element) {
}

// Add pair to existing relation if not already there
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

// Read number of pairs, n, and then n pairs of ints
int read_relation(pair *relation) {

	int size;
	int left;
    int right;

	scanf("%d",&size);
	for (int i = 0; i < size; i++)
	{
		scanf("%d %d",&left,&right);
        relation[i].first=left;
        relation[i].second=right;

	}
	
	return size;


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

int main(void) {
	int to_do;
	pair relation[MAX_REL_SIZE];
	pair relation_2[MAX_REL_SIZE];
	pair comp_relation[MAX_REL_SIZE];
	int domain[MAX_REL_SIZE];
	int max_elements[MAX_REL_SIZE];
	int min_elements[MAX_REL_SIZE];

	scanf("%d",&to_do);
	int size = read_relation(relation);
	int ordered, size_2, n_domain;

	switch (to_do) {
		case 1:
			printf("%d ", is_reflexive(relation, size));
			printf("%d ", is_irreflexive(relation, size));
			printf("%d ", is_symmetric(relation, size));
			printf("%d ", is_antisymmetric(relation, size));
			printf("%d ", is_asymmetric(relation, size));
			printf("%d\n", is_transitive(relation, size));
			break;
		case 2:
			ordered = is_partial_order(relation, size);
			n_domain = get_domain(relation, size, domain);
			printf("%d %d\n", ordered, is_total_order(relation, size));
			print_int_array(domain, n_domain);
			if (!ordered) break;
			int no_max_elements = find_max_elements(relation, size, max_elements);
			int no_min_elements = find_min_elements(relation, size, min_elements);
			print_int_array(max_elements, no_max_elements);
			print_int_array(min_elements, no_min_elements);
			break;
		case 3:
			size_2 = read_relation(relation_2);
			printf("%d\n", composition(relation, size, relation_2, size_2, comp_relation));
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	return 0;
}