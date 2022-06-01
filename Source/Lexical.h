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

//Store the possible tokens of the program
typedef struct
{
    char* name; 
    char* type;
} token;

//Stores a token and if it is a final state
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

/**
 * @brief Adds the states transitions to the matrix
 * 
 * @param matrix 
 */
void populate_matrix(int **matrix);

/**
 * @brief Allocate the vector of states
 * 
 * @return state 
 */
state* create_state_vector();

/**
 * @brief Add the final states to the vectpr
 * 
 * @param final_states
 */
void add_states(state *final_states);


/**
 * @brief deallocate the vector
 * 
 * @param final_states 
 */
void free_vector(state *final_states);

/**
 * @brief read the current token and apply the transition of states
 * 
 * @param program, transition_matrix, vec_state
 */
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