#ifndef VALIDATE_H
#define VALIDATE_H

#include "matrix_struct.h"
#include "utils.h"

/*function validates if 2 matrices can be added/substracted (each matrix has the same number of rows and the same number of columns as the other)*/
int validate_addition_substraction(matrix*m1, matrix*m2);

/*function validates multiplication process (the number of columns in the first matrix equals the number of rows in the second)*/
int validate_multiplication(matrix*m1, matrix*m2);

/*function checks if matrix is square*/
int validate_determinant(matrix*m1);

/*validates inversion process, matrix has an inverse if its determinant is not zero and matrix is not degenerate*/
int validate_inversion(matrix*m1, matrix_utils*p_struct);

/*checks if file is empty*/
int validate_file_isEmpty(FILE *file);

#endif
