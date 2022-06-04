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
        
    matrix = (int **) malloc(NUM_STATES * sizeof(int*));

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
    FILE *csv = open_file(file_name, 'r'); 

    read_matrix_csv_file(csv, matrix);   

    fclose(csv);
}


void read_matrix_csv_file(FILE *csv, int **matrix)
{
    //Consider the file already opened

    //Control variables
    int value, row = 0, col = 0;
    char trash;

    //Reading the transition matrix from a csv file
    for(row = 0; row < NUM_STATES; row++)
        for(col = 0; col < VALID_CHARACTERS; col++)
        {
            //Read the integer
            fscanf(csv, "%d", &value);

            //Read the comma
            fscanf(csv, "%c",&trash);

            //Add to the matrix
            matrix[row][col] = value;
        }
}