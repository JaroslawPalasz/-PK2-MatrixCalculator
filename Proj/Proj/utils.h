#ifndef UTILS_H
#define UTILS_H
#include "matrix_struct.h"

typedef struct {
	int matrix_count;
	int no_operations;
	double my_measured_time;
	double lib_measured_time;
} matrix_utils;

/*creates data template ready to fill - "2D array"*/
double** data_builder(int rows, int columns);

/*connects data to matrix*/
matrix* matrix_builder(int rows, int columns, double **my_value, int matrix_id);

/*creates array of matrices*/
matrix*make_matrix_struct(matrix*p_matrix, matrix*p_matrix_array, matrix_utils*p_struct);

/*allows to edit values in matrix*/
void edit_matrix(matrix*matrix, matrix_utils*p_struct);

/*uses strtok to split string*/
char * splitter(char array[], char * delimiter, int first_split);

/*returns an integer from char array*/
int number_from_char_array(char array[], int i, char delimiter);

/*executes given matrix operation*/
int execute(matrix*matrix1, matrix*matrix2, char choice, matrix_utils*p_struct);

/*uses isdigit library function to check whether string is numeric or not*/
int check_if_number(char*c_array);

/*checks if there exist columns with identical values in square matrix*/
int check_same_cols(matrix *m1, int first_column, int D_is_zero);

/*checks if there exist rows with identical values*/
int check_same_rows(matrix *m1, int first_row, int D_is_zero);

/*checks if there exist column or row full of zeros*/
int check_rows_cols_for_0(matrix *m1);

/*frees all of the allocated memory-including matrix struct*/
void free_all(matrix*matrix_array, matrix_utils*p_struct);

/*frees data*/
void free_data(double **data, int rows);

/*test function which generates a couple of big square matrices - needed for chart*/
matrix *big_matrix(matrix*matrix_array, matrix_utils*p_struct);

/*get random double value ranging from min to max value*/
double randfrom(double min, double max);

#endif