#pragma once

#include<stdio.h>
#include <stdbool.h>

FILE* ReadFile(char *name, char mode);
int CheckEOF();
bool ReadCharacter(FILE* arq, char *ch);
void ReturnPointer(FILE  *arq, int shift);
