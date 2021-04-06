#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix_struct.h"
#include "io.h"
#include "utils.h"
#include "validate.h"

matrix*read_matrix(FILE*p_file, matrix_utils*p_struct)	//passing file pointer and pointer to struct by reference
{
	rewind(p_file);
	char temp[1000];
	int len = 0,
		result = 0,
		i = 0,
		j = 0,
		k = 0,
		rows = 0,
		cols = 0,
		ntemp = 0,
		row = 0,
		col = 0;
	int matrix_id = 0;
	matrix*matrix_array = malloc(sizeof(matrix));
	int matrix_loaded = 0;
	while (fgets(temp, sizeof temp, p_file) != NULL)
	{
		if (temp[0] == 'M'&& matrix_loaded == 0)	// M123:34x421 
		{
			result = 0;
			rows = 0;
			cols = 0;
			ntemp = 0;
			row = 0;
			col = 0;
			i++;
			len = strlen(temp);	// +'M'

			for (i = 1; temp[i] != ':'; i++)
			{
				result = result * 10 + (temp[i] - '0');
			}
			p_struct->matrix_count++;
			matrix_id++;
			for (j = i + 1; temp[j] != 'x'; j++)	//reading number of rows
			{
				rows = rows * 10 + (temp[j] - '0');
			}
			for (k = j + 1; temp[k] != '\n'; k++)	//and respectively, columns
			{
				cols = cols * 10 + (temp[k] - '0');
			}
			matrix_loaded = 1;	//have cols, rows
			//create data template

			double**data = data_builder(rows, cols);

			double values[1000];//
			int i = 0;
			for (int l = 0; l < rows; l++)	//reading values of matrix
			{
				for (int column = 0; column < cols; column++)
				{
					fscanf(p_file, "%lf", &values[i]);
					data[l][column] = values[i];
					i++;
				}
				row++;
			}
			matrix*new_m = matrix_builder(rows, cols, data, matrix_id);	//have matrix pointer with data
			free_data(data, rows);

			//matrix*temp_array = make_matrix_struct(new_m, matrix_array, p_struct);
			matrix_array = make_matrix_struct(new_m, matrix_array, p_struct);
			//matrix_array = temp_array;
			//free(temp_array);
			matrix_loaded = 0;
		}

	}
	fclose(p_file);
	matrix_array=big_matrix(matrix_array, p_struct);
	/*ADDING BIG MATRICES FOR CHART*/

	return matrix_array;
}

void print_matrix(matrix *m) {
	printf("M[%d] %dx%d\n", m->matrix_id, m->n_rows, m->n_columns);
	for (int row = 0; row < m->n_rows; row++) {
		for (int columns = 0; columns < m->n_columns; columns++) {
			printf("%-10lf     ", m->data[row][columns]);
		}
		printf("\n");
	}
	printf("\n");
}

void print_all_matrices(matrix*matrix_array, matrix_utils*p_struct)
{
	for (int i = 0; i < p_struct->matrix_count; i++)
	{
		print_matrix(&matrix_array[i]);
	}
}

void write_all_operations(matrix*m1, matrix*m2, char choice, matrix_utils*p_struct)
{
	FILE *f_write = fopen("operation_times.txt", "a+");

	if (f_write == NULL)
	{
		printf("Error opening file!\n");
		return;
	}
	else
	{
		if (validate_file_isEmpty(f_write))
		{
			char *ptr = "|No. Matrix [1]|";
			char *ptr2 = "|No. Matrix [2]|";
			char *ptr3 = "|Operation|";
			char *ptr4 = "|time [ms] by program funcs|";
			char *ptr5 = "|time [ms] by GNU funcs|";
			fprintf(f_write, "%27s %20s %15s %35s %30s\n", ptr, ptr2, ptr3, ptr4, ptr5);
		}
		fclose(f_write);
		p_struct->no_operations = check_operation_count();
		FILE *f_write = fopen("operation_times.txt", "a+");
		if (m2 == NULL)
		{
			fprintf(f_write, "row [%d] %10d %20c %18c %35.15f %35.15f\n", p_struct->no_operations, m1->matrix_id, 'x',
				choice, p_struct->my_measured_time, 0);
		}
		else
		{
			fprintf(f_write, "row [%d] %10d %20d %18c %35.15f %35.15f\n", p_struct->no_operations, m1->matrix_id, m2->matrix_id,
				choice, p_struct->my_measured_time, 0);
		}
	}

	fclose(f_write);
}

int check_operation_count()
{
	FILE*file = fopen("operation_times.txt", "r");
	rewind(file);
	int ch = 0;
	int lines = 0;
	while (!feof(file))
	{
		ch = fgetc(file);
		if (ch == '\n')
		{
			lines++;
		}
	}
	fclose(file);
	return lines;
}

int check_for_operation(FILE*p_file, char choice)
{
	rewind(p_file);
	char temp[1000];
	int len = strlen(temp);
	while (fgets(temp, sizeof temp, p_file) != NULL)
	{
		for (int i = 0; i < len; i++)
		{
			if (temp[i] == choice)
			{
				return 1;
			}
		}
	}
	return 0;
}

void average_times(FILE*p_file, char choice, double values[])
{
	rewind(p_file);
	char temp[1000];
	char string_arr1[30];
	char string_arr2[30];
	int len = strlen(temp);
	double my_sum = 0;
	double gnu_sum = 0;
	double average_divide = 0;
	int k = 0;
	int first_num = 0;
	int c = 0;
	while (fgets(temp, sizeof temp, p_file) != NULL)
	{
		for (int i = 0; i < len; i++)
		{
			if (temp[i] == choice)
			{
				while (!isdigit(temp[i]))
					i++;
				for (first_num = i, c = 0; temp[first_num] != ' '; first_num++, c++)
				{
					string_arr1[c] = temp[first_num];
				}
				values[0] = atof(string_arr1);
				my_sum += values[0];
				first_num++;
				while (!isdigit(temp[first_num]))
					first_num++;
				for (first_num, c = 0; temp[first_num] != '\n'; first_num++, c++)
				{
					string_arr2[c] = temp[first_num];
				}
				values[1] = atof(string_arr2);
				gnu_sum += values[1];

				average_divide++;
				break;
			}
		}
	}

	fclose(p_file);
	values[0] = my_sum / average_divide;
	values[1] = gnu_sum / average_divide;
	values[2] = average_divide;
}

