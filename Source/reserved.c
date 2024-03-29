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


void free_reserved_vector(reserved *vec_reserved)
{
    int i;
    //Reading the reserved words from the tsv file
    for(i = 0; i < NUM_RESERVEDS; i++)
    {   
        free(vec_reserved[i].reserved_symb.name);
        free(vec_reserved[i].reserved_symb.type);
    }

    free(vec_reserved);
}


void populate_reserved_vector(reserved *vec_reserved, char *file_name)
{
    FILE *tsv = open_file(file_name, 'r'); 

    read_reserved_tsv_file(tsv, vec_reserved);   

    fclose(tsv);
}


void read_reserved_tsv_file(FILE *tsv, reserved* vec_reserved)
{
    //Consider the file already opened

    //Control variables
    int i;
    char string1[50];   //string of the reserved word
    char string2[50];   //type of reserved word

    //Reading the reserved words from the tsv file
    for(i = 0; i < NUM_RESERVEDS; i++)
    {
        //Read the integer
        fscanf(tsv, "%s\t%s", string1, string2);

        //Create the reserved token
        vec_reserved[i].reserved_symb.name = strdup(string1);
        vec_reserved[i].reserved_symb.type = strdup(string2);

        //printf("%s, %s\n", string1, string2);     //Debug print

    }
}


void check_reserverd_symbols(token *t, reserved *vec_reserveds)
{
    int i;

    //Run through the reserved words vector
    for (i = 0; i < NUM_RESERVEDS; i++)
    {
        if (strcmp(t->name, vec_reserveds[i].reserved_symb.name) == 0)
        {
            t->type = strdup(vec_reserveds[i].reserved_symb.type);  //token type is now the reserved word's type
            return;
        }
    }
}