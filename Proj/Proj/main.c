#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//#include <gsl/gsl_matrix_int.h>

#include "matrix_struct.h"
#include "io.h"
#include "menu.h"
#include "operations.h"
#include "utils.h"
#include "validate.h"


int main()
{
	setbuf(stdout, 0);
	matrix_utils MU;
	MU.matrix_count = 0;
	matrix_utils *p_struct = &MU;
	FILE*p_file = fopen("matrices.txt", "r");
	if (p_file == NULL)
	{
		printf("Error opening file, closing program.\n");
		return 0;
	}
	else
	{
		matrix*matrix_array = read_matrix(p_file, p_struct);
		p_struct->no_operations = 0;
		main_menu(matrix_array, p_struct);
	}

	return 0;
}