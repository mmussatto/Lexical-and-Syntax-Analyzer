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

#include"Headers/file.h"


FILE* read_new_file(char *name, char mode)
{
    FILE *fp;

    fp = fopen(name, &mode);

    return fp;
}


bool read_character(FILE* fp, char *ch)
{
    return (fscanf(fp, "%c", ch) == 1);
}


char* read_file(FILE *program, int size)
{
    char *string = (char*) malloc(sizeof(char)*size);
    fread(string, sizeof(char), size, program);
    return string;
}


void move_back_fp(FILE  *fp, int shift)
{
    fseek(fp, SEEK_SET + (SEEK_CUR-shift), SEEK_CUR);
}
