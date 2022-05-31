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
 
#include <stdbool.h>
#include <stdlib.h>

#define COLUMNS 127 
#define ROWS 10

/**
 * @brief Create a ROWSxCOLUMNS matrix populated with the invalid
 *  chareacter '-'
 * 
 * @return int** - matrix created
 */
int** create_matrix();

/**
 * @brief deallocate the matrix
 * 
 * @param matrix 
 */
void free_matrix(int **matrix);

void populate_matrix(int **matrix);