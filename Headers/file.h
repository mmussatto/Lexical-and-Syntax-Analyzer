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

#include<stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
#include "lexical.h"

/**
 * @brief Opens a new file and returns a pointer to id
 * 
 * @param name      - string with the name of the file to be read
 * @param mode      - mode to open the file
 * @return FILE*    - pointer to the file
 */
FILE* open_file(char *name, char mode);


int check_EOF(); //Need testing


/**
 * @brief Reads a character from a file.
 * 
 * @param fp        - Pointer to the opened file
 * @param ch        - Character address 
 * @return true     - If a character has been successfully read
 * @return false    - If no character was read or if an error has ocurred
 */
bool read_character(FILE* fp, char *ch);


/**
 * @brief Reads a string from an opened file
 * 
 * @param fp        - Pointer to opened file
 * @param size      - Size of the string to be read
 * @return char*    - String read
 */
char* read_file_string(FILE *fp, int size);


/**
 * @brief Moves the file pointer back. 
 * 
 * @param fp        - Pointer to the opened file
 * @param shift     - Number of spaces for the file pointer to be moved back
 */
void move_back_fp(FILE  *fp, int shift);


FILE* create_new_file(char *name);


void write_tokens_file(FILE *fp, vec_token *vec_tokens);

void read_csv_file(FILE *csv, int **matrix);