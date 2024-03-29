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
#include "Headers/syntax.h"

int main(int argc, char** argv)
{
    /*------------ Checking runtime parameters ------------*/
    if(argc != 2)
    {
        printf("Provide just the name of the file\n");
        return 1;
    }


    /*------------ Opening program file ------------*/
    //Opening file with the program to be tokenized  
    FILE *program = open_file(argv[1],'r');
    
    //Checking for error on file opening
    if(program == NULL)
    {
        printf("Error opening program file\n");
        return 1;
    }
    

    /*------------ Creating vectors and alocatting memory ------------*/
    // Allocating Transition Matrix
    int **transition_matrix = create_transition_matrix();
    populate_transition_matrix(transition_matrix, "Data/transition_matrix.tsv"); 

    // Allocating Vector of states
    state* vec_states = create_states_vector(NUM_STATES);
    populate_states_vector(vec_states, "Data/states.tsv"); 

    // Allocating Vector of possible lexical errors
    error *vec_errors = create_errors_vector(NUM_ERRORS);
    populate_errors_vector(vec_errors, "Data/errors.tsv"); 

    // Allocating Vector of reserved words
    reserved *vec_reserveds = create_reserved_vector(NUM_RESERVEDS);
    populate_reserved_vector(vec_reserveds, "Data/reserved_symbols.tsv");

    //Allocating the Vector of tokens read
    vec_token *vec_tokens = create_tokens_vector();

    //Allocating the vector of syntatic errors
    synt_error_vec *vec_synt_error = create_synth_error_vector(10); 

    //Allocating the stack of synchronization tokens
    stack *sync_stack = create_sync_stack();

    //Keeps track of the current line of the program
    int curr_line = 1;


    /*------------ Lexical analyser logic ------------*/
    //Read file and push tokens read to vector
    do
    {
        vec_tokens_push_back(vec_tokens, get_token(program, transition_matrix, vec_states, vec_tokens, vec_errors, vec_reserveds, &curr_line));
       
    } while(last_vec_token(vec_tokens).name == NULL || strcmp(last_vec_token(vec_tokens).name,"EOF") != 0  ); 


    /*------ Syntax Analyzer --------*/
    ASD(vec_tokens, vec_synt_error, sync_stack);


    /*------ Writting in out file --------*/
    //Open out file
    FILE *fp_out = fopen("Output/tokens.txt", "w");

    //Checking for error on file opening
    if(fp_out == NULL)
    {
        printf("Error opening output file\n");
        return 1;
    }

    //Opening error file
    FILE *fp_error = fopen("Output/errors.txt","w");
    
    //Checking for error on file opening
    if(fp_error == NULL)
    {
        printf("Error opening error file\n");
        return 1;
    }


    //Write all tokens read to file
    write_tokens_file(fp_out, vec_tokens);

    //Write all errors to file
    write_error_file(fp_error, vec_synt_error, vec_tokens);

    
    /*------ Deallocating memory --------*/
    //free data structures
    free_transition_matrix(transition_matrix);
    free_states_vector(vec_states);
    free_errors_vector(vec_errors);
    free_tokens_vector(vec_tokens);
    free_reserved_vector(vec_reserveds);
    free_synt_errors_vector(vec_synt_error);
    

    /*------ Closing the files --------*/
    fclose(program);
    fclose(fp_out);
    fclose(fp_error);
    
    return 0;
}
