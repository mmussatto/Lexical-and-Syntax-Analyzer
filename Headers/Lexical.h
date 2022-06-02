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
 
#pragma once
 
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "file.h"
#include "error.h"
#include "states_info.h"

#define COLUMNS 128   //possible valid characters
#define ROWS 21      //number of states

#define NUM_ERRORS 3


typedef struct 
{
    token* tokens;
    int size;
} vec_token;


/**
 * @brief Create a ROWSxCOLUMNS matrix populated with the invalid
 *  chareacter '-'
 * 
 * @return int** - matrix created
 */
int** create_transition_matrix();


/**
 * @brief deallocate the matrix
 * 
 * @param matrix 
 */
void free_transition_matrix(int **matrix);


/**
 * @brief Adds the states transitions to the matrix
 * 
 * @param matrix 
 */
void populate_transition_matrix(int **matrix);


/**
 * @brief useful function to fiil an entire row of a matrix with a value. This
 * function is used by the populate_transistion_matrix.
 * 
 * @param matrix 
 * @param row      -  row to be filled
 * @param start     - start column 
 * @param end       - end column
 * @param value     - value to be assigned
 */
void fill_matrix_rows(int **matrix, int row, int start, int end, int value);


token get_token(FILE* program, int **transition_matrix, state *vec_state);





