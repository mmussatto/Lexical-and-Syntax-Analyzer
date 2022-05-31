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

#include"Source/file.h"

FILE* read_file(char *name, char mode)
{
    FILE *arq;

    arq = fopen(name, &mode);

    return arq;
}

bool read_character(FILE* arq, char *ch)
{
    return (fscanf(arq, "%c", ch) == 1);
}

void return_pointer(FILE  *arq, int shift)
{
    fseek(arq, SEEK_SET + (SEEK_CUR-shift), SEEK_CUR);
}
