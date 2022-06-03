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
    //Checking runtime parameters
    if(argc != 2)
    {
        printf("Provide just the name of the file\n");
        return 1;
    }
      
    FILE *program = open_file(argv[1],'r');
  
    //Checking for error on file opening
    if(program == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }
    
    /*------ Lexical analyser logic --------*/
    int **transition_matrix = create_transition_matrix();
    populate_transition_matrix(transition_matrix); // Matrix of transitions

    state* vec_states = create_states_vector(NUM_STATES);
    populate_states_vector(vec_states); // Vector of states

    error *vec_errors = create_errors_vector(NUM_ERRORS);
    populate_errors_vector(vec_errors); // Vector of errors

    vec_token *vec_tokens = create_tokens_vector();

    do
    {
        vec_tokens_push_back(vec_tokens, get_token(program, transition_matrix, vec_states, vec_tokens, vec_errors));
       
    } while(strcmp(last_vec_token(vec_tokens).name,"EOF") != 0); 

    FILE *f_out = open_file("saida.txt", 'a');

    write_tokens_file(f_out, vec_tokens);

    //free data structures
    free_transition_matrix(transition_matrix);
    free_states_vector(vec_states);
    free_errors_vector(vec_errors);
    free_tokens_vector(vec_tokens);
    
    //Closing the files
    fclose(program);
    fclose(f_out);
    return 0;
}
