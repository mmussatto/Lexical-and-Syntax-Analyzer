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


token get_token(FILE* program, int **transition_matrix, state *final_states)
{   
    //Variables for storing user identifiers
    bool ident_flag = false;    //indicates if we're reading an identifier
    char *str_identifier;       //string of the identifier
    int str_size = 0;           //size of the string
    int letters = 0;            //number of letter in the string
    token token_ident;          //Temporary token to store the identifier chain

    //Stores the current state of the automaton
    int curr_state = 0;

    char character;

    //Loop while there are characters to read or the automaton hasn't reached a final state
    while(read_character(program, &character))
    {   
        //Get the transition value
        curr_state = transition_matrix[curr_state][(int)character];
        
        //Not an error, usual case
        if (curr_state >= 0)
        {
            //Testing if we are on a final state
            if(final_states[curr_state].final)
            {
                //We read it all, time to return
                if(!ident_flag)
                    return final_states[curr_state].s_token;
                else
                {
                    return_file_pointer(program, str_size);
                    str_identifier = read_file(program, str_size);
                    token_ident.name = str_identifier;
                    token_ident.type = (char *) malloc(11*sizeof(char));
                    strcpy(token_ident.type, "IDENTIFIER");
                }
            }
            else
            {
                //Not in a final state
                // Check if we need to read the token 
                if(curr_state == 12 && !ident_flag)
                {
                    ident_flag = true; //We are in the identifiers sate, so we need to read!
                    str_identifier = calloc(2, sizeof str_identifier); //initialize the string
                    letters = 1;   //does not count the '\0'
                    str_size = 2;
                } 

                if(ident_flag) //Reading identifier
                {
                    if (str_size <= letters + 1)
                    {
                        str_size *= 2;
                        str_identifier = realloc(str_identifier, str_size * sizeof(char));
                    }
                        
                    str_identifier[letters] = character;
                    letters ++;
                    str_identifier[letters] = '\0';
                    str_size++;
                }
            }    
        }
       // else // Error
      
    }

    token x;
    x.name = "EOF";
    x.type = "EOF";

    return x;
}


void populate_transition_matrix(int **matrix)
{
    fill_matrix_rows(matrix, 0, 0, 127, 0);
    matrix[0]['+'] = 1;
    matrix[0]['-'] = 2;
    matrix[0]['*'] = 3;
    matrix[0]['/'] = 4;

    matrix[0]['>'] = 5;
    matrix[0]['<'] = 8;

    fill_matrix_rows(matrix, 0 , '0', '9', 12);
    fill_matrix_rows(matrix, 0 , 'A', 'Z', 12);
    fill_matrix_rows(matrix, 0 , 'a', 'z', 12);
    
}

void fill_matrix_rows(int **matrix, int line, int start, int end, int value){
    int j;
    
    for (j = start; j <= end; j++)
        matrix[line][j] = value;
}

