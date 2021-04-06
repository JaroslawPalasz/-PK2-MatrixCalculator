#define _CRT_SECURE_NO_WARNING

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "matrix_struct.h"
#include "validate.h"
#include "utils.h"
#include "operations.h"

int validate_addition_substraction(matrix*m1, matrix*m2)
{
	if (m1->n_rows == m2->n_rows && m1->n_columns == m2->n_columns)
	{
		return 1;
	}
	else
		return 0;
}

int validate_multiplication(matrix*m1, matrix*m2)
{
	if (m1->n_columns == m2->n_rows)
	{
		return 1;
	}
	else
		return 0;
}

int validate_determinant(matrix*m1)
{
	if (m1->n_rows == m1->n_columns)
		return 1;
	else
		return 0;
}

int validate_inversion(matrix*m1, matrix_utils*p_struct)
{
	if (validate_determinant(m1))
	{
		if (matrix_determinant(m1, p_struct) != 0)
		{
			return 1;
		}
	}
	else
		return 0;
}

int validate_file_isEmpty(FILE *file) {
	long savedOffset = ftell(file);
	fseek(file, 0, SEEK_END);

	if (ftell(file) == 0) {
		return 1;
	}

	fseek(file, savedOffset, SEEK_SET);
	return 0;
}