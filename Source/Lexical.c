/*
 * **************************************************
 *                                                  *
 * SSC 0605 - Teoria da Computação e Compiladores   *
 *                                                  *
 * Autores:                                         *
 *  - Che Fan Pan                       - 11200421  *
 *  - Eduardo Cavalari Valença          - 11234381  *
 *  - Marcos Vinicius Firmino Pietrucci - 10770072  *
 *  - Murilo Mussatto                   - 11234245  *
 *                                                  *
 * São Carlos - SP                                  *
 * 2022                                             *
 *                                                  *
 * **************************************************
 */

#include "Lexical.h"


int** create_matrix()
{
    int **matrix, i, j;
        
    matrix = (int **) malloc(ROWS * sizeof(int*));

    for(i = 0; i < ROWS; i++)
        matrix[i] = (int *) malloc(COLUMNS * sizeof(int));

    //Populate Matrix with invalid character
    for(i = 0; i < ROWS; i++)
        for(j = 0; j < COLUMNS; j++)
            matrix[i][j] = -1;

    return matrix;
}

void free_matrix(int **matrix)
{
    int i;
    
    for(i = 0; i < ROWS; i++)
        free(matrix[i]);
    
    free(matrix); 
}

void populate_matrix(int **matrix)
{
    int i, j;

    for (i = 0; i < ROWS; i++)
        for (j = 0; j < COLUMNS; j++)
            if(i == 0)
                matrix[0][j] = i+1;
        
}

/*
state* create_state_vector()
{
    state* = (state*) calloc(ROWS, sizeof(state));
}*/

void populate_vector(state *v_state)
{
    int i;
    for (i = 0; i < ROWS; i++)
    {
        if(i != 0)
        {
            v_state->final = true;
        }
    }
    
}