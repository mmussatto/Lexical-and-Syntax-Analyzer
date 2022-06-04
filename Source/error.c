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

#include "Headers/error.h"


error* create_errors_vector(int NUM_ERRORS)
{
    error* vec_error = (error*) calloc(NUM_ERRORS, sizeof(error));
    return vec_error;
}


void populate_errors_vector(error* vec_error)
{ 
    

    vec_error[1].error_token.type = strdup("ERROR(State not defined)");
    vec_error[2].error_token.type = strdup("ERROR(Badly Formed Number)");
    vec_error[3].error_token.type = strdup("ERROR(Badly Formed Real Number)");
    vec_error[4].error_token.type = strdup("ERROR(Invalid Character)");
    vec_error[5].error_token.type = strdup("ERROR(Unclosed Comment)");
}


void free_errors_vector(error* vec_error)
{
    free(vec_error);
}