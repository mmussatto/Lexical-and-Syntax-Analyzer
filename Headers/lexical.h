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

#include "error_types.h"
#include "file.h"
#include "reserved.h"
#include "states_info.h"
#include "token.h"
#include "matrix.h"


#define STATE_PLUS 2    //Number of the state representing the plus symbol
#define STATE_MINUS 3   //Number of the state representing the minus symbol
#define STATE_IDENT 11  //Number of the state representing identifiers


/**
 * @brief Get the token object
 * 
 * @param program           pointer to opened file containg the program to be tokenized
 * @param transition_matrix state transition matrix
 * @param vec_states        vector with information from all states 
 * @param vec_tokens        vector with all the token read
 * @param vec_errors        vector with possible errors
 * @param vec_reserveds     vector with reserved words
 * 
 * @return token 
 */
token* get_token(FILE* program, int **transition_matrix, state *vec_states, 
                vec_token* vec_tokens, error* vec_errors, reserved* vec_reserveds, int* curr_line);


/**
 * @brief Create a token object
 * 
 * @param fp            pointer to opened file       
 * @param vec_states    vector with information from all states 
 * @param curr_state    current state
 * @param characters    number of characters read
 * @param vec_reserveds vector with reserved words  
 * 
 * @return token        
 */
token* create_token(FILE* fp, state* vec_states, int curr_state, int characters, reserved* vec_reserveds, int line);


/**
 * @brief Create a error token object
 * 
 * @param fp            pointer to opened file       
 * @param vec_errors    vector with possible errors
 * @param curr_state    current state 
 * @param characters    number of characters read
 * 
 * @return token 
 */
token* create_error_token(FILE* fp, error* vec_errors, int curr_state, int characters, int line);


/**
 * @brief Create a EOF token object
 * 
 * @return token 
 */
token* create_EOF_token(int line);


/**
 * @brief   Checks if the current state is a plus or minus state
 * 
 * @param curr_state    current state
 * @param vec_tokens    vector with all the token read
 * 
 * @return true         the token is only the plus symbol
 * @return false        the plus is part of a number declaration
 */
bool check_plusminus_state(int curr_state, vec_token *vec_tokens);


