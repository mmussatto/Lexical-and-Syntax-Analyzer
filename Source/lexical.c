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

#include "Headers/lexical.h"


int** create_transition_matrix()
{
    int **matrix, i, j;
        
    matrix = (int **) malloc(NUM_STATES * sizeof(int*));

    for(i = 0; i < NUM_STATES; i++)
        matrix[i] = (int *) malloc(VALID_CHARACTERS * sizeof(int));

    //Populate Matrix with invalid character
    for(i = 0; i < NUM_STATES; i++)
        for(j = 0; j < VALID_CHARACTERS; j++)
            matrix[i][j] = -1;

    return matrix;
}


void free_transition_matrix(int **matrix)
{
    int i;
    
    for(i = 0; i < NUM_STATES; i++)
        free(matrix[i]);
    
    free(matrix); 
}


void populate_transition_matrix(int **matrix, char* file_name)
{
    FILE *csv = open_file(file_name, 'r'); 

    read_csv_file(csv, matrix);   

    fclose(csv);
}

bool check_plusminus_state(int curr_state, vec_token *vec_tokens){
    
    if (curr_state == STATE_PLUS || curr_state == STATE_MINUS)
    {
        if(strcmp(last_vec_token(vec_tokens).type, "num_int")== 0)
            return true;

        if(strcmp(last_vec_token(vec_tokens).type, "num_real")== 0)
            return true;
    }

    return false;
}

token get_token(FILE* program, int **transition_matrix, state *vec_states, vec_token* vec_tokens, error* vec_errors)
{

    char character;
    int curr_state = 0;
    int n_characters_read = 0;
    char *string;
    token curr_token;

    //Loop while there are characters to read or the automaton hasn't reached a final state
    while(read_character(program, &character))
    {
        n_characters_read++;

        //Get the transition value
        curr_state = transition_matrix[curr_state][(int)character];

        //Error state
        if (curr_state < 0)
        {
            curr_state =  abs(curr_state);
            move_back_fp(program, n_characters_read);
            string = read_file_string(program, n_characters_read);
            curr_token.name = strdup(string);
            curr_token.type = strdup(vec_errors[curr_state].error_token.type);
            return curr_token;
        }

        //Testing if we are on a final state
        if(vec_states[curr_state].final || check_plusminus_state(curr_state, vec_tokens))
        {
            //retroceder
            if(vec_states[curr_state].go_back)
                move_back_fp(program, 1);       //remove look ahead token from file pointer

            move_back_fp(program, n_characters_read);
            string = read_file_string(program, n_characters_read);
            curr_token.name = strdup(string);
            curr_token.type = strdup(vec_states[curr_state].s_token.type);
            return curr_token;
        }

    }

    curr_token.name = strdup("EOF");

    return curr_token;
}



