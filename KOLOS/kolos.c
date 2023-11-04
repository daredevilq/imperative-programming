void free_matrix(Matrix **pmatrix) {
    
    free((*pmatrix)->data);
    free(*pmatrix);

}


#include <stdlib.h> // zeby skorzystac 
#include <time.h>   // 

Matrix* random_matrix(int rows, int cols) {
   
    Matrix* new_matrix = create_matrix(rows, cols);

    srand(time(NULL));


    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            new_matrix->data[i*cols + j] = (double)rand() / RAND_MAX;
        }
    }

    return new_matrix;
}


int set(Matrix* pm, int row, int col, double value) {
   
    if ( row >= pm->rows || col >= pm->cols || row < 0 || col < 0 || pm == NULL || pm->data == NULL) {
        return 0;
    }

    else{
    pm->data[col + row*pm->cols] = value;

    return 1;
    }
}

int get(Matrix* pm, int row, int col, double* pvalue) {

    if ( row >= pm->rows || col >= pm->cols || row < 0 || col < 0 || pm == NULL || pm->data == NULL) {
        return 0;
    }

    else {

    *pvalue = pm->data[col + row*pm->cols];
    // lub pvalue = &(pm->data[col + row*pm->cols])
    return 1;
    }
}


double dot_prod_vect(const double* v1, const double* v2, int size) {
    double result = 0;
    double temp = 0;
 
    for (int i = 0; i < size; i++) {
        temp = v1[i] * v2[i];
        result += temp;
        temp = 0;
    }

    return result;
}


void mul_vect(double *result, const Matrix *pm, const double * vect) {

    for (int i = 0; i < pm->rows; i++) {

        result[i] = dot_prod_vect(&(pm->data[i * pm->cols]), vect, pm->cols);
    
    }
}

#include <stdio.h>  // dla funkcji printf()

void print_row(double* row, size_t n) {
    // Sprawdzamy, czy wskaźnik do wiersza jest prawidłowy
    if (row == NULL) {
        return;
    }

    // Drukujemy elementy wiersza
    for (size_t i = 0; i < n; i++) {
        printf("%f ", row[i]);
    }

    printf("\n");
}
Ta funkcja drukuje na ekran n elementów tablicy row. Jeżeli wskaźnik do tablicy jest NULL, funkcja nie robi nic.

Elementy są drukowane jeden po drugim, oddzielone spacją, a na końcu drukowany jest znak końca linii (\n), aby kolejne wywołania funkcji drukowały elementy w nowych liniach. Wartości są drukowane jako liczby zmiennoprzecinkowe (%f), więc jeżeli chcesz zmienić format wydruku (na przykład na naukowy lub z określoną liczbą miejsc po przecinku), musisz zmienić format drukowania w funkcji printf().





User
f2) void find row (Matrix M, double key)
szuka w macierzy M wiersza, którego średnia arytmetyczna wszystkich elementów wiersza
ma wartość różniącą się od key o nie więcej niż 1% wartości key - polecana funkcja fabs. Jeżeli wiersz zostaje znaleziony, to funkcja wypisuje go na ekran wywołując funkcję print_row.
Uwaga: Wiersze macierzy M są posortowane wg rosnącej wartości średniej arytmetycznej wszystkich elementów wiersza.
W funkcji należy wywołać biblioteczną funkcję bsearch. - inne wersje będą oceniane o 3 pkt. niżej. Napisz definicję komparatora compar dla funkcji bsearch wywoływanej w find_row
int compar (const void*a, const void*b)
Do przekazania liczby kolumn macierzy do funkcji compar użyj globalnej zmiennej glob_columns o zasięgu plikowym i łączności wewnętrznej.
Uzupełnij definicję tej zmiennej.
.. glob_columns;
ChatGPT
Zadanie można rozwiązać, definiując globalną zmienną glob_columns oraz funkcje average (do obliczania średniej arytmetycznej elementów wiersza), compar (komparator dla bsearch) i find_row.

Poniżej znajduje się kod:

c
Copy code
#include <stdlib.h>  // dla funkcji bsearch(), qsort(), fabs()
#include <stdio.h>   // dla funkcji printf()

static int glob_columns;  // globalna zmienna przechowująca liczbę kolumn

double average(const double* row) {
    double sum = 0.0;
    for (int i = 0; i < glob_columns; i++) {
        sum += row[i];
    }
    return sum / glob_columns;
}

int compar(const void* a, const void* b) {
    double avg_a = average(a);
    double avg_b = average(b);
    return avg_a < avg_b ? -1 : avg_a > avg_b;
}

void find_row(Matrix* M, double key) {
    glob_columns = M->cols;
    double* found_row = (double*)bsearch(&key, M->data, M->rows, M->cols * sizeof(double), compar);

    if (found_row && fabs(average(found_row) - key) <= 0.01 * key) {
        print_row(found_row, M->cols);
    }
}


Uwaga: Wartości wierszy muszą być posortowane rosnąco według ich średnich arytmetycznych przed wywołaniem funkcji find_row. Jeżeli nie są, wynik działania funkcji bsearch jest nieokreślony.






