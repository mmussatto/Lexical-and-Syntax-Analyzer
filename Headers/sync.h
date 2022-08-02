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

#include "Headers/lexical.h"

//Stack to managing the synchronization tokens
typedef struct{
    int size;       //size of the memory alocated
    int curr_size;  //number of elements inside
    char **list_tokens;  
}stack;


/**
 * @brief Create a sync stack object
 * 
 * @return stack* 
 */
stack* create_sync_stack();

/**
 * @brief Deallocate the errors vector
 * 
 * @param sync_stack synchronization tokens stack
 */
void free_sync_stack(stack* sync_stack);

/**
 * @brief Push tokens to the synchronization stack
 * 
 * @param sync_stack synchronization stack
 * @param string token to be added 
 */
void sync_push (stack* sync_stack, char* string);

/**
 * @brief Pop tokens from the synchronization stack
 * 
 * @param sync_stack synchronization stack
 * @param n number of tokens to be poped
 */
void sync_pop (stack* sync_stack, int n);