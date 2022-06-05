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

#include "Headers/matrix.h"


int** create_transition_matrix()
{
    int **matrix, i, j;

    //Allocate matrix first column   
    matrix = (int **) malloc(NUM_STATES * sizeof(int*));

    //Allocate matrix rows
    for(i = 0; i < NUM_STATES; i++)
        matrix[i] = (int *) malloc(VALID_CHARACTERS * sizeof(int));

    //Populate Matrix with invalid character
    for(i = 0; i < NUM_STATES; i++)
        for(j = 0; j < VALID_CHARACTERS; j++)
            matrix[i][j] = -1;

    return matrix;
}


void free_transition_matrix(int **matrix)
{
    int i;

    for(i = 0; i < NUM_STATES; i++)
        free(matrix[i]);
    
    free(matrix); 
}


void populate_transition_matrix(int **matrix, char* file_name)
{
    FILE *tsv = open_file(file_name, 'r'); 

    read_matrix_tsv_file(tsv, matrix);   

    fclose(tsv);
}


void read_matrix_tsv_file(FILE *tsv, int **matrix)
{
    //Consider the file already opened

    //Control variables
    int value, row = 0, col = 0;

    //Reading the transition matrix from a tsv file
    for(row = 0; row < NUM_STATES; row++)
        for(col = 0; col < VALID_CHARACTERS; col++)
        {
            //Read the integer
            fscanf(tsv, "%d", &value);

            //Add to the matrix
            matrix[row][col] = value;
        }
}