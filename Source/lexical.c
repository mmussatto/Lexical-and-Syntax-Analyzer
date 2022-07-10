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


token* get_token(FILE* program, int **transition_matrix, state *vec_states, 
                vec_token* vec_tokens, error* vec_errors, reserved* vec_reserveds, int* curr_line)
{

    //Control Variables
    char character;     
    int curr_state = 0;
    int n_characters_read = 0;

    //Loop while there are characters to read or the automaton hasn't reached a final state or error
    while(read_character(program, &character))
    {
        //Verifies if it's a new line
        if(character == '\n') (*curr_line)++;
 
        //Get the current state from the transition matrix
        curr_state = transition_matrix[curr_state][(int)character];

        //Counts a character if the current state is not zero (ignore spaces, tabs and new lines)
        if(curr_state != 0)
            n_characters_read++;

        //printf("%c , %d\n", character, curr_state);   //Debug print

        //Error state
        if (curr_state < 0){
            //n_characters_read--;
            return create_error_token(program, vec_errors, abs(curr_state), n_characters_read, *curr_line);
        }
           

        //Final state
        if(vec_states[curr_state].final || check_plusminus_state(curr_state, vec_tokens))
        {
            //Go back file pointer
            if(vec_states[curr_state].go_back)
            {
                if(character == '\n') (*curr_line)--;
                //Removes look ahead token
                move_back_fp(program, 1);       
                n_characters_read--;            
            }
            
            //Returns the token read
            return create_token(program, vec_states, curr_state, n_characters_read, vec_reserveds, *curr_line);
        }
    }

    if(n_characters_read == 0) //End of file
        return create_EOF_token(*curr_line);
    else{
        curr_state = -5; //EOF while unclosed comment
        return create_error_token(program, vec_errors, abs(curr_state), n_characters_read, *curr_line);
    }
}


token* create_token(FILE* fp, state* vec_states, int curr_state, int characters, reserved* vec_reserveds, int line)
{
    //Control variables
    token *t;
    t = malloc(sizeof(token));

    char *string;

    //Read string
    move_back_fp(fp, characters);
    string = read_file_string(fp, characters);

    //Create token
    t->name = strndup(string, characters);
    //t->type = malloc(strlen(vec_states[curr_state].s_token.type)*sizeof(char));
    //strcpy(t->type, vec_states[curr_state].s_token.type);
    t->type = strdup(vec_states[curr_state].s_token.type);
    t->line = line;
    
    //Checks if token is and identifier and if its a reserved word
    if (curr_state == STATE_IDENT)
        check_reserverd_symbols(t, vec_reserveds);
    
    free(string);

    //Returns token
    return t;
}


token* create_error_token(FILE* fp, error* vec_errors, int curr_state, int characters, int line)
{
    //Control variables
    token *t;
    t = malloc(sizeof(token));
    char *string;

    //Read string
    move_back_fp(fp, characters);
    string = read_file_string(fp, characters);
    
    //Create error token
    t->name = strndup(string, characters);
    t->type = strdup(vec_errors[curr_state].error_token.type);
    t->line = line;

    free(string);
    //Return error token
    return t;
}


token* create_EOF_token(int line)
{
    token *t;
    t = malloc(sizeof(token));
    t->name = strdup("EOF");
    t->type = strdup("Dread it, run from it, EOF arrives all the same.");
    t->line = line;
    return t;
}


bool check_plusminus_state(int curr_state, vec_token *vec_tokens){
    
    if (curr_state == STATE_PLUS || curr_state == STATE_MINUS)
    {
        if(strcmp(last_vec_token(vec_tokens).type, "num_int")== 0)
            return true;

        if(strcmp(last_vec_token(vec_tokens).type, "num_real")== 0)
            return true;

        if(strcmp(last_vec_token(vec_tokens).type, "identifier")== 0)
            return true;
    }

    return false;   //plus symbol is part of a number
}