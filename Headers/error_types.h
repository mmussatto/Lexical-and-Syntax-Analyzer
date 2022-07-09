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

#define NUM_ERRORS 6    //Number of possible errors

typedef struct 
{
    token error_token;  
} error;

typedef struct{
    int 
    char *descript;
    int line;
}synt_error;


synt_error* create_synth_error_vector(int n);

/**
 * @brief Create a error vector object
 * 
 * @param n         Number of different errors
 * @return error*   Error vector
 */
error* create_errors_vector(int n);


/**
 * @brief Deallocate the errors vector
 * 
 * @param vec_errors Errors vector
 */
void free_errors_vector(error* vec_errors);


/**
 * @brief Add error cases to the vector
 * 
 * @param vec_errors    Error vector
 * @param file_name     Name of the file
 */
void populate_errors_vector(error* vec_errors, char* file_name);


/**
 * @brief Reads the tsv file and build the errors vector
 * 
 * @param tsv           Opened tsv file containing the errors
 * @param vec_errors    Errors vector
 */
void read_error_tsv_file(FILE *tsv, error *vec_errors);
