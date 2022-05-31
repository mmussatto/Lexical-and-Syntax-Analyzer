#pragma once

#include<stdio.h>
#include <stdbool.h>

FILE* read_file(char *name, char mode);
int check_EOF();
bool read_character(FILE* arq, char *ch);
void return_pointer(FILE  *arq, int shift);
