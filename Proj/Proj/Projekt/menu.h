#ifndef MENU_H
#define MENU_H
#include "matrix_struct.h"
#include "utils.h"

/*a "general menu", prints possible options (go to other menus->view, operation choice, statistics, exit) and reads user input*/
void main_menu(matrix*matrix_array, matrix_utils*p_struct);

/*"view menu", allows user to see different matrices or go back to the main menu*/
void view_choice(matrix*matrix_array, matrix_utils*p_struct);

/*function for choosing different mathematical operations on matrices*/
void operation_choice(matrix*matrix_array, matrix_utils*p_struct, int matrix_number1, int matrix_number2);

/*function prints statistics for completed operations*/
void show_statistics(matrix*matrix_array, matrix_utils*p_struct);

#endif