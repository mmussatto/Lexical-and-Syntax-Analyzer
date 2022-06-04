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
#include "token.h"

#define VALID_CHARACTERS 128    //Possible valid characters
#define NUM_STATES 30           //Number of states

#define NUM_ERRORS 6            //Number of possible errors

#define STATE_PLUS 2            //Number of the state representing the plus symbol
#define STATE_MINUS 3           //Number of the state representing the minus symbol


/**
 * @brief Create a (NUM_STATES x VALID_CHARACTERS) matrix populated with the invalid
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
void populate_transition_matrix(int **matrix, char* file_name);


/**
 * @brief Get the token object
 * 
 * @param program 
 * @param transition_matrix 
 * @param vec_states 
 * @param vec_tokens 
 * @param vec_errors 
 * @return token 
 */
token get_token(FILE* program, int **transition_matrix, state *vec_states, vec_token* vec_tokens, error* vec_errors);


/**
 * @brief 
 * 
 */
bool check_plusminus_state(int curr_state, vec_token *vec_tokens);

token create_token(FILE* fp, state* vec_states, int curr_state, int characters);

token create_error_token(FILE* fp, error* vec_errors, int curr_state, int characters);

token create_EOF_token();


