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


FILE* read_new_file(char *name, char mode);
int check_EOF();
bool read_character(FILE* arq, char *ch);
char* read_file(FILE *program, int size);
void return_file_pointer(FILE  *arq, int shift);
