#ifndef MATRIX_H
#define MATRIX_H

/*matrix struct, holding its dimensions, id and data*/
typedef struct {
	int matrix_id;
	int n_rows;
	int n_columns;
	int** data; ////pointer to an array of pointers(number of rows) each pointing to an array of ints (number of cols)
} matrix;


#endif