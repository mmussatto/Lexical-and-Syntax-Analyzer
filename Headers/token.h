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

#include<stdlib.h>
#include<string.h>

 //Store the possible tokens of the program
typedef struct
{
    char* name; 
    char* type;
} token;

typedef struct 
{
    token* tokens;
    int size;
    int total_size; 
} vec_token;


/**
 * @brief Create a tokens vector object
 * 
 * @return vec_token* 
 */
vec_token* create_tokens_vector();


/**
 * @brief Returns the last token read
 * 
 * @param vec_tokens    - Vector with all the tokens
 * @return token        - Last token read
 */
token last_vec_token(vec_token* vec_tokens);


/**
 * @brief  Push back a token to the token vector 
 * 
 * @param vec_tokens    - Vector with all the tokens
 * @param t             - Token to be pushed back
 */
void vec_tokens_push_back(vec_token* vec_tokens, token t);


/**
 * @brief Deallocate the toekn vector
 * 
 * @param vec_tokens    - Vector with all the tokens
 */
void free_tokens_vector(vec_token* vec_tokens);