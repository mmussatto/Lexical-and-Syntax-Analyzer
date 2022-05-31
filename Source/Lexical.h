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
#include "file.h"

#define COLUMNS 4   //possible valid characters
#define ROWS 5      //number of states

typedef struct
{
    char* name; 
    char* type;
} token;

typedef struct
{
    bool final ; 
    token s_token;
} state;

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

void populate_matrix(int **matrix);


state* create_state_vector();

void populate_vector(state *vec_state);

void free_vector(state *vec_state);

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