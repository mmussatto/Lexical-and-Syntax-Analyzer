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

#include <stdlib.h>
#include <stdio.h>

#include "file.h"

#define VALID_CHARACTERS 128    //Possible valid characters
#define NUM_STATES 30           //Number of states


/**
 * @brief Create a (NUM_STATES x VALID_CHARACTERS) matrix populated with the invalid
 *  chareacter '-1'
 * 
 * @return int** - Matrix created
 */
int** create_transition_matrix();


/**
 * @brief Deallocate the matrix
 * 
 * @param matrix    Transition matrix
 */
void free_transition_matrix(int **matrix);


/**
 * @brief Adds the states transitions to the matrix
 * 
 * @param matrix    Transition matrix
 * @param file_name Name of the tsv file containing the matrix
 */
void populate_transition_matrix(int **matrix, char* file_name);


/**
 * @brief Reads a tsv file with the values of the transition matrix
 * 
 * @param tsv       Pointer to tsv file
 * @param matrix    Transition Matrix
 */
void read_matrix_tsv_file(FILE *tsv, int **matrix);