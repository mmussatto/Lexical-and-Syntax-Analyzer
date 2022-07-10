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

typedef struct {
    token error_token;  
} error;

typedef struct{
    char *desc;
    int line;
}synt_error;

typedef struct{
    int size;
    int list_size;
    synt_error *list_errors;  
}synt_error_vec;


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


/**
 * @brief Create a synth error vector object
 * 
 * @param n                 initial size of the vector
 * @return synt_error_vec*  
 */
synt_error_vec* create_synth_error_vector(int n);


/**
 * @brief Adds a syntax error to the vector
 * 
 * @param vec_synt_error    vector containing all errors from the syntax analyzer
 * @param description       error message
 * @param linha             line containing the error
 */
void add_synt_error(synt_error_vec* vec_synt_error, char *description, int linha);


/**
 * @brief  Deallocate memory from errors vector
 * 
 * @param vec_synt_error    vector containing all errors from the syntax analyzer
 */
void free_synt_errors_vector(synt_error_vec* vec_synt_error);


/**
 * @brief Sorts the synt error vector
 * 
 * @param vec_synt_error vector containing all errors from the syntax analyzer
 */
void sort_synt_error_vec(synt_error_vec *vec_synt_error);


/**
 * @brief Write all error token to error_file
 * 
 * @param fp              Pointer to error_file
 * @param vec_synt_error  Vector of syntatic erros
 * @param vec_tokens      Vector of tokens
 */
void write_error_file(FILE *fp, synt_error_vec *vec_synt_error, vec_token *vec_tokens);
