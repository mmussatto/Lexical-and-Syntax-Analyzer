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

 
//Store the possible tokens of the program
typedef struct
{
    char* name; 
    char* type;
} token;

//Stores a token and if it is a final state
typedef struct
{
    bool final; 
    token s_token;
} state;


state* create_state_vector(int ROWS);

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
void free_vector_states(state *final_states);
