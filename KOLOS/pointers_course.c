#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void print(int *pointer_to_array, int size)
{
    for (int i = 0; i < size; i++)
    {
        //printf("%d ",*(pointer_to_array));
        //pointer_to_array++;
        printf("%d ",(pointer_to_array[i]));
    }   
    
}


int add(int a  , int b )
{
    return a + b;
}



void Af()
{
    printf("hello");
}

void Bf(void (*A)())
{
    A();
}


int main()
{
    int  a=1025;
    int *p;

    p = &a;

    printf("value: %d and bytes: %d\n",*p,p);

    char *c;

    c = (char * )p; //typcasting 

    //printf("%d\n",c);

    void *p0; // void type pointer 

    p0=p;

    int **q;

    q = &p;

    //printf("a: %d %d\n",a,&a);
    //printf("p: %d %d %d\n",*p,p,&p);
    //printf("q: %d %d\n",*(*q),q);

    int A[5] = {1, 2, 3, 4, 5};

    int *arr_p;

    arr_p=&(A[0]); // or arr_p = A simply 

    //printf("%d ",*arr_p);

    for (int i; i <  5 ; i++)
    {
        //printf("%d\n", A[i]);
    }
    
    //print(arr_p,5);

    char word[]= "ALA MA KOTA";
    int len = strlen(word);
    //printf("%d",len);

    char *word2 = "asdasdasda";

    int B[2][3] = {{1, 2, 3},
                    {4, 5, 6}};
    

    int *arr;

    //printf("%d ",*B );
    //printf("%d ",*(*B+1));
    // B[i][j] =  *(B[i] + j) = *((*B + i ) + j)

    //printf("%d %d %d",B,*B,*(B[0]+1));

    // Dynamic memory

    int *pointer;

    pointer = (int*)malloc(sizeof(int)); // malloc tylko przez referencje 
    
    *pointer = 10;
    
    free(pointer);
    
    // (void *)malloc(sizeof)
    // (void *)calloc(size_t num - liczba el, sizeof() - wielkosc) - dodatkowo wypelnia zaaloowane miejsce zerami
    // (void *)realloc(void * pointer - wskaznik do bloku istniejacego, size_t size -rozmiar nowego bloku)

    
    // wskazniki od funkcji
    int d; 
    int (*f_pointer)(int, int) =&add;



    d = f_pointer(2,3); // or d = (*p)(2,3)
    //printf("%d",d);
    
    //void (*pointer_a)() = Af;
    

    //Bf(pointer_a);   
    Bf(Af);

    return 0;
}