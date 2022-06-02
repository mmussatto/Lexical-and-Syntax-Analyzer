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


error* create_error_vector(int NUM_ERRORS){
    error* vec_error = (error*) calloc(NUM_ERRORS, sizeof(error));
    return vec_error;
}


void populate_error_vector(error* vec_error){
    
}


void free_error_vector(error* vec_error){
    free(vec_error);
}