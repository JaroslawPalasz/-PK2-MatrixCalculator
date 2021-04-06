#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix_struct.h"
#include "operations.h"
#include "utils.h"
#include "io.h"

matrix *matrix_addition(matrix *m1, matrix *m2, matrix_utils *p_struct) {

	double **data = data_builder(m1->n_rows, m1->n_columns);    //creating data

	for (int i = 0; i < m1->n_rows; i++) {    //then filling data with values (adding matrices)
		for (int j = 0; j < m1->n_columns; j++) {
			data[i][j] = m1->data[i][j] + m2->data[i][j];
		}
	}
	return matrix_builder(m1->n_rows, m1->n_columns, data, m1->matrix_id);	//creating matrix and connecting everything
}

matrix *matrix_substraction(matrix *m1, matrix *m2, matrix_utils *p_struct) {
	double **data = data_builder(m1->n_rows, m1->n_columns);    //same as matrix_addition
	for (int i = 0; i < m1->n_rows; i++) {    //then filling data with values (substracting matrices)
		for (int j = 0; j < m1->n_columns; j++) {
			data[i][j] = m1->data[i][j] - m2->data[i][j];
		}
	}
	return matrix_builder(m1->n_rows, m1->n_columns, data, m1->matrix_id);
}

matrix *matrix_multiplication(matrix *m1, matrix *m2, matrix_utils *p_struct) {
	//C(m, n) = A(m, k) * B(k, n)
	double **data = data_builder(m1->n_rows, m2->n_columns);
	double sum = 0;    //operation (multiplying)

	for (int i = 0; i < m1->n_rows; i++) {
		for (int j = 0; j < m2->n_columns; j++) {
			sum = 0;
			for (int k = 0; k < m1->n_columns; k++)
				sum += (m1->data[i][k]) * (m2->data[k][j]);
			data[i][j] = sum;
		}
	}
	return matrix_builder(m1->n_rows, m2->n_columns, data, m1->matrix_id);
}

matrix *matrix_transposition(matrix *m1, matrix_utils *p_struct) {
	if (m1->n_columns == m1->n_rows) {
		return transpose_matrix_square(m1, p_struct);
	}
	else
		return transpose_matrix_non_square(m1, p_struct);
}

matrix *transpose_matrix_square(matrix *m1, matrix_utils *p_struct) {
	matrix *transposed = matrix_builder(m1->n_columns, m1->n_rows, m1->data, m1->matrix_id);
	//transposing

	for (int i = 0; i < m1->n_columns - 1; i++) {
		for (int j = i + 1; j < m1->n_columns; j++) {
			double temp = transposed->data[i][j];
			transposed->data[i][j] = transposed->data[j][i];
			transposed->data[j][i] = temp;
		}
	}
	return transposed;
}

matrix *transpose_matrix_non_square(matrix *m1, matrix_utils *p_struct) {
	double **data = data_builder(m1->n_columns, m1->n_rows);
	//transposing

	for (int i = 0; i < m1->n_rows; i++)
		for (int j = 0; j < m1->n_columns; j++) {
			data[j][i] = m1->data[i][j];
		}
	return matrix_builder(m1->n_columns, m1->n_rows, data, m1->matrix_id);
}

long double matrix_determinant(matrix *m1, matrix_utils *p_struct) {
	long double D = 0;
	if (check_same_cols(m1, 0, 0) == 1)
		return 0;
	if (check_same_rows(m1, 0, 0) == 1)
		return 0;
	if (check_rows_cols_for_0(m1) == 1)
		return 0;
	if (m1->n_columns == 1 && m1->n_rows == 1) {
		D = determinant_matrix_1x1(m1, p_struct);
		return D;
	}
	else if (m1->n_columns == 2 && m1->n_rows == 2) {
		D = determinant_matrix_2x2(m1, p_struct);
		return D;
	}
	else if (m1->n_columns == 3 && m1->n_rows == 3) {
		D = determinant_matrix_3x3(m1, p_struct);
		return D;
	}
	else if (m1->n_columns > 3 && m1->n_rows > 3) {
		D = determinant_matrix_NxN(m1, p_struct);
		return D;
	}
}

double determinant_matrix_1x1(matrix *m1, matrix_utils *p_struct) {
	double D = m1->data[0][0];
	return D;
}

double determinant_matrix_2x2(matrix *m1, matrix_utils *p_struct) {
	double D = (m1->data[0][0] * m1->data[1][1] - m1->data[0][1] * m1->data[1][0]);
	return D;
}

double determinant_matrix_3x3(matrix *m1, matrix_utils *p_struct) {
	double D = (m1->data[0][0] * m1->data[1][1] * m1->data[2][2] + m1->data[0][1] * m1->data[1][2] * m1->data[2][0] +
		m1->data[0][2] *
		m1->data[1][0] * m1->data[2][1] - m1->data[0][2] * m1->data[1][1] * m1->data[2][0] -
		m1->data[0][0] * m1->data[1][2] *
		m1->data[2][1] - m1->data[0][1] * m1->data[1][0] * m1->data[2][2]);
	return D;
}


long double determinant_matrix_NxN(matrix *m1, matrix_utils *p_struct)
{
	int rows = m1->n_rows;
	int cols = rows;
	int row, column, sub_row, sub_col, one_swap, temp_row, temp_col, sub_sub_col, sub_sub_row;
	int swaps = 0;
	double x;
	double temp;
	//using Doolittle's v of LU decomposition - with switching rows
	double **data_lower = data_builder(rows, cols);
	double **new_data = data_builder(rows, cols);	//representing upper triangular matrix
	//creating lower and triangular matrix template
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
		{
			new_data[r][c] = m1->data[r][c];
			if (r == c)
			{
				data_lower[r][c] = 1;
			}
			else
			{
				data_lower[r][c] = 0;
			}
		}
	}
	matrix*new_matrix = matrix_builder(rows, cols, new_data, 0);

	//L - lower
	//U - upper

	for (row = 0; row < rows; row++)
	{
		for (column = 0; column < cols; column++)
		{
			if (row == column)
			{
				if (new_matrix->data[row][column] == 0) //searching downwards for not empty value and switching rows
				{
					for (sub_row = column; sub_row < rows; sub_row++)
					{
						if (new_matrix->data[sub_row][column] != 0)
						{
							one_swap = 1;
							temp_row = sub_row;
							temp_col = column;
							swaps++;
							break;
							//swap rows
						}
					}
					if (one_swap == 1)	//swapping rows, no need to swap data_lower rows as determinant of it will be 1
					{
						for (sub_sub_col = 0; sub_sub_col < cols; sub_sub_col++)
						{
							temp = new_matrix->data[temp_row][sub_sub_col];
							new_matrix->data[temp_row][sub_sub_col] = new_matrix->data[row][sub_sub_col];
							new_matrix->data[row][sub_sub_col] = temp;
						}
						one_swap = 0;
					}
				}
				if (new_matrix->data[row][column] != 0)  //not multiplying whole row, just one value
				{
					temp_col = column;
					temp_row = row;
					for (sub_row = row + 1; sub_row < rows; sub_row++)   // searching downwards rows for non- 0
					{
						if (new_matrix->data[sub_row][column] == 0)
						{
							data_lower[sub_row][column] = 0;
						}
						if (new_matrix->data[sub_row][column] != 0)
						{
							x = new_matrix->data[sub_row][column] / new_matrix->data[row][column];
							data_lower[sub_row][column] = -x;
							temp_col = column;
							for (sub_sub_col = column; sub_sub_col < cols; sub_sub_col++)
							{
								new_matrix->data[sub_row][sub_sub_col] -= (x*new_matrix->data[temp_row][temp_col]);
								temp_col++;
							}
						}
					}
				}
			}
		}
	}
	if (rows < 100)
	{
		printf("L matrix:\n");
		for (int r = 0; r < rows; r++)
		{
			for (int c = 0; c < cols; c++)
			{
				printf("%f     ", data_lower[r][c]);
			}
			printf("\n");
		}
		printf("\nU matrix:\n");
		print_matrix(new_matrix);
	}

	//determinant of matrix is: det(A)=det(L)*det(U), S is number of row exchanges in the decomposition
	//whereas determinants of triangular ones (L and U) are products of their diagonal entries
	long double det_U = 1;
	double det_L = 1;
	for (int i = 0; i < rows; i++)
	{
		det_U = det_U * new_matrix->data[i][i];
	}
	long double D = -1 *det_U * det_L;
	free_data(data_lower, rows);
	free_data(new_data, rows);
	free_data(new_matrix->data, rows);

	return D;
}

matrix *inverse_matrix(matrix *m1, matrix_utils *p_struct)
{
	int row = 0;
	int column = 0;

	int rows = m1->n_rows;
	int cols = m1->n_columns * 2;
	int new_cols = m1->n_columns;

	double temp = 0;
	int sub_col = 0;
	int sub_row = 0;
	int sub_sub_row = 0;
	int sub_sub_col = 0;
	int one_swap = 0;
	int temp_row = 0;
	int temp_col = 0;

	//create matrix ready for gauss-jordan operations
	double **data_new_matrix = data_builder(rows, cols);
	matrix* new_matrix = matrix_builder(rows, cols, data_new_matrix, m1->matrix_id);

	create_gauss_jordan_data_template(m1, new_matrix, rows, cols);

	//create identity matrix and filling values in new matrix
	double **data_new_identity_matrix = data_builder(rows, new_cols);
	matrix* identity_matrix = matrix_builder(rows, new_cols, data_new_identity_matrix, m1->matrix_id);

	create_gauss_jordan_data(rows, new_cols, new_matrix, identity_matrix);

	//I now have input square matrix extended with identity one

	lower_triangular_operations_data(rows, cols, new_matrix);

	upper_triangular_operations_data(rows, cols, new_matrix);

	for (row = 0, sub_row = 0; row < rows, sub_row < rows; row++, sub_row++)
	{
		for (column = 0, sub_col = rows; column < new_cols, sub_col < cols; column++, sub_col++)
		{
			identity_matrix->data[row][column] = new_matrix->data[sub_row][sub_col];
		}
	}
	free_data(data_new_matrix, rows);
	free_data(data_new_identity_matrix, rows);

	return identity_matrix;
}

void create_gauss_jordan_data_template(matrix *m1, matrix *new_matrix, int rows, int cols)
{
	//create matrix ready for gauss-jordan operations(input m1 matrix augmented by same size- one, right now with random values)

	int row = 0;
	int column = 0;

	for (row = 0; row < rows; row++)
	{
		for (column = 0; column < cols; column++)
		{
			new_matrix->data[row][column] = m1->data[row][column];
		}
	}

}

void create_gauss_jordan_data(int rows, int cols, matrix *new_matrix, matrix *identity_matrix)
{
	//creating identity matrix and filling values in gauss-jordan one

	int row = 0;
	int column = 0;


	for (row = 0; row < rows; row++)
	{
		for (column = 0; column < cols; column++)
		{
			if (row == column)
			{
				identity_matrix->data[row][column] = 1;
				new_matrix->data[row][column + cols] = identity_matrix->data[row][column];
			}
			else
			{
				identity_matrix->data[row][column] = 0;
				new_matrix->data[row][column + cols] = identity_matrix->data[row][column];
			}
		}
	}
}

void lower_triangular_operations_data(int rows, int cols, matrix *new_matrix)
{
	int row = 0;
	int column = 0;

	int new_cols = cols / 2;

	double temp = 0;
	int sub_col = 0;
	int sub_row = 0;
	int sub_sub_row = 0;
	int sub_sub_col = 0;
	int one_swap = 0;
	int temp_row = 0;
	int temp_col = 0;

	for (row = 0; row < rows; row++)
	{
		for (column = 0; column < cols; column++)
		{
			if (row == column)
			{
				if (new_matrix->data[row][column] == 0) //searching downwards for not empty value and switching rows
				{
					for (sub_row = column; sub_row < rows; sub_row++)
					{
						if (new_matrix->data[sub_row][column] != 0)
						{
							one_swap = 1;
							temp_row = sub_row;
							temp_col = column;
							break;
							//swap rows
						}

					}
					if (one_swap == 1)
					{
						for (sub_sub_col = 0; sub_sub_col < cols; sub_sub_col++)
						{
							temp = new_matrix->data[temp_row][sub_sub_col];
							new_matrix->data[temp_row][sub_sub_col] = new_matrix->data[row][sub_sub_col];
							new_matrix->data[row][sub_sub_col] = temp;
						}
						one_swap = 0;
					}
				}
				if (new_matrix->data[row][column] != 1 && new_matrix->data[row][column] != 0)  //multiplying whole row so that [r][c], r=c, can be 1
				{
					temp = 1 / new_matrix->data[row][column];
					for (sub_col = row; sub_col < cols; sub_col++)
					{
						new_matrix->data[row][sub_col] = new_matrix->data[row][sub_col] * temp;
					}
				}

				if (new_matrix->data[row][column] == 1)
				{
					temp_col = column;
					temp_row = row;
					for (sub_row = row + 1; sub_row < rows; sub_row++)   //is 1, searching downwards rows for non- 0
					{
						if (new_matrix->data[sub_row][column] != 0)
						{
							temp = new_matrix->data[sub_row][column];
							temp_col = column;
							for (sub_sub_col = column; sub_sub_col < cols; sub_sub_col++)
							{
								new_matrix->data[sub_row][sub_sub_col] -= (temp*new_matrix->data[temp_row][temp_col]);
								temp_col++;
							}
						}
					}
				}
			}
		}
	}
}

void upper_triangular_operations_data(int rows, int cols, matrix *new_matrix)
{
	int row = 0;
	int column = 0;

	int new_cols = cols / 2;

	double temp = 0;
	int sub_col = 0;
	int sub_row = 0;
	int sub_sub_row = 0;
	int sub_sub_col = 0;
	int one_swap = 0;
	int temp_row = 0;
	int temp_col = 0;

	for (row = rows - 1; row >= 0; row--)
	{
		for (column = 0; column < cols; column++)
		{
			if (row == column)
			{
				for (sub_row = row - 1; sub_row >= 0; sub_row--)
				{
					if (new_matrix->data[sub_row][column] != 0)
					{
						temp = new_matrix->data[sub_row][column];
						temp_col = column;
						temp_row = row;
						for (sub_sub_col = column; sub_sub_col < cols; sub_sub_col++)
						{
							new_matrix->data[sub_row][sub_sub_col] -= (temp*new_matrix->data[temp_row][temp_col]);
							temp_col++;
						}
					}
				}
			}
		}
	}
}


