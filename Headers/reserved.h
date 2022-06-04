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


reserved* create_reserved_vector(int n);

void populate_reserved_vector(reserved *vec_reserved, char *file_name);

void free_reserved_vector(reserved *vec_reserved);

void read_reserved_csv_file(FILE *csv, reserved* vec_reserved);

void check_reserverd_symbols(token *t, reserved *vec_reserveds);
