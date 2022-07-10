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

#include "Headers/error_types.h"

/***************** Codigo do Dois começa a aqui ****************/

synt_error_vec* create_synth_error_vector(int n)
{
    //Alloc the synt error vector
    synt_error_vec* vec_synt_error = (synt_error_vec*) malloc(sizeof(synt_error_vec));
    
    //Stores the size
    vec_synt_error->size = n;

    vec_synt_error->list_size = 0;

    //Initialize the error description
    vec_synt_error->list_errors = (synt_error *) malloc(n*sizeof(synt_error));

    return vec_synt_error;
}

void add_synt_error(synt_error_vec* vec_synt_error, char *descricao, int linha)
{
    if(vec_synt_error->list_size >= vec_synt_error->size - 1)
    {
        vec_synt_error->size += 10;
        vec_synt_error->list_errors = realloc(vec_synt_error->list_errors, vec_synt_error->size);
    }

    vec_synt_error->list_errors[vec_synt_error->list_size].desc = strndup(descricao, strlen(descricao));
    vec_synt_error->list_errors[vec_synt_error->list_size].line = linha;

    vec_synt_error->list_size++;
}

void free_synt_errors_vector(synt_error_vec* vec_synt_error)
{
    int i;

    for (i = 0; i < NUM_ERRORS; i++){
        free(vec_synt_error->list_errors[i].desc);
    }

    free(vec_synt_error->list_errors);
    free(vec_synt_error);
}

/********************* Codigo do Dois termina aqui **************/

error* create_errors_vector(int n)
{
    error* vec_error = (error*) calloc(n, sizeof(error));
    return vec_error;
}


void free_errors_vector(error* vec_error)
{
    int i;

    for (i = 0; i < NUM_ERRORS; i++){
        free(vec_error[i].error_token.name);
        free(vec_error[i].error_token.type);
    }
    free(vec_error);
}


void populate_errors_vector(error* vec_errors, char* file_name)
{ 
    FILE *tsv = open_file(file_name, 'r');

    read_error_tsv_file(tsv, vec_errors);

    fclose(tsv);

}


void read_error_tsv_file(FILE *tsv, error *vec_errors)
{
    //Consider the file already opened

    //Control variables
    int i;
    char buff[100];
    char s_error[100];

    //Reading the errors from a tsv file
    for(i = 1; i < NUM_ERRORS; i++){
       
        //Reads line from file and puts it in a buffer
        fgets(buff, sizeof(buff), tsv);

        //Get only the error from the buffer
        sscanf(buff, "%[^\n]s", s_error);

        //Add to the matrix
        vec_errors[i].error_token.type = strdup(s_error);

        //printf("%s\n", s_error);      //Debug print to terminal
    }

}