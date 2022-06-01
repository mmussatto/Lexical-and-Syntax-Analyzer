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

#include "Lexical.h"


int** create_matrix()
{
    int **matrix, i, j;
        
    matrix = (int **) malloc(ROWS * sizeof(int*));

    for(i = 0; i < ROWS; i++)
        matrix[i] = (int *) malloc(COLUMNS * sizeof(int));

    //Populate Matrix with invalid character
    for(i = 0; i < ROWS; i++)
        for(j = 0; j < COLUMNS; j++)
            matrix[i][j] = -1;

    return matrix;
}

void free_matrix(int **matrix)
{
    int i;
    
    for(i = 0; i < ROWS; i++)
        free(matrix[i]);
    
    free(matrix); 
}

void populate_matrix(int **matrix)
{
    int i, j;

    for (i = 0; i < ROWS; i++)
        for (j = 0; j < COLUMNS; j++)
            if(i == 0)
                matrix[0][j] = i+1;
        
}

// Creating a vector of states
state* create_state_vector()
{
    state* final_states = (state*) calloc(ROWS, sizeof(state));
    return final_states;
}

void add_states(state *final_states)
{
    final_states[0].final = false;

    final_states[1].final = true;
    final_states[1].s_token.name = "+";
    final_states[1].s_token.type = "simb_mais";

    final_states[2].final = true;   
    final_states[2].s_token.name = "-";
    final_states[2].s_token.type = "simb_menos";


    final_states[3].final = true;
    final_states[3].s_token.name = "*";
    final_states[3].s_token.type = "simb_vezes";
    

    final_states[4].final = true;
    final_states[4].s_token.name = "/";
    final_states[4].s_token.type = "simb_div";
}

void free_vector(state *final_states)
{
    free(final_states);
}


token get_token(FILE* program, int **transition_matrix, state *final_states)
{
    int curr_state = 0;
    char character;

    while(read_character(program, &character))
    {
        printf("%c", character);

        switch (character)
        {
        case '+':
            curr_state = transition_matrix[curr_state][0];
            break;
        case '-':
            curr_state = transition_matrix[curr_state][1];
            break;
        case '*':
            curr_state = transition_matrix[curr_state][2];
            break;
        case '/':
            curr_state = transition_matrix[curr_state][3];
            break;
        default:
            curr_state = 0;
        }

        // if(final_states[curr_state].final)
        //     return final_states[curr_state].s_token;

        if(final_states[curr_state].final)
            printf("\n%s - %s \n",final_states[curr_state].s_token.name , final_states[curr_state].s_token.type);
        else
            curr_state = 0; //teste somente

        //Implementing the finite state
    }

    token x;

    return x;

}