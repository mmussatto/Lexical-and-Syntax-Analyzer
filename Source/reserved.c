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


void populate_reserved_vector(reserved *vec_reserved, char *file_name)
{
    FILE *csv = open_file(file_name, 'r'); 

    read_reserved_csv_file(csv, vec_reserved);   

    fclose(csv);
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
    char buff[100];
    char string1[50];
    char string2[50];

    //Reading the transition matrix from a csv file
    for(i = 0; i < NUM_RESERVEDS; i++)
    {
        //Read the integer
        fscanf(csv, "%s%*c %s", vec_reserved[i].reserved_symb.name, vec_reserved[i].reserved_symb.type);

        fgets(buff, sizeof(buff), csv);
        sscanf(buff, "%[^,\n],%s", string1, string2);

        //printf("%s, %s\n", string1, string2);

        vec_reserved[i].reserved_symb.name = strdup(string1);
        vec_reserved[i].reserved_symb.type = strdup(string2);

    }
}

void check_reserverd_symbols(token *t, reserved *vec_reserveds)
{
    int i;

    for (i = 0; i < NUM_RESERVEDS; i++)
    {
        if (strcmp(t->name, vec_reserveds[i].reserved_symb.name) == 0)
        {
            t->type = strdup(vec_reserveds[i].reserved_symb.type);
            return;
        }
    }
}