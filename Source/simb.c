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


#include"Headers/simb.h"


reserved* create_reserved_vector(int NUM_RESERVEDS)
{
    reserved* vec_reserved = (reserved*) calloc(NUM_RESERVEDS, sizeof(reserved));
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

