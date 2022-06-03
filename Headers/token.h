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
 * @brief 
 * 
 * @param vec_tokens 
 * @return token 
 */
token last_vec_token(vec_token* vec_tokens);

/**
 * @brief 
 * 
 * @param vec_tokens 
 * @param t 
 */
void vec_tokens_push_back(vec_token* vec_tokens, token t);


void free_tokens_vector(vec_token* vec_tokens);