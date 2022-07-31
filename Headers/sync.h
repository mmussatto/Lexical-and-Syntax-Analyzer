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

#include "Headers/lexical.h"


#pragma once

typedef struct{
    int size;       //size of the memory alocated
    int curr_size;  //number of elements inside
    char **list_tokens;  
}stack;


stack* create_sync_stack();

void free_sync_stack(stack* sync_stack);

void sync_push (stack* sync_stack, char* string);

void sync_pop (stack* sync_stack, int n);