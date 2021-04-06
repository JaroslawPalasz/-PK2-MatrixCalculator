#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "matrix_struct.h"
#include "menu.h"
#include "utils.h"
#include "io.h"
#include "validate.h"
#include <string.h>

void main_menu(matrix*matrix_array, matrix_utils*p_struct)
{
	char c_matrix_number[100];
	while (0 < 1)
	{
		printf("1 - viewing matrices\n2 - operation choice\n3 - view statistics\n4 - exit program\n");
		scanf("%s", c_matrix_number);
		while ((getchar()) != '\n');
		if (strcmp(c_matrix_number, "1") == 0)
		{
			view_choice(matrix_array, p_struct);
			break;
		}
		if (strcmp(c_matrix_number, "2") == 0)
		{
			operation_choice(matrix_array, p_struct, 0, 0);
			break;
		}
		if (strcmp(c_matrix_number, "3") == 0)
		{
			show_statistics(matrix_array, p_struct);
			break;
		}
		if (strcmp(c_matrix_number, "4") == 0)
		{
			free_all(matrix_array, p_struct);
			exit(1);
		}
		else
		{
			printf("Invalid input, try again.\n");
		}
	}
}

void view_choice(matrix*matrix_array, matrix_utils*p_struct)
{

	char c_matrix_number[100];
	int number = 0;
	while (0 < 1)
	{
		number = 0;
		printf("\"a\" - view all matrices\n\"b\" - go back to main menu\nOr enter matrix number to view that matrix\n");
		int edit = 0;
		scanf("%s", c_matrix_number);
		while ((getchar()) != '\n');
		if (strcmp(c_matrix_number, "a") == 0)
		{
			print_all_matrices(matrix_array, p_struct);
			edit = 1;
		}
		else if (strcmp(c_matrix_number, "b") == 0)
		{
			main_menu(matrix_array, p_struct);
			break;
		}
		else if (check_if_number(c_matrix_number) != 1)
		{
			printf("Wrong number, try again.\n");
		}
		else if (check_if_number(c_matrix_number) == 1)
		{
			number = number_from_char_array(c_matrix_number, 0, '\0');
			if (number > 0 && number <= p_struct->matrix_count)
			{
				print_matrix(&matrix_array[number - 1]);
				edit = 1;
			}
			else
			{
				printf("There is no matrix with such number, try again.\n");
				edit = 0;
			}
		}
		if (edit == 1)
		{
			while (0 < 1)
			{
				printf("enter the number of matrix you want to edit, press \"o\" to go to operation choice\nOr press \"b\" to go back to viewing matrices\n");
				scanf("%s", c_matrix_number);
				while ((getchar()) != '\n');
				if (strcmp(c_matrix_number, "o") == 0)
				{
					operation_choice(matrix_array, p_struct, 0, 0);
					break;
				}
				if (strcmp(c_matrix_number, "b") == 0)
				{
					break;
				}
				if (check_if_number(c_matrix_number) == 1)
				{
					number = number_from_char_array(c_matrix_number, 0, '\0');
					if ((number > 0) && (number <= p_struct->matrix_count))
					{
						printf("editing matrix [%d].\n", number);
						edit_matrix(&matrix_array[number - 1], p_struct);
					}
					else
					{
						printf("Wrong number, try again.\n");
					}
				}
				if (check_if_number(c_matrix_number) != 1)
				{
					printf("Invalid input, try again.\n");
				}
			}
		}
	}

}

void operation_choice(matrix*matrix_array, matrix_utils*p_struct, int matrix_number1, int matrix_number2)
{
	char c_choice[1000];
	char choice;
	int operation_completed = 0;
	while (0 < 1)
	{
		printf("choose operations:\n\"+\" for matrix addition\n\"-\" for matrix substraction\n"
			"\"*\" for matrix multiplication\n\"T\" for matrix transposition\n\"D\" for calculating matrix determinant\n"
			"\"I\" for finding inverse matrix\n""Or press 'b' to go back to menu\n");
		scanf("%s", c_choice);
		choice = c_choice[0];
		while ((getchar()) != '\n');

		int number_array[2] = { 0, 0 };
		if (matrix_number1 || matrix_number2)
		{
			number_array[0] = matrix_number1;
			number_array[1] = matrix_number2;
		}
		if (strcmp(c_choice, "b") == 0)
		{
			main_menu(matrix_array, p_struct);
			break;
		}
		if (strcmp(c_choice, "+") == 0 || strcmp(c_choice, "-") == 0 || strcmp(c_choice, "*") == 0)
		{
			if (matrix_number1 == 0 || matrix_number2 == 0)
			{
				while (0 < 1)
				{
					number_array[0] = 0;
					number_array[1] = 0;
					for (int numbers = 0; numbers < 2; numbers++)
					{
						printf("choose your matrices or press \"b\" to choose another operation\nMatrix %d :\n", numbers + 1);
						scanf("%s", c_choice);
						while ((getchar()) != '\n');
						if (strcmp(c_choice, "b") == 0)
						{
							operation_choice(matrix_array, p_struct, matrix_number1, matrix_number2);
							break;
						}
						if (check_if_number(c_choice))
						{
							number_array[numbers] = number_from_char_array(c_choice, 0, '\0');
						}
					}
					if ((number_array[0] > 0 && number_array[0] <= p_struct->matrix_count)
						&& (number_array[1] > 0 && number_array[1] <= p_struct->matrix_count))
					{
						operation_completed = execute(&matrix_array[number_array[0] - 1], &matrix_array[number_array[1] - 1], choice, p_struct);
						break;
					}
					else {
						printf("There is no matrix with such number, try again\n");
					}
				}
			}

		}
		if (strcmp(c_choice, "T") == 0 || strcmp(c_choice, "D") == 0 || strcmp(c_choice, "I") == 0)
		{
			while (0 < 1)
			{
				number_array[0] = 0;
				printf("choose your matrix\n");
				scanf("%s", c_choice);
				while ((getchar()) != '\n');
				if (strcmp(c_choice, "b") == 0)
				{
					break;
				}
				if (check_if_number(c_choice))
				{
					number_array[0] = number_from_char_array(c_choice, 0, '\0');
				}
				if (number_array[0] > 0 && number_array[0] <= p_struct->matrix_count)
				{
					operation_completed = execute(&matrix_array[number_array[0] - 1], NULL, choice, p_struct);
					break;
				}
				else
				{
					printf("There is no matrix with such number, try again\n");
				}
			}
		}
		if (operation_completed == 0)
		{
			printf("Chosen operation did not succeed.\n");
		}
	}
}

void show_statistics(matrix*matrix_array, matrix_utils*p_struct)
{
	char c_choice[100];
	while (0 < 1)
	{
		printf("1 - show average times for different operations\n"
			"\"b\" - go back to main menu\n");
		scanf("%s", c_choice);
		while ((getchar()) != '\n');
		if (strcmp(c_choice, "b") == 0)
		{
			main_menu(matrix_array, p_struct);
			break;
		}
		if (strcmp(c_choice, "1") == 0)
		{
			while (0 < 1)
			{
				printf("select operation:\n\"+\"\n\"-\"\n\"*\"\n\"T\"\n\"D\"\n\"I\"\n");
				scanf("%s", c_choice);
				while ((getchar()) != '\n');
				if (strcmp(c_choice, "+") == 0 || strcmp(c_choice, "-") == 0 || strcmp(c_choice, "*") == 0 ||
					strcmp(c_choice, "T") == 0 || strcmp(c_choice, "D") == 0 || strcmp(c_choice, "I") == 0)
				{
					double values[3] = { 0, 0, 0 };
					FILE*p_file = fopen("operation_times.txt", "r");
					if (p_file == NULL)
						printf("No file found.\n");
					else if (validate_file_isEmpty(p_file))
						printf("File is empty.\n");
					else if (check_for_operation(p_file, c_choice[0]) == 1)
					{
						average_times(p_file, c_choice[0], values);
						int operations = (int)values[2];
						printf("Average times for chosen operation:\n"
							"My functions - %10.10f [ms]\nGNU functions - %10.10f [ms]\n"
							"Number of operations - %d\n", values[0], values[1], operations);
					}
					else
					{
						printf("There is none such operation completed.\n");
					}
					break;
				}
			}
		}
		else
		{
			printf("Invalid input, try again\n");
		}
	}
}




