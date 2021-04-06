#ifndef IO_H
#define IO_H
#include <stdio.h>
#include <stdlib.h>
#include "matrix_struct.h"
#include "utils.h"

/*reads matrices.txt and returns pointer to start of the Dyn array of matrix structs*/
matrix *read_matrix(FILE*p_file, matrix_utils*p_struct);

/*function prints certain matrix requested by user*/
void print_matrix(matrix* m);

/*prints all of the matrices*/
void print_all_matrices(matrix*matrix_array, matrix_utils*p_struct);

/*writes completed operations with matrix numbers and completion times*/
void write_all_operations(matrix*m1, matrix*m2, char choice, matrix_utils*p_struct);

/*checks how many operations were completed*/
int check_operation_count();

/*checks if given operation has been executed*/
int check_for_operation(FILE*p_file, char choice);

/*counts and returns average complete times of operation in form of array*/
void average_times(FILE*p_file, char choice, double values[]);

#endif