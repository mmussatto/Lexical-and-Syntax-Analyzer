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
int** create_matrix();

/**
 * @brief deallocate the matrix
 * 
 * @param matrix 
 */
void free_matrix(int **matrix);

/**
 * @brief Adds the states transitions to the matrix
 * 
 * @param matrix 
 */
void populate_transition_matrix(int **matrix);

void fill_matrix_rows(int **matrix, int line, int start, int end, int value);


token get_token(FILE* program, int **transition_matrix, state *vec_state);





/*

4 colunas
5 linhas 

   +   -  *  / 
q0 q1 q2 q3 q4           if < 9
q1 -  -  -  -
q2 -  -1  -1  -1
q3 -  -  -  -
q4 -  -  -  - 

estado atual --> 

switch(s)
    case q2: return -, simbolo_menos

    default:
        proximo_estado

    :  =  outro
q0  q1 -  -
q1  - q2  q3
q2 -  -   -
q3 -  -   -



*/