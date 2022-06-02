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

#include <stdio.h>
#include <stdlib.h>
#include "Headers/lexical.h"

int main(int argc, char** argv)
{
    FILE *program = read_new_file(argv[1],'r');

    //Checking runtime parameters
    if(argc != 2)
    {
        printf("Provide just the name of the file\n");
        return 1;
    }
    
    //Checking for error on file opening
    if(program == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }
    
    /*------ Lexical analyser logic --------*/
    int **transition_matrix = create_matrix();
    populate_transition_matrix(transition_matrix);

    state* final_states = create_state_vector(ROWS);
    add_states(final_states);

    error *vec_error = create_error_vector(NUM_ERRORS);
    add_errors(vec_error);

    token t;

    while(strcmp(t.name,"EOF") != 0) //???
    {
        t = get_token(program, transition_matrix, final_states);
        //LEMBRAR DE DESALOCAR O TOKEN, A STRING DELE TA SENDO ALOCADA
    }

    //free data structures
    free_matrix(transition_matrix);
    free_vector_states(final_states);
    free_error_vec(vec_error);
    
    fclose(program);
    return 0;
}