#pragma once
 
#include <stdbool.h>
#include <stdlib.h>

#define COLUMNS 127 
#define ROWS 10

/**
 * @brief Create a ROWSxCOLUMNS matrix populated with the invalid
 *  chareacter '-'
 * 
 * @return int** - matrix created
 */
int** CreateMatrix();

/**
 * @brief deallocate the matrix
 * 
 * @param matrix 
 */
void FreeMatrix(int **matrix);

void PopulateMatrix(int **matrix);