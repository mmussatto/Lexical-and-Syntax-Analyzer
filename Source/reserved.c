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


#include"Headers/reserved.h"


reserved* create_reserved_vector(int n)
{
    reserved* vec_reserved = (reserved*) calloc(n, sizeof(reserved));
    return vec_reserved;
}


void populate_reserved_vector(char *file_name, reserved *vec_reserved)
{
    // FILE *csv = open_file(file_name, 'r'); 

    // read_reserved_csv_file(csv, vec_reserved);   

    // fclose(csv);
}


void free_reserved_vector(reserved *vec_reserved)
{
    free(vec_reserved);
}


void read_reserved_csv_file(FILE *csv, reserved* vec_reserved)
{
    //Consider the file already opened

    //Control variables
    int i;

    //Reading the transition matrix from a csv file
    for(i = 0; i < NUM_RESERVEDS; i++)
    {
        //Read the integer
        fscanf(csv, "%s%*c %s", vec_reserved[i].reserved_symb.name, vec_reserved[i].reserved_symb.type);
    }
}
