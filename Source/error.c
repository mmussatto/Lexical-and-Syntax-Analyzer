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

#include "Headers/error.h"


error* create_errors_vector(int n)
{
    error* vec_error = (error*) calloc(n, sizeof(error));
    return vec_error;
}


void populate_errors_vector(error* vec_errors, char* file_name)
{ 
    FILE *csv = open_file(file_name, 'r');

    read_error_csv_file(csv, vec_errors);

    fclose(csv);

}

void read_error_csv_file(FILE *csv, error *vec_errors)
{
    //Consider the file already opened

    //Control variables
    int i;
    char buff[100];
    char s_error[100];

    //Reading the transition matrix from a csv file
    for(i = 1; i < NUM_ERRORS; i++){
       
        fgets(buff, sizeof(buff), csv);

        sscanf(buff, "%[^\n]s", s_error);

        //printf("%s\n", s_error);

        //Add to the matrix
        vec_errors[i].error_token.type = strdup(s_error);
    }

}


void free_errors_vector(error* vec_error)
{
    free(vec_error);
}