#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include "matrix_struct.h"
#include "utils.h"
#include "io.h"
#include "operations.h"
#include "validate.h"


/*function creating data template*/
double**data_builder(int n_rows, int n_columns) {
	double **data = malloc(n_rows * sizeof(double *));
	for (int i = 0; i < n_rows; i++)
		data[i] = malloc(n_columns * sizeof(double));
	return data;
}

/*function building matrix template*/
matrix *matrix_builder(int n_rows, int n_columns, double **data, int matrix_id) {
	matrix *p_matrix = malloc(sizeof(matrix));
	p_matrix->n_rows = n_rows;
	p_matrix->n_columns = n_columns;
	p_matrix->matrix_id = matrix_id;

	double **result_data = malloc(p_matrix->n_rows * sizeof(double *));
	//pointer to an array of pointers(number of rows) each pointing to an array of doubles (number of cols)
	for (int i = 0; i < p_matrix->n_rows; i++)
		result_data[i] = malloc(p_matrix->n_columns * sizeof(double));

	p_matrix->data = result_data;

	for (int i = 0; i < n_rows; i++) {
		for (int j = 0; j < n_columns; j++) {
			p_matrix->data[i][j] = data[i][j];
		}
	}

	return p_matrix;
}

matrix*make_matrix_struct(matrix*p_matrix, matrix*p_matrix_array, matrix_utils*p_struct)
{
	p_matrix_array = realloc(p_matrix_array, p_struct->matrix_count * sizeof(matrix));
	p_matrix_array[p_struct->matrix_count - 1] = *p_matrix;
	return p_matrix_array;
}

void edit_matrix(matrix*matrix, matrix_utils*p_struct)
{
	print_matrix(matrix);
	char c_matrix_number[100];
	while (0 < 1) {
		printf("Enter row and column which you want to edit in the following format:\nROW:COLUMN\n"
			"Or press \"b\" to go back to view choice:\n");

		fgets(c_matrix_number, (sizeof(c_matrix_number) / sizeof(c_matrix_number[0])), stdin);
		int first_split = 0;
		char*delimiter = ":";

		int rows_columns[2] = { 0, 0 };
		int number = 0;

		if (c_matrix_number[0] == 'b')
		{
			break;
		}
		for (int i = 0; i < 2; i++)
		{
			if (i == 1)
			{
				delimiter = "\n";
				first_split = 1;
			}
			char * token = splitter(c_matrix_number, delimiter, first_split);
			if (token == NULL)
			{
				printf("Invalid input, try again.\n");
			}
			else
			{
				if (check_if_number(c_matrix_number))
				{
					rows_columns[i] = number_from_char_array(c_matrix_number, 0, '\0');
				}
			}
		}
		if ((rows_columns[0] > 0 && rows_columns[0] <= matrix->n_rows) && (rows_columns[1] > 0 && rows_columns[1] <= matrix->n_columns))
		{
			while (0 < 1)
			{
				printf("Enter value in [%d]row [%d]column: \nOr press \"b\" to choose another place in matrix:\n",
					rows_columns[0], rows_columns[1]);
				scanf("%s", c_matrix_number);
				while ((getchar()) != '\n');
				if (strcmp(c_matrix_number, "b") == 0)
				{
					break;
				}
				else
				{
					double d = atof(c_matrix_number);
					printf("Changing value in [%d]row [%d]column to %lf\nPress \"a\" to accept or any other input to "
						"cancel\n", rows_columns[0], rows_columns[1], d);
					scanf("%s", c_matrix_number);
					while ((getchar()) != '\n');
					if (strcmp(c_matrix_number, "a") == 0)
					{
						matrix->data[rows_columns[0] - 1][rows_columns[1] - 1] = d;
						printf("Succesfully edited [%d]row [%d]column.\n", rows_columns[0], rows_columns[1]);
						print_matrix(matrix);
						break;
					}
				}
			}
		}
		else
		{
			printf("Invalid input, try again.\n");
		}
	}
}

char * splitter(char array[], char *delimiter, int first_split)
{
	char *token = NULL;
	int len = strlen(array);

	if (first_split == 1)
	{
		token = strtok(NULL, delimiter);
	}
	else
	{
		token = strtok(array, delimiter);
	}
	char *temp = token;
	if (token != NULL)
		strcpy(array, temp);
	return token;
}

int number_from_char_array(char array[], int i, char delimiter)
{
	int number = 0;
	for (i; array[i] != delimiter; i++)
	{
		number = number * 10 + (array[i] - '0');
	}
	return number;
}

int execute(matrix*matrix1, matrix*matrix2, char choice, matrix_utils*p_struct)
{
	matrix*result = NULL;
	int operation_completed = 0;
	if (choice == '+')
	{
		if (validate_addition_substraction(matrix1, matrix2))
		{
			
			clock_t start = clock();

			result = matrix_addition(matrix1, matrix2, p_struct);

			clock_t end = clock();
			double time_taken = (end - start) / (double)CLOCKS_PER_SEC;
			p_struct->my_measured_time = time_taken;

			write_all_operations(matrix1, matrix2, '+', p_struct);
			printf("Matrix [%d] + Matrix [%d] =\n", matrix1->matrix_id, matrix2->matrix_id);
			print_matrix(result);

			operation_completed = 1;
		}
		else
			printf("Matrix [%d] and [%d] can't be added!\n", matrix1->matrix_id, matrix2->matrix_id);

	}
	else if (choice == '-')
	{
		if (validate_addition_substraction(matrix1, matrix2))
		{
			
			clock_t start = clock();

			result = matrix_substraction(matrix1, matrix2, p_struct);

			clock_t end = clock();
			double time_taken = (end - start) / (double)CLOCKS_PER_SEC;
			p_struct->my_measured_time = time_taken;

			write_all_operations(matrix1, matrix2, '-', p_struct);
			printf("Matrix [%d] - Matrix [%d] =\n", matrix1->matrix_id, matrix2->matrix_id);
			print_matrix(result);
			operation_completed = 1;
		}
		else
			printf("Matrix [%d] and [%d] can't be substracted!\n", matrix1->matrix_id, matrix2->matrix_id);
	}
	else if (choice == '*')
	{
		if (validate_multiplication(matrix1, matrix2))
		{
			
			clock_t start = clock();

			result = matrix_multiplication(matrix1, matrix2, p_struct);

			clock_t end = clock();
			double time_taken = (end - start) / (double)CLOCKS_PER_SEC;
			p_struct->my_measured_time = time_taken;

			write_all_operations(matrix1, matrix2, '*', p_struct);
			printf("Matrix [%d] * Matrix [%d] =\n", matrix1->matrix_id, matrix2->matrix_id);
			print_matrix(result);
			operation_completed = 1;
		}
		else
			printf("Matrix [%d] and [%d] can't be multiplied!\n", matrix1->matrix_id, matrix2->matrix_id);
	}
	else if (choice == 'T')
	{
		
		clock_t start = clock();

		result = matrix_transposition(matrix1, p_struct);

		clock_t end = clock();
		double time_taken = (end - start) / (double)CLOCKS_PER_SEC;
		p_struct->my_measured_time = time_taken;

		write_all_operations(matrix1, NULL, 'T', p_struct);
		printf("Transposed matrix [%d]:\n", matrix1->matrix_id);
		print_matrix(result);
		operation_completed = 1;
	}
	else if (choice == 'D')
	{
		if (validate_determinant(matrix1))
		{
			
			clock_t start = clock();

			long double D = matrix_determinant(matrix1, p_struct);

			clock_t end = clock();
			double time_taken = (end - start) / (double)CLOCKS_PER_SEC;
			p_struct->my_measured_time = time_taken;

			/*if (/*isnan(D) != 0 || isinf(D) != 0)*/
			write_all_operations(matrix1, NULL, 'D', p_struct);
			printf("Determinant of matrix [%d] = %Lf\n", matrix1->matrix_id, D);
			operation_completed = 1;
		}
		else
		{
			printf("Matrix [%d] is not square!\n", matrix1->matrix_id);
		}
	}
	else if (choice == 'I')
	{
		if (validate_inversion(matrix1, p_struct))
		{
			
			clock_t start = clock();

			result = inverse_matrix(matrix1, p_struct);

			clock_t end = clock();
			double time_taken = (end - start) / (double)CLOCKS_PER_SEC;
			p_struct->my_measured_time = time_taken;

			write_all_operations(matrix1, NULL, 'I', p_struct);
			if (matrix1->n_rows < 100)
			{
				printf("Inversed matrix [%d]:\n", matrix1->matrix_id);
				print_matrix(result);
			}
			operation_completed = 1;
		}
		else
			printf("Matrix [%d] can't be inversed!\n", matrix1->matrix_id);
	}
	if (result != NULL)
		free_data(result->data, result->n_rows);
	return operation_completed;
}

int check_if_number(char*c_array)
{
	int len = strlen(c_array);
	for (int i = 0; i < len; i++)
	{
		if (!isdigit(c_array[i]))
		{
			return 0;
		}
	}
	return 1;
}



int check_same_cols(matrix *m1, int first_column, int D_is_zero)
{
	if (first_column == m1->n_columns || first_column == m1->n_columns - 1)
		return D_is_zero;
	int i = first_column;
	int row_data_is_same = 0;
	for (i; i < m1->n_columns; i++)
	{
		for (int l = 0; l < m1->n_rows; l++)
		{
			if (i + 1 >= m1->n_columns)
				break;
			if (m1->data[l][i + 1] == m1->data[l][i])
			{
				row_data_is_same++;

			}
			if (l == (m1->n_rows - 1))
			{
				if (row_data_is_same == m1->n_rows)
				{
					D_is_zero = 1;
					return D_is_zero;
				}
				else
				{
					D_is_zero = 0;
					row_data_is_same = 0;
				}
			}
		}
	}
	check_same_cols(m1, first_column + 1, D_is_zero);
}

int check_same_rows(matrix *m1, int first_row, int D_is_zero)
{
	if (first_row == m1->n_rows || first_row == m1->n_rows - 1)
		return D_is_zero;
	int i = first_row;
	int column_data_is_same = 0;
	for (i; i < m1->n_rows; i++)
	{
		for (int l = 0; l < m1->n_columns; l++)
		{
			if (i + 1 >= m1->n_rows)
				break;
			if (m1->data[i + 1][l] == m1->data[i][l])
			{
				column_data_is_same++;

			}
			if (l == (m1->n_columns - 1))
			{
				if (column_data_is_same == m1->n_columns)
				{
					D_is_zero = 1;
					return D_is_zero;
				}
				else
				{
					D_is_zero = 0;
					column_data_is_same = 0;
				}
			}
		}
	}
	check_same_rows(m1, first_row + 1, D_is_zero);
}

int check_rows_cols_for_0(matrix *m1)
{
	int col_is_zero = 0;
	int row_is_zero = 0;
	for (int row = 0; row < m1->n_rows; row++)
	{
		for (int col = 0; col < m1->n_columns; col++)
		{
			if (m1->data[row][col] == 0)
			{
				col_is_zero++;
				if (col == (m1->n_columns - 1))
				{
					if (col_is_zero == m1->n_rows)
						return 1;
					else
						col_is_zero = 0;
				}
			}
		}
	}
	for (int col = 0; col < m1->n_columns; col++)
	{
		for (int row = 0; row < m1->n_rows; row++)
		{
			if (m1->data[row][col] == 0)
			{
				row_is_zero++;
				if (row == (m1->n_rows - 1))
				{
					if (row_is_zero == m1->n_columns)
						return 1;
					else
						row_is_zero = 0;
				}
			}
		}
	}
	return 0;
}

void free_all(matrix*matrix_array, matrix_utils*p_struct)
{
	for (int matrix = 0; matrix < p_struct->matrix_count; matrix++)
	{
		free_data(matrix_array[matrix].data, matrix_array[matrix].n_rows);
	}
	free(matrix_array);
}

void free_data(double **data, int rows)
{
	for (int i = 0; i < rows; i++)
	{
		free((double*)data[i]);
	}
	free((double*)data);
}

matrix *big_matrix(matrix*matrix_array, matrix_utils*p_struct)
{
	//matrix*new_m = matrix_builder(rows, cols, data, matrix_id);
	//matrix_array = make_matrix_struct(new_m, matrix_array, p_struct);
	int big_rows[10] = {50, 100, 200, 255, 300, 500, 1000, 1200, 1500, 2000 };
	int i, j, k, row, col;
	int n = sizeof(big_rows) / sizeof(big_rows[0]);
	for (i = 0; i < n; i++)
	{
		double **data = data_builder(big_rows[i], big_rows[i]);
		for (row = 0; row < big_rows[i]; row++)
		{
			for (col = 0; col < big_rows[i]; col++)
			{
				data[row][col] = randfrom(-3, 3);
			}
		}
		p_struct->matrix_count++;
		matrix*new_matrix = matrix_builder(big_rows[i], big_rows[i], data, p_struct->matrix_count);
		free_data(data, big_rows[i]);
		matrix_array = make_matrix_struct(new_matrix, matrix_array, p_struct);
	}
	return matrix_array;
}

double randfrom(double min, double max)
{
	double range = (max - min);
	double div = RAND_MAX / range;
	return min + (rand() / div);
}