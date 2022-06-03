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


void populate_transition_matrix(int **matrix)
{
    fill_matrix_state(matrix, 0, 0, 127, 0);
    matrix[0]['+'] = 1;
    matrix[0]['-'] = 2;
    matrix[0]['*'] = 3;
    matrix[0]['/'] = 4;

    matrix[0]['>'] = 5;
    matrix[0]['<'] = 8;

    fill_matrix_state(matrix, 0 , '0', '9', 12);
    fill_matrix_state(matrix, 0 , 'A', 'Z', 12);
    fill_matrix_state(matrix, 0 , 'a', 'z', 12);
    
}


void fill_matrix_state(int **matrix, int state, int start, int end, int value){
    int j;
    
    for (j = start; j <= end; j++)
        matrix[state][j] = value;
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



