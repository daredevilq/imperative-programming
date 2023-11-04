#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define TAB_SIZE  1000
#define BUF_SIZE  1000

int get(int cols, int row, int col, const int *A) {


}

void set(int cols, int row, int col, int *A, int value) {
}

void prod_mat(int rowsA, int colsA, int colsB, int *A, int *B, int *AB) {



}

void read_mat(int rows, int cols, int *t) {
	for (int i = 0; i < rows*cols; i++)
	{
		scanf("%d",&t[i]);
	}
	

}

void print_mat(int rows, int cols, int *t) {
    for (int i = 0; i < rows*cols; i++)
	{   
		printf("%d ",t[i]);
        if ((i+1)%cols==0)
        {
            printf("\n");
        }
        
    }
}

int read_char_lines(char *array[]) {
}

void write_char_line(char *array[], int n) {
}

void delete_lines(char *array[]) {
}

int read_int_lines_cont(int *ptr_array[]) {
}

void write_int_line_cont(int *ptr_array[], int n) {
}

typedef struct {
	int *values;
	int len;
	double average;
} line_type;

int read_int_lines(line_type lines_array[]) {
}

void write_int_line(line_type lines_array[], int n) {
}

void delete_int_lines(line_type array[], int line_count) {
}

int cmp (const void *a, const void *b) {
}

void sort_by_average(line_type lines_array[], int line_count) {
}

typedef struct {
	int r, c, v;
} triplet;

int read_sparse(triplet *triplet_array, int n_triplets) {
}

int cmp_triplets(const void *t1, const void *t2) {
}

void make_CSR(triplet *triplet_array, int n_triplets, int rows, int *V, int *C, int *R) {
}

void multiply_by_vector(int rows, const int *V, const int *C, const int *R, const int *x, int *y) {
}

void read_vector(int *v, int n) {
}

void write_vector(int *v, int n) {
}

int read_int() {
	char c_buf[BUF_SIZE];
	fgets(c_buf, BUF_SIZE, stdin);
	return (int)strtol(c_buf, NULL, 10);
}

int main(void) {
	int to_do = read_int();

	int A[TAB_SIZE], B[TAB_SIZE], AB[TAB_SIZE];
	int n, lines_counter, rowsA, colsA, rowsB, colsB;
	int rows, cols, n_triplets;
	char *char_lines_array[TAB_SIZE] = { NULL };
	int continuous_array[TAB_SIZE];
	int *ptr_array[TAB_SIZE];
	triplet triplet_array[TAB_SIZE];
	int V[TAB_SIZE], C[TAB_SIZE], R[TAB_SIZE];
	int x[TAB_SIZE], y[TAB_SIZE];
	line_type int_lines_array[TAB_SIZE];

	switch (to_do) {
		case 1:
			scanf("%d %d", &rowsA, &colsA);
			read_mat(rowsA, colsA, A);
            print_mat(rowsA,colsA,A);
			scanf("%d %d", &rowsB, &colsB);
			read_mat(rowsB, colsB, B);
			prod_mat(rowsA, colsA, colsB, A, B, AB);
			print_mat(rowsA, colsB, AB);
			break;

	}
	return 0;
}