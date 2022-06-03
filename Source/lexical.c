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

    for(i = 0; i < ROWS; i++)
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


void fill_matrix_state(int **matrix, int state, int start, int end, int value){
    int j;
    
    for (j = start; j <= end; j++)
        matrix[state][j] = value;
}

bool check_plusminus_state(int curr_state, vec_token *vec_tokens){
    
    if (curr_state == STATE_PLUS || curr_state == STATE_MINUS)
    {
        if(strcmp(last_vec_token(tokens_readed).type, "num_int")== 0)
            return true;

        if(strcmp(last_vec_token(tokens_readed).type, "num_real")== 0)
            return true;
    }

    return false;
}

token get_token(FILE* program, int **transition_matrix, state *vec_states, vec_token* tokens_readed)
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
            
        }

        //Testing if we are on a final state
        if(vec_states[curr_state].final || check_plusminus_state(int curr_state, vec_token vec_tokens))
        {
            //retroceder
            if(vec_states[curr_state].go_back)
                move_back_fp(program, 1);       //remove look ahead token from file pointer

            move_back_fp(program, n_characters_read);
            string = read_file_strng(ing(program, str_size);
        }

    }

    token EOF_token;
    EOF_token.name = "EOF";

    return EOF_token;
}

token get_token_from_chernobil(FILE* program, int **transition_matrix, state *final_states, vec_token tokens_readed)
{   
    //Variables for storing user identifiers
    bool ident_flag = false;    //indicates if we're reading an identifier
    char *str_identifier;       //string of the identifier
    int str_size = 0;           //size of the string
    int letters = 0;            //number of letter in the string
    token token_ident;          //Temporary token to store the identifier chain

    //Stores the current state of the automaton
    int curr_state = 0;

    char character, ch_aux;
    
    //Get the token before
    token t_before = tokens_readed.tokens[tokens_readed.size];
    int flag_number = 0;

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
                //Testing if we have an special case
                if(flag_number)
                {
                    move_back_fp(program, str_size);
                    str_identifier = read_file(program, str_size);
                    token_ident.name = atoi(str_identifier);
                    token_ident.type = (char *) malloc(11*sizeof(char));
                    strcpy(token_ident.type, "NUMERO");

                    if(flag_number == 2)
                        token_ident.name *= -1;                    
                }
                //We read it all, time to return
                if(!ident_flag)
                {
                    return final_states[curr_state].s_token;
                }
                else
                {
                    move_back_fp(program, str_size);
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
                }

                //Special case: use look "before" techniche
                if(curr_state == 14 || curr_state == 15)
                {
                    if(strcmp(t_before.type, "NUMERO") == 0)
                    {
                        //WE HAVE AN OPERATOR
                    }                       
                    else
                    {
                        //WE HAVE A NUMBER SIGNAL
                        if(character == '+')
                            flag_number = 1; //POSITIVE NUMBER
                        else
                            flag_number = 2; //NEGATIVE NUMBER 
                    } 
                }
                else
                    flag_number = 0;

                if(ident_flag) //Reading identifier, add the character
                {
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



