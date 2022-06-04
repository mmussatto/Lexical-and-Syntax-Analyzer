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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"

typedef struct 
{
    token error_token;
} error;


/**
 * @brief Create a error vector object
 * 
 * @param NUM_ERRORS    - Number of different errors
 * @return error*       - Error vector
 */
error* create_errors_vector(int NUM_ERRORS);

/**
 * @brief Add error cases to the vector
 * 
 * @param vec_error - Error vector
 */
void populate_errors_vector(error* vec_error);


/**
 * @brief Deallocate the error vector
 * 
 * @param vec_error - Error vector
 */
void free_errors_vector(error* vec_error);

