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
#include "file.h"

#define NUM_ERRORS 6            //Number of possible errors

typedef struct 
{
    token error_token;
} error;


/**
 * @brief Create a error vector object
 * 
 * @param n - Number of different errors
 * @return error*       - Error vector
 */
error* create_errors_vector(int n);

/**
 * @brief Add error cases to the vector
 * 
 * @param vec_errors - Error vector
 * @param file_name - name of the csv file
 */
void populate_errors_vector(error* vec_errors, char* file_name);



void read_error_csv_file(FILE *csv, error *vec_errors);


/**
 * @brief Deallocate the error vector
 * 
 * @param vec_errors - Error vector
 */
void free_errors_vector(error* vec_errors);

