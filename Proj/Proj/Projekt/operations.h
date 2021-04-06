#ifndef OPERATIONS_H
#define OPERATIONS_H
#include "matrix_struct.h"
#include "utils.h"

/*below functions for basic matrix operations*/
matrix* matrix_addition(matrix* m1, matrix* m2, matrix_utils*p_struct);

matrix* matrix_substraction(matrix*m1, matrix*m2, matrix_utils*p_struct);

matrix* matrix_multiplication(matrix*m1, matrix*m2, matrix_utils*p_struct);

/*below functions transpose different matrices*/
matrix* matrix_transposition(matrix*m1, matrix_utils*p_struct);

matrix*transpose_matrix_square(matrix*m1, matrix_utils*p_struct);

matrix*transpose_matrix_non_square(matrix*m1, matrix_utils*p_struct);

/*below functions calculate determinant of matrices of specific size */
long double matrix_determinant(matrix*m1, matrix_utils*p_struct);

double determinant_matrix_1x1(matrix*m1, matrix_utils*p_struct);

double determinant_matrix_2x2(matrix*m1, matrix_utils*p_struct);

double determinant_matrix_3x3(matrix*m1, matrix_utils*p_struct);

long double determinant_matrix_NxN(matrix*m1, matrix_utils*p_struct); //Doolittle's version of LU decomposition

/*function creates an inverse matrix*/
matrix*inverse_matrix(matrix*m1, matrix_utils*p_struct);

/*Below functions used for creating inverse matrix*/
void create_gauss_jordan_data_template(matrix *m1, matrix *new_matrix, int rows, int cols);

void create_gauss_jordan_data(int rows, int cols, matrix *new_matrix, matrix *identity_matrix);

void lower_triangular_operations_data(int rows, int cols, matrix *new_matrix);

void upper_triangular_operations_data(int rows, int cols, matrix *new_matrix);

#endif
