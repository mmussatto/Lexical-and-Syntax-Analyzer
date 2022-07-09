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

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "token.h"
#include "file.h"
#include "matrix.h"

 
//Stores a token and if it is a final state
typedef struct
{
    bool final;         //indicates if it is a final state
    bool go_back;       //indicates if the look ahead token has been read;
    token s_token;      //token associated to the state
} state;


/**
 * @brief Create a states vector object
 * 
 * @param size      size of the vector
 * 
 * @return state*   states vector
 */
state* create_states_vector(int size);


/**
 * @brief Deallocate the vector
 * 
 * @param vec_states    states vector
 */
void free_states_vector(state *vec_states);


/**
 * @brief Add the states to the vector
 * 
 * @param vec_states    states vector
 * @param file_name     name of the tsv file containing the states information
 */
void populate_states_vector(state *vec_states, char* file_name);


/**
 * @brief Read a tsv file containing the states information
 * 
 * @param tsv           pointer to tsv file 
 * @param vec_states    states vector
 */
void read_state_tsv_file(FILE *tsv, state* vec_states);



