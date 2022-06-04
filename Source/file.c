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


FILE* open_file(char *name, char mode)
{
    FILE *fp;

    fp = fopen(name, &mode);

    return fp;
}


bool read_character(FILE* fp, char *ch)
{
    return (fscanf(fp, "%c", ch) == 1);
}


char* read_file_string(FILE *program, int size)
{
    char *string = malloc(size * sizeof(char));
    fread(string, sizeof(char), size, program);
    return string;
}


void move_back_fp(FILE  *fp, int shift)
{
    fseek(fp, - shift, SEEK_CUR); 
}


int check_EOF(FILE *fp)
{
    char value;

    //Didnt read anything, EOF
    if(!fread(&value, sizeof(char), 1, fp))
        return 1;
    else
    {
        //Return the pointer, this is not EOF
        move_back_fp(fp, 1);
        return 0;
    }

}
