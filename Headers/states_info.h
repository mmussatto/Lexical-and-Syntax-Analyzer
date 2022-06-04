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

 
//Stores a token and if it is a final state
typedef struct
{
    bool final; 
    bool go_back;       //indicates if the look ahead token has been read;
    token s_token;
} state;


/**
 * @brief Create a states vector object
 * 
 * @param size      - size of the vector
 * @return state*   - states vector
 */
state* create_states_vector(int size);


/**
 * @brief Adds the states to the vector
 * 
 * @param vec_states - states vector
 */
void populate_states_vector(state *vec_states, char* file_name);


void read_state_tsv_file(FILE *tsv, state* vec_states);


/**
 * @brief Deallocates the vector
 * 
 * @param vec_states - states vector
 */
void free_states_vector(state *vec_states);
