/*Napisz program, który dla zadanej liczby naturalnej n
 odpowiada na pytanie, czy liczba ta jest iloczynem
 dowolnych dwóch kolejnych wyrazów ciągu Fibonacciego. 
 Zakładamy, że pierwsze dwa wyrazy ciągu Fibonacciego to 0 i 1. */


 #include <stdio.h>
 #include <stdlib.h>



 int main()
 {
    int n=41;
    int prev=0;
    int curr=1;
    int next=0;


    while (prev<=n)
    {
        if (prev*curr==n)
        {
            printf("TAK");
            return 0;
        }
        next=curr+prev;
        prev=curr;
        curr=next;



    }
    
    printf("NIE");




    return 0;
 }




