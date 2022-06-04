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
    token reserved_symb;
} reserved;


reserved* create_reserved_vector(int NUM_RESERVEDS);

void populate_reserved_vector(char *file_name, reserved *vec_reserved);

void free_reserved_vector(reserved *vec_reserved);

