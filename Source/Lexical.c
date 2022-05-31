#include "Lexical.h"


int** CreateMatrix()
{
    int **matrix, i, j;
        
    matrix = (int **) malloc(ROWS * sizeof(int*));

    for(i = 0; i < ROWS; i++)
        matrix[i] = (int *) malloc(COLUMNS * sizeof(int));

    //Populate Matrix with invalid character
    for(i = 0; i < ROWS; i++)
        for(j = 0; j < COLUMNS; j++)
            matrix[i][j] = '-';

    return matrix;
}

void FreeMatrix(int **matrix)
{
    int i;
    
    for(i = 0; i < ROWS; i++)
        free(matrix[i]);
    
    free(matrix); 
}

void PopulateMatrix(int **matrix){

}