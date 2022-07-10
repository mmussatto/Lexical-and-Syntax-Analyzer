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

#define NUM_RESERVEDS 17         //Number of reserved symbols

typedef struct 
{
    token reserved_symb;
} reserved;


/**
 * @brief Create a reserved vector object
 * 
 * @param n             numeber of reserved words 
 * 
 * @return reserved*    reserved words vector
 */
reserved* create_reserved_vector(int n);


/**
 * @brief   Deallocate reserved words vetor
 * 
 * @param vec_reserved  reserved words vector 
 */
void free_reserved_vector(reserved *vec_reserved);


/**
 * @brief Populate the reserved words vector
 * 
 * @param vec_reserved  reserved words vector
 * @param file_name     name of a tvs file cointaing the reserved words
 */
void populate_reserved_vector(reserved *vec_reserved, char *file_name);


/**
 * @brief Read a tsv file with all the reserved words 
 * 
 * @param tsv           pointer to tsv file 
 * @param vec_reserved  reserved words vector
 */
void read_reserved_tsv_file(FILE *tsv, reserved* vec_reserved);


/**
 * @brief Check if a token is a reserved word
 * 
 * @param t             token to be checked
 * @param vec_reserveds reserved words vector 
 */
void check_reserverd_symbols(token *t, reserved *vec_reserveds);
